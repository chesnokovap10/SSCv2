/*
 * btstack_config.h - BTstack compile-time configuration for SSCv2.
 *
 * Classic A2DP source (AAC / SSC / SBC endpoints) + AVRCP volume, and an LE
 * central for the HID-over-GATT mouse bridge, over WinUSB.
 */
#ifndef BTSTACK_CONFIG_H
#define BTSTACK_CONFIG_H

#define HAVE_ASSERT
#define HAVE_MALLOC
#define HAVE_POSIX_FILE_IO
#define HAVE_POSIX_TIME

#define ENABLE_CLASSIC

/* LE central: HID-over-GATT mouse. Re-encryption uses the LTK imported
 * from Windows; LE Secure Connections uses software P-256 (micro-ecc). */
#define ENABLE_BLE
#define ENABLE_LE_CENTRAL
#define ENABLE_LE_SECURE_CONNECTIONS
#define ENABLE_MICRO_ECC_FOR_LE_SECURE_CONNECTIONS
#define MAX_NR_LE_DEVICE_DB_ENTRIES 4
#define MAX_ATT_DB_SIZE 256

#define ENABLE_SOFTWARE_AES128

#define ENABLE_LOG_ERROR
#define ENABLE_LOG_INFO

#define ENABLE_L2CAP_ENHANCED_RETRANSMISSION_MODE

#define HCI_ACL_PAYLOAD_SIZE (1691 + 4)
#define HCI_INCOMING_PRE_BUFFER_SIZE 14

#define NVM_NUM_LINK_KEYS 16

/* Explicit A2DP config: required for the vendor (SSC) and AAC endpoints. */
#define ENABLE_A2DP_EXPLICIT_CONFIG

#define MAX_NR_AVDTP_STREAM_ENDPOINTS  4
#define MAX_NR_AVDTP_CONNECTIONS       1
#define MAX_NR_A2DP_SOURCE_CONNECTIONS 1

#endif
