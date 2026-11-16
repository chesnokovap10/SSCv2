package logx

import (
	"io"
	"os"
	"sync"

	"golang.org/x/sys/windows"
)

// A separate lock file coordinates rotation with other processes that append
// to debug.log. Truncating under that lock keeps their open handles valid.
type journal struct {
	mu         sync.Mutex
	file, lock *os.File
	limit      int64
}

func openJournal(path string, limit int64) (*journal, error) {
	f, err := os.OpenFile(path, os.O_CREATE|os.O_RDWR, 0600)
	if err != nil {
		return nil, err
	}
	l, err := os.OpenFile(path+".lock", os.O_CREATE|os.O_RDWR, 0600)
	if err != nil {
		f.Close()
		return nil, err
	}
	return &journal{file: f, lock: l, limit: limit}, nil
}

func (j *journal) Write(p []byte) (int, error) {
	j.mu.Lock()
	defer j.mu.Unlock()
	var region windows.Overlapped
	h := windows.Handle(j.lock.Fd())
	if err := windows.LockFileEx(h, windows.LOCKFILE_EXCLUSIVE_LOCK, 0, 1, 0, &region); err != nil {
		return 0, err
	}
	defer windows.UnlockFileEx(h, 0, 1, 0, &region)
	fi, err := j.file.Stat()
	if err != nil {
		return 0, err
	}
	if fi.Size() > 0 && fi.Size()+int64(len(p)) > j.limit {
		old, err := os.OpenFile(j.file.Name()+".old", os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0600)
		if err != nil {
			return 0, err
		}
		_, copyErr := io.Copy(old, io.NewSectionReader(j.file, 0, fi.Size()))
		closeErr := old.Close()
		if copyErr != nil {
			return 0, copyErr
		}
		if closeErr != nil {
			return 0, closeErr
		}
		if err := j.file.Truncate(0); err != nil {
			return 0, err
		}
	}
	if _, err := j.file.Seek(0, io.SeekEnd); err != nil {
		return 0, err
	}
	return j.file.Write(p)
}

func (j *journal) Close() error {
	j.mu.Lock()
	defer j.mu.Unlock()
	defer j.lock.Close()
	return j.file.Close()
}
