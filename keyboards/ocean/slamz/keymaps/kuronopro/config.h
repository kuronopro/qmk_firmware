#pragma once

#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY
#define HOLD_ON_OTHER_KEYPRESS
#define HOLD_ON_OTHER_KEYPRESS_PER_KEY
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define COMBO_COUNT 2

// Recommended for heavy chording.
#define QMK_KEYS_PER_SCAN 4

// Mouse key speed and acceleration.
#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY          0
#undef MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL       16
#undef MOUSEKEY_WHEEL_DELAY
#define MOUSEKEY_WHEEL_DELAY    0
#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED      6
#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX    64

#define XXX KC_NO

#define LAYOUT_kuronopro( \
    K00, K01, K02, K03, K04,        K05, K06, K07, K08, K09, \
    K10, K11, K12, K13, K14,        K15, K16, K17, K18, K19, \
    K20, K21, K22, K23, K24,        K25, K26, K27, K28, K29, \
    K30, K31, K32,      K34,        K35,      K37, K38, K39 \
) \
LAYOUT(\
    K00, K01, K02, K03, K04,        K05, K06, K07, K08, K09, \
    K10, K11, K12, K13, K14,        K15, K16, K17, K18, K19, \
    K20, K21, K22, K23, K24,        K25, K26, K27, K28, K29, \
    K30, K31, K32, XXX, K34,        K35, XXX, K37, K38, K39 \
)
