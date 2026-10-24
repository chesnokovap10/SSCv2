// Package ipc defines the messages exchanged between the tray, the engine
// child process (JSON lines over its stdin/stdout) and the helper service
// (JSON request/response over a named pipe).
package ipc

import (
	"bufio"
	"encoding/json"
	"io"
	"sync"
)

// ---- tray <-> engine ----------------------------------------------------------

// EngineConfig is the first line the tray writes to the engine.
type EngineConfig struct {
	Codec        string `json:"codec"` // "aac" | "ssc"
	Headphones   string `json:"headphones,omitempty"`
	Mouse        string `json:"mouse,omitempty"`
	VID          uint16 `json:"vid"`
	PID          uint16 `json:"pid"`
	MuteSpeakers bool   `json:"muteSpeakers"`
	Verbose      bool   `json:"verbose,omitempty"`
	Debug        bool   `json:"debug,omitempty"`
	AACMode      string `json:"aacMode,omitempty"` // "fit" | "frag"
	SSCBitrate   int    `json:"sscBitrate,omitempty"` // kbps, 0 = like the phone
}

// Command from tray to engine.
type Command struct {
	Cmd  string `json:"cmd"` // "stop" | "scan" | "connect" | "debug"
	Addr string `json:"addr,omitempty"`
	On   bool   `json:"on,omitempty"`
}

// Found device from a scan.
type Found struct {
	Addr  string `json:"addr"`
	Name  string `json:"name"`
	CoD   uint32 `json:"cod"`
	RSSI  int    `json:"rssi"`
	Audio bool   `json:"audio"`
}

// EngineStatus is a full snapshot sent whenever something changes.
type EngineStatus struct {
	Phase   string `json:"phase"` // firmware|starting|connecting|streaming|waiting|idle|error|stopped
	Message string `json:"message,omitempty"`

	AdapterAddr string `json:"adapterAddr,omitempty"`
	Chip        string `json:"chip,omitempty"`
	Firmware    string `json:"firmware,omitempty"`

	Headphones     string `json:"headphones,omitempty"`
	HeadphonesName string `json:"headphonesName,omitempty"`
	Connected      bool   `json:"connected"`
	Streaming      bool   `json:"streaming"`
	Codec          string `json:"codec,omitempty"`
	BitrateKbps    int    `json:"bitrateKbps,omitempty"`
	SampleRate     int    `json:"sampleRate,omitempty"`
	Volume         int    `json:"volume"` // 0..127, -1 unknown
	AVRCP          bool   `json:"avrcp"`
	CaptureDevice  string `json:"captureDevice,omitempty"`
	CaptureFormat  string `json:"captureFormat,omitempty"`
	Virtual        bool   `json:"virtual"`
	// What to undo if the engine dies: previous default output, speakers muted.
	PrevDefault string `json:"prevDefault,omitempty"`
	Muted       bool   `json:"muted"`

	Mouse        string `json:"mouse,omitempty"`
	MouseState   string `json:"mouseState,omitempty"`
	MouseReports uint32 `json:"mouseReports"`

	Queue int    `json:"queue"`
	Fails uint32 `json:"fails"`
	Sent  uint64 `json:"sent"`
}

// Event from engine to tray.
type Event struct {
	Ev      string        `json:"ev"` // status|scan|linkkey|log
	Status  *EngineStatus `json:"status,omitempty"`
	Devices []Found       `json:"devices,omitempty"`
	Addr    string        `json:"addr,omitempty"`
	Key     string        `json:"key,omitempty"`
	KeyType int           `json:"keyType,omitempty"`
	Name    string        `json:"name,omitempty"`
	Msg     string        `json:"msg,omitempty"`
}

// ---- tray -> helper ------------------------------------------------------------

// Request to the privileged helper.
type Request struct {
	Op      string `json:"op"` // ping|driver|keys-read|keys-write|virtual-install|virtual-uninstall
	VID     uint16 `json:"vid,omitempty"`
	PID     uint16 `json:"pid,omitempty"`
	WinUSB  bool   `json:"winusb,omitempty"`
	Adapter string `json:"adapter,omitempty"`
	Device  string `json:"device,omitempty"`
	Key     string `json:"key,omitempty"`
	Dir     string `json:"dir,omitempty"`
	Name    string `json:"name,omitempty"`
	Debug   bool   `json:"debug,omitempty"` // hand the op's log lines back
	Variant string `json:"variant,omitempty"` // diagnostics: driver switch variant
}

// Response from the helper.
type Response struct {
	OK      bool            `json:"ok"`
	Error   string          `json:"error,omitempty"`
	Message string          `json:"message,omitempty"`
	Data    json.RawMessage `json:"data,omitempty"`
	Version string          `json:"version,omitempty"`
	Log     []string        `json:"log,omitempty"`
}

// ---- line codec ------------------------------------------------------------------

// Writer writes JSON lines (safe for concurrent use).
type Writer struct {
	mu sync.Mutex
	w  io.Writer
}

func NewWriter(w io.Writer) *Writer { return &Writer{w: w} }

func (w *Writer) Write(v any) error {
	b, err := json.Marshal(v)
	if err != nil {
		return err
	}
	b = append(b, '\n')
	w.mu.Lock()
	defer w.mu.Unlock()
	_, err = w.w.Write(b)
	return err
}

// Reader reads JSON lines.
type Reader struct{ s *bufio.Scanner }

func NewReader(r io.Reader) *Reader {
	s := bufio.NewScanner(r)
	s.Buffer(make([]byte, 64<<10), 4<<20)
	return &Reader{s: s}
}

func (r *Reader) Read(v any) error {
	if !r.s.Scan() {
		if err := r.s.Err(); err != nil {
			return err
		}
		return io.EOF
	}
	return json.Unmarshal(r.s.Bytes(), v)
}

// Version of the program (set from main via -ldflags or constant).
var Version = "2.0.0-dev"
