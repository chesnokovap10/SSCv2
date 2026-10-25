/* shim.c - see shim.h */
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "btstack_config.h"
#include "btstack_debug.h"
#include "btstack_event.h"
#include "btstack_run_loop.h"
#include "btstack_hid_parser.h"
#include "hci.h"
#include "hci_dump.h"
#include "gap.h"
#include "classic/a2dp_source.h"
#include "classic/avdtp.h"
#include "classic/avdtp_util.h"
#include "classic/avrcp.h"
#include "classic/avrcp_controller.h"
#include "classic/avrcp_target.h"
#include "classic/hid_host.h"
#include "classic/btstack_link_key_db.h"
#include "classic/sdp_server.h"
#include "classic/sdp_util.h"
#include "ble/sm.h"
#include "ble/att_db_util.h"
#include "ble/att_server.h"
#include "ble/le_device_db.h"
#include "ble/gatt-service/hids_host.h"

#include "shim.h"
#include "_cgo_export.h"

/* ---- logging: BTstack log_error/log_info -> Go ------------------------- */

static int g_log_verbose;

static void dump_reset(void) {}
/* Debug journal: every HCI packet goes to Go (decoded and filtered there). */
static void dump_packet(uint8_t t, uint8_t in, uint8_t *p, uint16_t len) {
    goBtHci(t, in, p, len);
}
static void dump_message(int level, const char *fmt, va_list ap) {
    if (level < HCI_DUMP_LOG_LEVEL_ERROR && !g_log_verbose) return;
    char buf[300];
    vsnprintf(buf, sizeof(buf), fmt, ap);
    goBtLog(level, buf);
}
static const hci_dump_t g_dump = { dump_reset, dump_packet, dump_message };

void ssc_log_init(int verbose) {
    g_log_verbose = verbose;
    hci_dump_init(&g_dump);
    hci_dump_enable_packet_log(false);
}

void ssc_set_debug(int packets, int verbose) {
    g_log_verbose = verbose;
    hci_dump_enable_packet_log(packets != 0);
}

/* ---- packet handlers --------------------------------------------------- */

static btstack_packet_callback_registration_t g_hci_cb;
static btstack_packet_callback_registration_t g_sm_cb;

static void on_hci(uint8_t t, uint16_t ch, uint8_t *p, uint16_t n)   { goBtPacket(SSC_SRC_HCI, t, ch, p, n); }
static void on_a2dp(uint8_t t, uint16_t ch, uint8_t *p, uint16_t n)  { goBtPacket(SSC_SRC_A2DP, t, ch, p, n); }
static void on_avrcp(uint8_t t, uint16_t ch, uint8_t *p, uint16_t n) { goBtPacket(SSC_SRC_AVRCP, t, ch, p, n); }
static void on_sm(uint8_t t, uint16_t ch, uint8_t *p, uint16_t n)    { goBtPacket(SSC_SRC_SM, t, ch, p, n); }
static void on_hids(uint8_t t, uint16_t ch, uint8_t *p, uint16_t n)  { goBtPacket(SSC_SRC_HIDS, t, ch, p, n); }

void ssc_register_handlers(void) {
    g_hci_cb.callback = on_hci;
    hci_add_event_handler(&g_hci_cb);
    a2dp_source_register_packet_handler(on_a2dp);
    avrcp_register_packet_handler(on_avrcp);
    avrcp_controller_register_packet_handler(on_avrcp);
    avrcp_target_register_packet_handler(on_avrcp);
}

/* ---- cross-thread kick (Go guarantees one in flight) -------------------- */

static btstack_context_callback_registration_t g_kick;
static void kick_cb(void *ctx) { (void)ctx; goBtDrain(); }

void ssc_kick(void) {
    g_kick.callback = kick_cb;
    g_kick.context = NULL;
    btstack_run_loop_execute_on_main_thread(&g_kick);
}

/* ---- timers ------------------------------------------------------------ */

#define SSC_MAX_TIMERS 8
static btstack_timer_source_t g_timers[SSC_MAX_TIMERS];

static void timer_cb(btstack_timer_source_t *t) {
    goBtTimer((int)(intptr_t)btstack_run_loop_get_timer_context(t));
}

void ssc_timer_set(int id, uint32_t ms) {
    if (id < 0 || id >= SSC_MAX_TIMERS) return;
    btstack_timer_source_t *t = &g_timers[id];
    btstack_run_loop_remove_timer(t);
    btstack_run_loop_set_timer(t, ms);
    btstack_run_loop_set_timer_handler(t, timer_cb);
    btstack_run_loop_set_timer_context(t, (void *)(intptr_t)id);
    btstack_run_loop_add_timer(t);
}

void ssc_timer_stop(int id) {
    if (id < 0 || id >= SSC_MAX_TIMERS) return;
    btstack_run_loop_remove_timer(&g_timers[id]);
}

/* ---- link key DB backed by Go ------------------------------------------ */

static void db_open(void) {}
static void db_close(void) {}
static void db_set_local(bd_addr_t a) { goLinkKeyLocalAddr(a); }
static int db_get(bd_addr_t a, link_key_t k, link_key_type_t *t) {
    int ty = 0;
    int r = goLinkKeyGet(a, k, &ty);
    if (r) *t = (link_key_type_t)ty;
    return r;
}
static void db_put(bd_addr_t a, link_key_t k, link_key_type_t t) { goLinkKeyPut(a, k, (int)t); }
static void db_delete(bd_addr_t a) { goLinkKeyDelete(a); }
static int db_it_init(btstack_link_key_iterator_t *it) { it->context = (void *)0; return 1; }
static int db_it_next(btstack_link_key_iterator_t *it, bd_addr_t a, link_key_t k, link_key_type_t *t) {
    int idx = (int)(intptr_t)it->context, ty = 0;
    if (!goLinkKeyAt(idx, a, k, &ty)) return 0;
    *t = (link_key_type_t)ty;
    it->context = (void *)(intptr_t)(idx + 1);
    return 1;
}
static void db_it_done(btstack_link_key_iterator_t *it) { (void)it; }

static const btstack_link_key_db_t g_keydb = {
    db_open, db_set_local, db_close, db_get, db_put, db_delete,
    db_it_init, db_it_next, db_it_done,
};

void ssc_use_go_link_key_db(void) { hci_set_link_key_db(&g_keydb); }

/* ---- A2DP stream endpoints ---------------------------------------------- */

static void put_vendor(uint8_t *b, uint8_t cap) {
    b[0] = (uint8_t)SSC_VENDOR_ID; b[1] = (uint8_t)(SSC_VENDOR_ID >> 8);
    b[2] = (uint8_t)(SSC_VENDOR_ID >> 16); b[3] = (uint8_t)(SSC_VENDOR_ID >> 24);
    b[4] = (uint8_t)SSC_CODEC_ID; b[5] = (uint8_t)(SSC_CODEC_ID >> 8);
    b[6] = cap;
}

void ssc_register_endpoints(uint8_t *sbc_seid, uint8_t *aac_seid, uint8_t *ssc_seid, int with_ssc) {
    /* SBC: 44.1+48k, all channel modes, 16 blocks, 8 subbands, loudness. */
    static uint8_t sbc_caps[4] = { 0x3F, 0x15, 2, 53 };
    static uint8_t sbc_cfg[4]  = { 0x11, 0x15, 2, 53 };
    /* AAC-LC, 44.1+48k, 2ch, 256 kbps. */
    static uint8_t aac_caps[6] = { 0x80, 0x0C, 0x04, 0x03, 0xE8, 0x00 };
    static uint8_t aac_cfg[6]  = { 0x80, 0x04, 0x04, 0x03, 0xE8, 0x00 };
    static uint8_t ssc_caps[7], ssc_cfg[7];
    put_vendor(ssc_caps, SSC_CAP_UHQ);
    put_vendor(ssc_cfg, SSC_CAP_BASIC);

    avdtp_stream_endpoint_t *ep;
    *sbc_seid = *aac_seid = *ssc_seid = 0;
    ep = a2dp_source_create_stream_endpoint(AVDTP_AUDIO, AVDTP_CODEC_SBC,
            sbc_caps, sizeof(sbc_caps), sbc_cfg, sizeof(sbc_cfg));
    if (ep) *sbc_seid = avdtp_local_seid(ep);
    ep = a2dp_source_create_stream_endpoint(AVDTP_AUDIO, AVDTP_CODEC_MPEG_2_4_AAC,
            aac_caps, sizeof(aac_caps), aac_cfg, sizeof(aac_cfg));
    if (ep) *aac_seid = avdtp_local_seid(ep);
    if (!with_ssc) return;   /* not offered: sinks would pick it themselves */
    ep = a2dp_source_create_stream_endpoint(AVDTP_AUDIO, AVDTP_CODEC_NON_A2DP,
            ssc_caps, sizeof(ssc_caps), ssc_cfg, sizeof(ssc_cfg));
    if (ep) *ssc_seid = avdtp_local_seid(ep);
}

uint8_t ssc_set_config_aac(uint16_t cid, uint8_t local, uint8_t remote,
                           uint32_t sample_rate, uint8_t channels, uint32_t bitrate) {
    avdtp_configuration_mpeg_aac_t c;
    memset(&c, 0, sizeof(c));
    c.object_type = AVDTP_AAC_MPEG2_LC;
    c.sampling_frequency = sample_rate;
    c.channels = channels;
    c.bit_rate = bitrate;
    c.vbr = 0;
    c.drc = false;
    return a2dp_source_set_config_mpeg_aac(cid, local, remote, &c);
}

uint8_t ssc_set_config_sbc(uint16_t cid, uint8_t local, uint8_t remote,
                           uint16_t sample_rate, uint8_t channels) {
    avdtp_configuration_sbc_t c;
    memset(&c, 0, sizeof(c));
    c.sampling_frequency = sample_rate;
    c.channel_mode = channels == 1 ? AVDTP_CHANNEL_MODE_MONO : AVDTP_CHANNEL_MODE_JOINT_STEREO;
    c.block_length = AVDTP_SBC_BLOCK_LENGTH_16;
    c.subbands = AVDTP_SBC_SUBBANDS_8;
    c.allocation_method = AVDTP_SBC_ALLOCATION_METHOD_LOUDNESS;
    c.min_bitpool_value = 2;
    c.max_bitpool_value = 53;
    return a2dp_source_set_config_sbc(cid, local, remote, &c);
}

uint8_t ssc_set_config_ssc(uint16_t cid, uint8_t local, uint8_t remote, uint8_t cap) {
    static uint8_t info[7];
    put_vendor(info, cap);
    return a2dp_source_set_config_other(cid, local, remote, info, sizeof(info));
}

/* ---- HID-over-GATT mouse ------------------------------------------------ */

static uint8_t g_hid_storage[1024];
static uint8_t g_device_name[] = "SSCv2";

void ssc_hog_init(void) {
    /* SM first: it initialises the LE device DB filled afterwards. */
    sm_init();
    sm_set_io_capabilities(IO_CAPABILITY_NO_INPUT_NO_OUTPUT);
    sm_set_authentication_requirements(SM_AUTHREQ_SECURE_CONNECTION | SM_AUTHREQ_BONDING);
    g_sm_cb.callback = on_sm;
    sm_add_event_handler(&g_sm_cb);

    /* Minimal GATT server (GAP + GATT services) so the mouse's own ATT
     * requests are answered instead of timing out. */
    att_db_util_init();
    att_db_util_add_service_uuid16(0x1800);
    att_db_util_add_characteristic_uuid16(0x2A00, ATT_PROPERTY_READ, ATT_SECURITY_NONE,
                                          ATT_SECURITY_NONE, g_device_name,
                                          (uint16_t)(sizeof(g_device_name) - 1));
    att_db_util_add_service_uuid16(0x1801);
    att_server_init(att_db_util_get_address(), NULL, NULL);

    gatt_client_init();
    hids_host_init(g_hid_storage, sizeof(g_hid_storage));
}

uint8_t ssc_hids_connect(uint16_t con_handle, uint16_t *cid) {
    return hids_host_connect(con_handle, on_hids, HID_PROTOCOL_MODE_REPORT, cid);
}

int ssc_le_add_bond(int addr_type, const uint8_t addr[6], const uint8_t irk[16],
                    const uint8_t ltk[16], uint16_t ediv, const uint8_t rand[8],
                    int key_size, int secure_connection) {
    bd_addr_t a;
    sm_key_t k, l;
    uint8_t r[8];
    memcpy(a, addr, 6);
    memcpy(k, irk, 16);
    memcpy(l, ltk, 16);
    memcpy(r, rand, 8);
    int idx = le_device_db_add(addr_type, a, k);
    if (idx < 0) return idx;
    le_device_db_encryption_set(idx, ediv, r, l, key_size, 0, 0, secure_connection);
    memset(l, 0, sizeof(l));
    return idx;
}

/* Mouse fields of one HID input report, parsed with the device's report
 * descriptor (LE: from GATT, classic: from SDP). */
static int hid_parse_mouse(const uint8_t *desc, uint16_t desc_len, const uint8_t *report,
                           uint16_t len, uint32_t prev_buttons, int32_t *dx, int32_t *dy,
                           int32_t *wheel, int32_t *hwheel, uint32_t *buttons) {
    btstack_hid_parser_t parser;
    btstack_hid_parser_init(&parser, desc, desc_len, HID_REPORT_TYPE_INPUT, report, len);
    int is_mouse = 0;
    uint32_t b = prev_buttons;
    *dx = *dy = *wheel = *hwheel = 0;
    while (btstack_hid_parser_has_more(&parser)) {
        uint16_t page = 0, usage = 0;
        int32_t value = 0;
        btstack_hid_parser_get_field(&parser, &page, &usage, &value);
        if (page == 0x01) {                               /* Generic Desktop */
            if (usage == 0x30) { *dx = value; is_mouse = 1; }
            else if (usage == 0x31) { *dy = value; is_mouse = 1; }
            else if (usage == 0x38) { *wheel = value; is_mouse = 1; }
        } else if (page == 0x09 && usage >= 1 && usage <= 5) {   /* Buttons */
            if (!is_mouse) { is_mouse = 1; b = 0; }
            if (value) b |= 1u << (usage - 1); else b &= ~(1u << (usage - 1));
        } else if (page == 0x0C && usage == 0x0238) {             /* AC Pan */
            *hwheel = value;
            is_mouse = 1;
        }
    }
    *buttons = b;
    return is_mouse;
}

int ssc_hog_parse(uint16_t hids_cid, uint8_t service_index, const uint8_t *report,
                  uint16_t len, uint32_t prev_buttons, int32_t *dx, int32_t *dy,
                  int32_t *wheel, int32_t *hwheel, uint32_t *buttons) {
    return hid_parse_mouse(hids_host_descriptor_storage_get_descriptor_data(hids_cid, service_index),
                           hids_host_descriptor_storage_get_descriptor_len(hids_cid, service_index),
                           report, len, prev_buttons, dx, dy, wheel, hwheel, buttons);
}

/* ---- classic (BR/EDR) HID mouse --------------------------------------------- */

static uint8_t g_hid_classic_storage[1024];

static void on_hid(uint8_t t, uint16_t ch, uint8_t *p, uint16_t n) { goBtPacket(SSC_SRC_HID, t, ch, p, n); }

/* Registers the HID control/interrupt PSMs: the mouse reconnects by itself
 * (it pages its host when moved) and is accepted in ssc_hid_classic_accept. */
void ssc_hid_classic_init(void) {
    hid_host_init(g_hid_classic_storage, sizeof(g_hid_classic_storage));
    hid_host_register_packet_handler(on_hid);
}

uint8_t ssc_hid_classic_accept(uint16_t hid_cid) {
    return hid_host_accept_connection(hid_cid, HID_PROTOCOL_MODE_REPORT);
}

uint8_t ssc_hid_classic_decline(uint16_t hid_cid) { return hid_host_decline_connection(hid_cid); }

uint8_t ssc_hid_classic_connect(const uint8_t addr[6], uint16_t *hid_cid) {
    bd_addr_t a;
    memcpy(a, addr, 6);
    return hid_host_connect(a, HID_PROTOCOL_MODE_REPORT, hid_cid);
}

/* report: the interrupt-channel payload, HID header (0xA1 = DATA | INPUT)
 * first. Report protocol: parsed with the SDP descriptor; boot protocol (no
 * descriptor): buttons, dx, dy[, wheel] as signed bytes. */
int ssc_hid_classic_parse(uint16_t hid_cid, const uint8_t *report, uint16_t len, uint32_t prev_buttons,
                          int32_t *dx, int32_t *dy, int32_t *wheel, int32_t *hwheel, uint32_t *buttons) {
    const uint8_t *desc = hid_descriptor_storage_get_descriptor_data(hid_cid);
    uint16_t desc_len = hid_descriptor_storage_get_descriptor_len(hid_cid);
    *dx = *dy = *wheel = *hwheel = 0;
    *buttons = prev_buttons;
    if (len < 2 || report[0] != 0xA1) return 0;
    report++;
    len--;
    if (desc && desc_len)
        return hid_parse_mouse(desc, desc_len, report, len, prev_buttons, dx, dy, wheel, hwheel, buttons);
    if (len < 3) return 0;
    *buttons = report[0] & 0x1F;
    *dx = (int8_t)report[1];
    *dy = (int8_t)report[2];
    if (len >= 4) *wheel = (int8_t)report[3];
    return 1;
}

/* ---- media channel MTU override ("AAC 256" mode) ------------------------- */

void ssc_l2cap_set_remote_mtu(uint16_t local_cid, uint16_t mtu);

int ssc_media_force_mtu(uint8_t local_seid, uint16_t mtu) {
    avdtp_stream_endpoint_t *ep = avdtp_get_stream_endpoint_for_seid(local_seid);
    if (!ep || !ep->l2cap_media_cid) return -1;
    int old = l2cap_get_remote_mtu_for_local_cid(ep->l2cap_media_cid);
    ssc_l2cap_set_remote_mtu(ep->l2cap_media_cid, mtu);
    return old;
}

/* ---- C stdio -------------------------------------------------------------- */

/* BTstack prints with printf in places; keep that out of the engine's
 * stdout, which carries the JSON protocol to the tray. */
int ssc_redirect_stdout(const char *path) {
    if (!freopen(path, "a", stdout)) return -1;
    setvbuf(stdout, NULL, _IOLBF, 4096);
    return 0;
}

/* ---- SDP records + connectable ------------------------------------------ */

/* Headphones that reconnect by themselves (taken out of the case) look up
 * an A2DP Source / AVRCP service on the host first; without these records
 * they never come back on their own. */
static uint8_t g_sdp_a2dp[150];
static uint8_t g_sdp_avrcp_tg[200];
static uint8_t g_sdp_avrcp_ct[200];

void ssc_register_sdp(void) {
    a2dp_source_create_sdp_record(g_sdp_a2dp, sdp_create_service_record_handle(),
                                  AVDTP_SOURCE_FEATURE_MASK_PLAYER, NULL, NULL);
    sdp_register_service(g_sdp_a2dp);
    avrcp_target_create_sdp_record(g_sdp_avrcp_tg, sdp_create_service_record_handle(),
                                   AVRCP_FEATURE_MASK_CATEGORY_PLAYER_OR_RECORDER, NULL, NULL);
    sdp_register_service(g_sdp_avrcp_tg);
    avrcp_controller_create_sdp_record(g_sdp_avrcp_ct, sdp_create_service_record_handle(),
                                       AVRCP_FEATURE_MASK_CATEGORY_MONITOR_OR_AMPLIFIER, NULL, NULL);
    sdp_register_service(g_sdp_avrcp_ct);
    gap_connectable_control(1);   /* page scan: let paired devices connect */
}
