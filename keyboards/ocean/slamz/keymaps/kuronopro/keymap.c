#include QMK_KEYBOARD_H

#include "casemodes.h"
#include "swapper.h"

enum layers { _QWERTY, _SYMBOL, _NUMBER, _NAVIGATION, _CODE, _FUNCTION, _MOUSE };

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
};

// fungsi untuk TD_EQL_ARR

void equal_arrow(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 2:
            tap_code(KC_EQL);
            tap_code16(KC_GT);
            break;
        default:
            tap_code(KC_EQL);
            break;
    }

    reset_tap_dance(state);
}

// fungsi untuk TD_MIN_ARR

void minus_arrow(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 2:
            tap_code(KC_MINS);
            tap_code16(KC_GT);
            break;
        default:
            tap_code(KC_MINS);
            break;
    }

    reset_tap_dance(state);
}

// fungsi untuk TD_PHP_OPN

void php_open(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 2:
            tap_code16(KC_LT);
            tap_code16(KC_QUES);
            tap_code(KC_EQL);
            break;
        case 3:
            tap_code16(KC_LT);
            tap_code16(KC_QUES);
            tap_code(KC_P);
            tap_code(KC_H);
            tap_code(KC_P);
        default:
            tap_code16(KC_LT);
            break;
    }

    reset_tap_dance(state);
}

// fungsi untuk TD_PHP_CLS

void php_close(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 2:
            tap_code16(KC_QUES);
            tap_code16(KC_GT);
            break;
        default:
            tap_code16(KC_GT);
            break;
    }

    reset_tap_dance(state);
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_EQL_ARR] = ACTION_TAP_DANCE_FN(equal_arrow),
    [TD_MIN_ARR] = ACTION_TAP_DANCE_FN(minus_arrow),
    [TD_PHP_OPN] = ACTION_TAP_DANCE_FN(php_open),
    [TD_PHP_CLS] = ACTION_TAP_DANCE_FN(php_close),
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
    SW_WIN,

    // vscode tutup semua editor
    VSC_CLA,
    // vscode fokus editor kanan
    VSC_FER,
    // vscode fokus editor kiri
    VSC_FEL,
    // vscode pindah ke editor kanan
    VSC_MER,
    // vscode pindah ke editor kiri
    VSC_MEL
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
#define Z_CODE  LT(_CODE, KC_Z)

// home row mod
#define A_GUI   LGUI_T(KC_A) // TD(TD_A_GUI)
#define S_ALT   LALT_T(KC_S) // TD(TD_S_ALT)
#define D_CTL   LCTL_T(KC_D) // TD(TD_D_CTL)
#define F_SFT   LSFT_T(KC_F) // TD(TD_F_SFT)
#define J_SFT   LSFT_T(KC_J) // TD(TD_J_SFT)
#define K_CTL   LCTL_T(KC_K) // TD(TD_K_CTL)
#define L_ALT   LALT_T(KC_L) // TD(TD_L_ALT)
#define QUO_GUI LGUI_T(KC_QUOT) // TD(TD_QUO_GUI)

// tap dance
#define EQL_ARR TD(TD_EQL_ARR)
#define MIN_ARR TD(TD_MIN_ARR)
#define LT_PHP  TD(TD_PHP_OPN)
#define GT_PHP  TD(TD_PHP_CLS)

// shortcut vscode
#define VSC_NEW MEH(KC_N)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        A_GUI,   S_ALT,   D_CTL,   F_SFT,   KC_G,    KC_H,    J_SFT,   K_CTL,   L_ALT,   QUO_GUI,
        Z_CODE,  KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
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
        XXXXXXX, XXXXXXX, _______, XXXXXXX, _______, KC_0,    XXXXXXX, _______, XXXXXXX, XXXXXXX
    ),

    [_NAVIGATION] = LAYOUT(
        KC_ESC,  SW_TABL, SW_TABR, SW_WIN,  XXXXXXX, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  MOUSE,
        KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_INS,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_DEL,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, CAPSWRD, SNKCASE, KBBCASE, CMLCASE, KC_CAPS,
        XXXXXXX, XXXXXXX, _______, XXXXXXX, _______, _______, XXXXXXX, _______, XXXXXXX, XXXXXXX
    ),

    [_CODE] = LAYOUT(
        _______, _______, _______, _______, _______, VSC_NEW, _______, _______, _______, VSC_CLA,
        _______, _______, _______, _______, _______, VSC_MEL, VSC_FEL, VSC_FER, VSC_MER, _______,
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
};

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

        case VSC_CLA:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_K);
                tap_code(KC_W);
            } else {
                unregister_code(KC_LCTL);
            }
            break;
        case VSC_FEL:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_K);
                tap_code(KC_LEFT);
            } else {
                unregister_code(KC_LCTL);
            }
            break;
        case VSC_FER:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_K);
                tap_code(KC_RGHT);
            } else {
                unregister_code(KC_LCTL);
            }
            break;
        case VSC_MEL:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_K);
                register_code(KC_LSFT);
                tap_code(KC_LEFT);
            } else {
                unregister_code(KC_LCTL);
                unregister_code(KC_LSFT);
            }
            break;
        case VSC_MER:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_K);
                register_code(KC_LSFT);
                tap_code(KC_RGHT);
            } else {
                unregister_code(KC_LCTL);
                unregister_code(KC_LSFT);
            }
            break;
    }

    if (!process_case_modes(keycode, record)) {
        return false;
    }

    return true;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case S_ALT:
        case SPC_SYM:
            return TAPPING_TERM + 15;
        case A_GUI:
            return TAPPING_TERM + 25;
        default:
            return TAPPING_TERM;
    }
}
