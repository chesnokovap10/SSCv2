package main

import (
	"fmt"
	"io"
	"os"
)

const (
	discover           = 0x01
	getAllCapabilities = 0x0c
	getCapabilities    = 0x02
)

// The transport presents one L2CAP SDU per read or write.
type probe struct {
	link  io.ReadWriter
	label byte
}

type rejection struct {
	messageType byte
	payload     []byte
}

func (r *rejection) Error() string {
	return fmt.Sprintf("AVDTP rejected command (type %d, payload % x)", r.messageType, r.payload)
}

func (p *probe) command(signal byte, payload ...byte) ([]byte, error) {
	label := p.label
	p.label = (label + 1) & 15
	packet := append([]byte{label << 4, signal}, payload...)
	n, err := p.link.Write(packet)
	if err != nil {
		return nil, err
	}
	if n != len(packet) {
		return nil, io.ErrShortWrite
	}

	reply := make([]byte, 65535)
	n, err = p.link.Read(reply)
	if err != nil {
		return nil, err
	}
	reply = reply[:n]
	if len(reply) == 0 || reply[0]>>4 != label {
		return nil, fmt.Errorf("unexpected AVDTP transaction: % x", reply)
	}
	if reply[0]&0x0c != 0 {
		return nil, fmt.Errorf("fragmented AVDTP response")
	}
	if len(reply) < 2 || reply[1] != signal {
		return nil, fmt.Errorf("unexpected AVDTP signal: % x", reply)
	}
	switch kind := reply[0] & 3; kind {
	case 2:
		return reply[2:], nil
	case 1, 3:
		return nil, &rejection{kind, reply[2:]}
	default:
		return nil, fmt.Errorf("received an AVDTP command while waiting for a response")
	}
}

func inspect(link io.ReadWriter, out io.Writer) error {
	p := probe{link: link}
	endpoints, err := p.command(discover)
	if err != nil {
		return fmt.Errorf("discover: %w", err)
	}
	if len(endpoints)%2 != 0 {
		return fmt.Errorf("invalid endpoint list: % x", endpoints)
	}
	for i := 0; i < len(endpoints); i += 2 {
		seid := endpoints[i] >> 2
		if endpoints[i+1]>>3 != 1 {
			continue // Audio sink only.
		}
		fmt.Fprintf(out, "SEID %d (in use: %t)\n", seid, endpoints[i]&2 != 0)
		caps, err := p.command(getAllCapabilities, seid<<2)
		if reject, ok := err.(*rejection); ok &&
			(reject.messageType == 1 || len(reject.payload) == 1 && reject.payload[0] == 0x19) {
			caps, err = p.command(getCapabilities, seid<<2)
		}
		if err != nil {
			return fmt.Errorf("SEID %d capabilities: %w", seid, err)
		}
		for len(caps) > 0 {
			if len(caps) < 2 || int(caps[1]) > len(caps)-2 {
				return fmt.Errorf("SEID %d: truncated capabilities: % x", seid, caps)
			}
			size := int(caps[1])
			value := caps[2 : 2+size]
			if caps[0] == 7 {
				if len(value) < 2 {
					return fmt.Errorf("SEID %d: truncated media codec", seid)
				}
				fmt.Fprintf(out, "  media type %#x, codec %#02x, data % x\n", value[0]>>4, value[1], value[2:])
			}
			caps = caps[2+size:]
		}
	}
	return nil
}

func run(args []string) error {
	if len(args) != 1 {
		return fmt.Errorf("usage: avdtp-probe <profile-driver device interface path>")
	}
	link, err := os.OpenFile(args[0], os.O_RDWR, 0)
	if err != nil {
		return err
	}
	defer link.Close()
	return inspect(link, os.Stdout)
}

func main() {
	if err := run(os.Args[1:]); err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}
}
