package app

import (
	"os"
	"unsafe"

	"golang.org/x/sys/windows"
)

// startWorker suppresses the Windows startup cursor while retaining process
// isolation and limiting handle inheritance to the worker's standard pipes.
func startWorker(exe string, args ...string) (*os.Process, *os.File, *os.File, error) {
	input, writeInput, err := os.Pipe()
	if err != nil {
		return nil, nil, nil, err
	}
	defer input.Close()
	output, writeOutput, err := os.Pipe()
	if err != nil {
		writeInput.Close()
		return nil, nil, nil, err
	}
	defer writeOutput.Close()
	process, err := createWorker(exe, args, input, writeOutput)
	if err != nil {
		writeInput.Close()
		output.Close()
		return nil, nil, nil, err
	}
	return process, writeInput, output, nil
}

func createWorker(exe string, args []string, input, output *os.File) (*os.Process, error) {
	name, err := windows.UTF16PtrFromString(exe)
	if err != nil {
		return nil, err
	}
	command, err := windows.UTF16PtrFromString(windows.ComposeCommandLine(append([]string{exe}, args...)))
	if err != nil {
		return nil, err
	}
	var handles [2]windows.Handle
	for i, file := range []*os.File{input, output} {
		self := windows.CurrentProcess()
		if err := windows.DuplicateHandle(self, windows.Handle(file.Fd()), self, &handles[i], 0, true, windows.DUPLICATE_SAME_ACCESS); err != nil {
			return nil, err
		}
		defer windows.CloseHandle(handles[i])
	}
	attrs, err := windows.NewProcThreadAttributeList(1)
	if err != nil {
		return nil, err
	}
	defer attrs.Delete()
	if err := attrs.Update(windows.PROC_THREAD_ATTRIBUTE_HANDLE_LIST, unsafe.Pointer(&handles[0]), unsafe.Sizeof(handles)); err != nil {
		return nil, err
	}
	const startfForceOffFeedback = 0x80
	start := windows.StartupInfoEx{
		StartupInfo: windows.StartupInfo{
			Flags:      windows.STARTF_USESTDHANDLES | windows.STARTF_USESHOWWINDOW | startfForceOffFeedback,
			ShowWindow: windows.SW_HIDE,
			StdInput:   handles[0],
			StdOutput:  handles[1],
			StdErr:     handles[1],
		},
		ProcThreadAttributeList: attrs.List(),
	}
	start.Cb = uint32(unsafe.Sizeof(start))
	var info windows.ProcessInformation
	flags := uint32(windows.EXTENDED_STARTUPINFO_PRESENT | windows.CREATE_NO_WINDOW)
	if err := windows.CreateProcess(name, command, nil, nil, true, flags, nil, nil, &start.StartupInfo, &info); err != nil {
		return nil, err
	}
	defer windows.CloseHandle(info.Process)
	defer windows.CloseHandle(info.Thread)
	process, err := os.FindProcess(int(info.ProcessId))
	if err != nil {
		_ = windows.TerminateProcess(info.Process, 1)
	}
	return process, err
}
