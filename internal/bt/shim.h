/*
 * shim.h - thin C glue between BTstack and the Go side of package bt.
 * Only things that are awkward from cgo live here (static registrations,
 * callbacks, structs with enums/bitfields). All logic is in Go.
 */
#ifndef SSC_SHIM_H
#define SSC_SHIM_H

#include <stdint.h>

/* Packet sources reported to goBtPacket(). */
enum { SSC_SRC_HCI = 0, SSC_SRC_A2DP, SSC_SRC_AVRCP, SSC_SRC_SM, SSC_SRC_HIDS, SSC_SRC_HID };

/* SSC vendor codec (Samsung Scalable Codec). */
#define SSC_VENDOR_ID 0x00000075u
#define SSC_CODEC_ID  0x0103u
/* Capability byte (phone's A2DP_ParseInfoSsc): 0xF0 sample rates (0x10 48k,
 * 0x20 44.1k, 0x40 32k, 0x80 96k), 0x08 no bitrate limit, 0x04 24-bit 48k,
 * 0x02 UHQ v2 (96k). */
#define SSC_CAP_BASIC 0x0Cu  /* 24-bit 48k, no bitrate limit */
#define SSC_CAP_UHQ   0x0Eu  /* basic + 96k UHQ */

void ssc_log_init(int verbose);
void ssc_set_debug(int packets, int verbose);
int ssc_media_force_mtu(uint8_t local_seid, uint16_t mtu);
int ssc_redirect_stdout(const char *path);
void ssc_register_handlers(void);
void ssc_register_sdp(void);
void ssc_kick(void);
void ssc_timer_set(int id, uint32_t ms);
void ssc_timer_stop(int id);
void ssc_use_go_link_key_db(void);

/* Stream endpoints: returns local SEIDs (0 = not registered). */
void ssc_register_endpoints(uint8_t *sbc_seid, uint8_t *aac_seid, uint8_t *ssc_seid, int with_ssc);
uint8_t ssc_set_config_aac(uint16_t cid, uint8_t local, uint8_t remote,
                           uint32_t sample_rate, uint8_t channels, uint32_t bitrate);
uint8_t ssc_set_config_sbc(uint16_t cid, uint8_t local, uint8_t remote,
                           uint16_t sample_rate, uint8_t channels);
uint8_t ssc_set_config_ssc(uint16_t cid, uint8_t local, uint8_t remote, uint8_t cap);

/* HID-over-GATT mouse. */
void ssc_hog_init(void);
uint8_t ssc_hids_connect(uint16_t con_handle, uint16_t *cid);
int ssc_le_add_bond(int addr_type, const uint8_t addr[6], const uint8_t irk[16],
                    const uint8_t ltk[16], uint16_t ediv, const uint8_t rand[8],
                    int key_size, int secure_connection);
/* Parse one HID input report. Returns 1 when it carries mouse data. */
int ssc_hog_parse(uint16_t hids_cid, uint8_t service_index, const uint8_t *report,
                  uint16_t len, uint32_t prev_buttons, int32_t *dx, int32_t *dy,
                  int32_t *wheel, int32_t *hwheel, uint32_t *buttons);

/* Classic (BR/EDR) HID mouse. */
void ssc_hid_classic_init(void);
uint8_t ssc_hid_classic_accept(uint16_t hid_cid);
uint8_t ssc_hid_classic_decline(uint16_t hid_cid);
uint8_t ssc_hid_classic_connect(const uint8_t addr[6], uint16_t *hid_cid);
int ssc_hid_classic_parse(uint16_t hid_cid, const uint8_t *report, uint16_t len, uint32_t prev_buttons,
                          int32_t *dx, int32_t *dy, int32_t *wheel, int32_t *hwheel, uint32_t *buttons);

#endif
