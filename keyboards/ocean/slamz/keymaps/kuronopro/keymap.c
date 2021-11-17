#include QMK_KEYBOARD_H

#include "casemodes.h"
#include "swapper.h"

enum layers { _QWERTY, _SYMBOL, _NUMBER, _NAVIGATION, _CODE, _FUNCTION, _MOUSE, _LMOD, _RMOD };

// tap dance yg dipake
enum {
    // berguna untuk koding php
    // tap untuk =, double tap untuk =>
    TD_EQL_ARR,
    // tap untuk -, double tap untuk ->
    TD_MIN_ARR,
    // tap untuk <, double tap untuk <?
    TD_PHP_OPN,
    // tap untuk >, double tap untuk ?>
    TD_PHP_CLS,

    // home row mod tapi pake tap dance, klo pake mod-tap sering salah pencet
    TD_A_GUI,
    TD_S_ALT,
    TD_D_CTL,
    TD_F_SFT,
    TD_J_SFT,
    TD_K_CTL,
    TD_L_ALT,
    TD_QUO_GUI
};

// fungsi di bawah diambil dari contoh di dokumentasi qmk
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

td_state_t cur_dance(qk_tap_dance_state_t *state);

td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

// fungsi untuk TD_EQL_ARR

void equal_arrow_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code(KC_EQL);
    } else {
        register_code(KC_EQL);
        register_code16(KC_GT);
    }
}

void equal_arrow_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code(KC_EQL);
    } else {
        unregister_code(KC_EQL);
        unregister_code16(KC_GT);
    }
}

// fungsi untuk TD_MIN_ARR

void minus_arrow_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code(KC_MINS);
    } else {
        register_code(KC_MINS);
        register_code16(KC_GT);
    }
}

void minus_arrow_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code(KC_MINS);
    } else {
        unregister_code(KC_MINS);
        unregister_code16(KC_GT);
    }
}

// fungsi untuk TD_PHP_OPN

void php_open_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_LT);
    } else {
        register_code16(KC_LT);
        register_code16(KC_QUES);
    }
}

void php_open_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_LT);
    } else {
        unregister_code16(KC_LT);
        unregister_code16(KC_QUES);
    }
}

// fungsi untuk TD_PHP_CLS

void php_close_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_GT);
    } else {
        register_code16(KC_QUES);
        register_code16(KC_GT);
    }
}

void php_close_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_GT);
    } else {
        unregister_code16(KC_QUES);
        unregister_code16(KC_GT);
    }
}

// fungsi untuk TD_A_GUI

static td_tap_t td_a_gui_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void a_gui_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_a_gui_tap_state.state = cur_dance(state);
    switch (td_a_gui_tap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_A); break;
        case TD_SINGLE_HOLD: register_code(KC_LGUI); layer_on(_LMOD); break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_A); register_code(KC_A); break;
        case TD_DOUBLE_HOLD: register_code(KC_A); break;
        default: break;
    }
}

void a_gui_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_a_gui_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_A); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LGUI); layer_off(_LMOD); break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_A); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_A); break;
        default: break;
    }
    td_a_gui_tap_state.state = TD_NONE;
}

// fungsi untuk TD_S_ALT

static td_tap_t td_s_alt_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void s_alt_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_s_alt_tap_state.state = cur_dance(state);
    switch (td_s_alt_tap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_S); break;
        case TD_SINGLE_HOLD: register_code(KC_LALT); layer_on(_LMOD); break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_S); register_code(KC_S); break;
        case TD_DOUBLE_HOLD: register_code(KC_S); break;
        default: break;
    }
}

void s_alt_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_s_alt_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_S); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LALT); layer_off(_LMOD); break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_S); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_S); break;
        default: break;
    }
    td_s_alt_tap_state.state = TD_NONE;
}

// fungsi untuk TD_D_CTL

static td_tap_t td_d_ctl_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void d_ctl_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_d_ctl_tap_state.state = cur_dance(state);
    switch (td_d_ctl_tap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_D); break;
        case TD_SINGLE_HOLD: register_code(KC_LCTL); layer_on(_LMOD); break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_D); register_code(KC_D); break;
        case TD_DOUBLE_HOLD: register_code(KC_D); break;
        default: break;
    }
}

void d_ctl_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_d_ctl_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_D); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LCTL); layer_off(_LMOD); break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_D); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_D); break;
        default: break;
    }
    td_d_ctl_tap_state.state = TD_NONE;
}

// fungsi untuk TD_F_SFT

static td_tap_t td_f_sft_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void f_sft_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_f_sft_tap_state.state = cur_dance(state);
    switch (td_f_sft_tap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_F); break;
        case TD_SINGLE_HOLD: register_code(KC_LSFT); layer_on(_LMOD); break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_F); register_code(KC_F); break;
        case TD_DOUBLE_HOLD: register_code(KC_F); break;
        default: break;
    }
}

void f_sft_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_f_sft_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_F); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LSFT); layer_off(_LMOD); break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_F); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_F); break;
        default: break;
    }
    td_f_sft_tap_state.state = TD_NONE;
}

// fungsi untuk TD_J_SFT

static td_tap_t td_j_sft_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void j_sft_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_j_sft_tap_state.state = cur_dance(state);
    switch (td_j_sft_tap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_J); break;
        case TD_SINGLE_HOLD: register_code(KC_LSFT); layer_on(_RMOD); break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_J); register_code(KC_J); break;
        case TD_DOUBLE_HOLD: register_code(KC_J); break;
        default: break;
    }
}

void j_sft_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_j_sft_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_J); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LSFT); layer_off(_RMOD); break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_J); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_J); break;
        default: break;
    }
    td_j_sft_tap_state.state = TD_NONE;
}

// fungsi untuk TD_K_CTL

static td_tap_t td_k_ctl_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void k_ctl_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_k_ctl_tap_state.state = cur_dance(state);
    switch (td_k_ctl_tap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_K); break;
        case TD_SINGLE_HOLD: register_code(KC_LCTL); layer_on(_RMOD); break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_K); register_code(KC_K); break;
        case TD_DOUBLE_HOLD: register_code(KC_K); break;
        default: break;
    }
}

void k_ctl_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_k_ctl_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_K); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LCTL); layer_off(_RMOD); break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_K); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_K); break;
        default: break;
    }
    td_k_ctl_tap_state.state = TD_NONE;
}

// fungsi untuk TD_L_ALT

static td_tap_t td_l_alt_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void l_alt_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_l_alt_tap_state.state = cur_dance(state);
    switch (td_l_alt_tap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_L); break;
        case TD_SINGLE_HOLD: register_code(KC_LALT); layer_on(_RMOD); break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_L); register_code(KC_L); break;
        case TD_DOUBLE_HOLD: register_code(KC_L); break;
        default: break;
    }
}

void l_alt_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_l_alt_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_L); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LALT); layer_off(_RMOD); break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_L); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_L); break;
        default: break;
    }
    td_l_alt_tap_state.state = TD_NONE;
}

// fungsi untuk TD_QUO_GUI

static td_tap_t td_quo_gui_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void quote_double_quote_gui_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_quo_gui_tap_state.state = cur_dance(state);
    switch (td_quo_gui_tap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_QUOT); break;
        case TD_SINGLE_HOLD: register_code(KC_LGUI); layer_on(_RMOD); break;
        case TD_DOUBLE_TAP: register_code16(KC_DQUO); break;
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_QUOT); register_code(KC_QUOT); break;
        case TD_DOUBLE_HOLD: register_code(KC_QUOT); break;
        default: break;
    }
}

void quote_double_quote_gui_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_quo_gui_tap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_QUOT); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LGUI); layer_off(_RMOD); break;
        case TD_DOUBLE_TAP: unregister_code16(KC_DQUO); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_QUOT);
        case TD_DOUBLE_HOLD: unregister_code(KC_QUOT); break;
        default: break;
    }
    td_quo_gui_tap_state.state = TD_NONE;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_EQL_ARR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, equal_arrow_finished, equal_arrow_reset),
    [TD_MIN_ARR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, minus_arrow_finished, minus_arrow_reset),
    [TD_PHP_OPN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, php_open_finished, php_open_reset),
    [TD_PHP_CLS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, php_close_finished, php_close_reset),
    [TD_A_GUI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, a_gui_finished, a_gui_reset),
    [TD_S_ALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, s_alt_finished, s_alt_reset),
    [TD_D_CTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, d_ctl_finished, d_ctl_reset),
    [TD_F_SFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, f_sft_finished, f_sft_reset),
    [TD_J_SFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, j_sft_finished, j_sft_reset),
    [TD_K_CTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, k_ctl_finished, k_ctl_reset),
    [TD_L_ALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, l_alt_finished, l_alt_reset),
    [TD_QUO_GUI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, quote_double_quote_gui_finished, quote_double_quote_gui_reset)
};

enum custom_keycodes {
    // clear semua layer, balik ke default
    NORMAL = SAFE_RANGE,

    // berguna untuk ngetik variabel/fungsi ketika koding
    // caps word, capslock untuk satu kata
    CAPSWRD,
    // snake case, pencet spasi untuk _
    SNKCASE,
    // kebab case, pencet spasi untuk -
    KBBCASE,
    // camel case, pencet spasi untuk one shot shift
    CMLCASE,

    // switch window aka alt+tab
    SW_WIN
};

// short cut pindah tab
#define SW_TABL C(KC_PGUP)
#define SW_TABR C(KC_PGDN)

// shortcut copy dkk
#define UNDO    C(KC_Z)
#define CUT     C(KC_X)
#define COPY    C(KC_C)
#define PASTE   C(KC_V)
#define REDO    C(KC_B)

// shortcut untuk workspace di linuxmint
#define WS_LEFT LCA(KC_LEFT)
#define WS_RGHT LCA(KC_RGHT)
#define WSM_LFT MEH(KC_LEFT)
#define WSM_RGT MEH(KC_RGHT)

// layer change
#define TAB_NUM LT(_NUMBER, KC_TAB)
#define BSP_NAV LT(_NAVIGATION, KC_BSPC)
#define SPC_SYM LT(_SYMBOL, KC_SPC)
#define ENT_FUN LT(_FUNCTION, KC_ENT)
#define MOUSE   TO(_MOUSE)
#define MO_CODE MO(_CODE)

// home row mod
#define A_GUI   TD(TD_A_GUI)
#define S_ALT   TD(TD_S_ALT)
#define D_CTL   TD(TD_D_CTL)
#define F_SFT   TD(TD_F_SFT)
#define J_SFT   TD(TD_J_SFT)
#define K_CTL   TD(TD_K_CTL)
#define L_ALT   TD(TD_L_ALT)
#define QUO_GUI TD(TD_QUO_GUI)

// tap dance
#define EQL_ARR TD(TD_EQL_ARR)
#define MIN_ARR TD(TD_MIN_ARR)
#define LT_PHP  TD(TD_PHP_OPN)
#define GT_PHP  TD(TD_PHP_CLS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        A_GUI,   S_ALT,   D_CTL,   F_SFT,   KC_G,    KC_H,    J_SFT,   K_CTL,   L_ALT,   QUO_GUI,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
        XXXXXXX, XXXXXXX, TAB_NUM, XXXXXXX, BSP_NAV, SPC_SYM, XXXXXXX, ENT_FUN, XXXXXXX, XXXXXXX
    ),

    [_SYMBOL] = LAYOUT(
        KC_LPRN, KC_LBRC, KC_COLN, KC_RBRC, KC_RPRN, KC_EXLM, KC_LCBR, KC_PIPE, KC_RCBR, KC_QUES,
        KC_DLR,  KC_AMPR, MIN_ARR, KC_UNDS, KC_SCLN, KC_CIRC, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
        KC_GRV,  KC_AT,   EQL_ARR, KC_HASH, KC_BSLS, KC_PERC, LT_PHP,  KC_ASTR, GT_PHP,  KC_PLUS,
        XXXXXXX, XXXXXXX, KC_BSPC, XXXXXXX, KC_SPC,  _______, XXXXXXX, _______, XXXXXXX, XXXXXXX
    ),

    [_NUMBER] = LAYOUT( // media button juga dimasukkan di sini
        KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY, KC_MNXT, KC_ASTR, KC_7,    KC_8,    KC_9,    KC_PLUS,
        KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX, KC_SLSH, KC_4,    KC_5,    KC_6,    KC_MINS,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DOT,  KC_1,    KC_2,    KC_3,    KC_ENT,
        XXXXXXX, XXXXXXX, _______, XXXXXXX, _______, _______, XXXXXXX, KC_0,    XXXXXXX, XXXXXXX
    ),

    [_NAVIGATION] = LAYOUT(
        KC_ESC,  SW_TABL, SW_TABR, SW_WIN,  XXXXXXX, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  MOUSE,
        KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_INS,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_DEL,
        MO_CODE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, CAPSWRD, SNKCASE, KBBCASE, CMLCASE, KC_CAPS,
        XXXXXXX, XXXXXXX, _______, XXXXXXX, _______, _______, XXXXXXX, _______, XXXXXXX, XXXXXXX
    ),

    [_CODE] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, WSM_LFT, WS_LEFT, WS_RGHT, WSM_RGT, _______,
        XXXXXXX, XXXXXXX, _______, XXXXXXX, _______, _______, XXXXXXX, _______, XXXXXXX, XXXXXXX
    ),

    [_FUNCTION] = LAYOUT(
        KC_F12,  KC_F7,   KC_F8,   KC_F9,   XXXXXXX, XXXXXXX, XXXXXXX, KC_BRID, KC_BRIU, MOUSE,
        KC_F11,  KC_F4,   KC_F5,   KC_F6,   XXXXXXX, XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
        KC_F10,  KC_F1,   KC_F2,   KC_F3,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR,
        XXXXXXX, XXXXXXX, _______, XXXXXXX, _______, _______, XXXXXXX, _______, XXXXXXX, XXXXXXX
    ),

    [_MOUSE] = LAYOUT(
        KC_ESC,  SW_TABL, SW_TABR, SW_WIN,  XXXXXXX, KC_WH_U, KC_WH_L, KC_MS_U, KC_WH_R, NORMAL,
        KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX,
        UNDO,    CUT,     COPY,    PASTE,   REDO,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET,
        XXXXXXX, XXXXXXX, KC_BTN2, XXXXXXX, KC_BTN1, KC_BTN1, XXXXXXX, KC_BTN2, XXXXXXX, XXXXXXX
    ),

    // layer untuk home row mod sekaligus untuk bilateral combinations
    [_LMOD] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______,
        KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX, _______, KC_J,    KC_K,    KC_L,    KC_QUOT,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_RMOD] = LAYOUT(
        _______, _______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_A,    KC_S,    KC_D,    KC_F,    _______, XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
        _______, _______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
};

bool terminate_case_modes(uint16_t keycode, const keyrecord_t *record) {
        switch (keycode) {
            // Keycodes to ignore (don't disable caps word)
            case KC_A ... KC_Z:
            case KC_1 ... KC_0:
            case KC_MINS:
            case KC_UNDS:
            case KC_BSPC:
            case A_GUI:
            case S_ALT:
            case D_CTL:
            case F_SFT:
            case J_SFT:
            case K_CTL:
            case L_ALT:
                // If mod chording disable the mods
                if (record->event.pressed && (get_mods() != 0)) {
                    return true;
                }
                break;
            default:
                if (record->event.pressed) {
                    return true;
                }
                break;
        }
        return false;
}

bool sw_win_active = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_swapper(
        &sw_win_active, KC_LALT, KC_TAB, SW_WIN,
        keycode, record
    );

    switch (keycode) {
        case NORMAL:
            layer_clear();
            return false;

        case CAPSWRD:
            if (record->event.pressed) {
                enable_caps_word();
            }
            return false;

        case SNKCASE:
            if (record->event.pressed) {
                enable_xcase_with(KC_UNDS);
            }
            return false;

        case KBBCASE:
            if (record->event.pressed) {
                enable_xcase_with(KC_MINS);
            }
            return false;

        case CMLCASE:
            if (record->event.pressed) {
                enable_xcase_with(OSM(MOD_LSFT));
            }
            return false;
    }

    if (!process_case_modes(keycode, record)) {
        return false;
    }

    return true;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case K_CTL:
        case D_CTL:
            return TAPPING_TERM - 15;
        case SPC_SYM:
            return TAPPING_TERM + 15;
        case A_GUI:
            return TAPPING_TERM + 25;
        default:
            return TAPPING_TERM;
    }
}
