#include QMK_KEYBOARD_H

#include "casemodes.h"
#include "swapper.h"

enum layers { _QWERTY, _NUMBER, _SYMBOL, _NAVIGATION, _FUNCTION, _MOUSE, _SHORTCUT };

enum combos { COMBO_TAB, COMBO_ESC, COMBO_DEL, COMBO_ENT, COMBO_BSP };

enum { TD_EQUAL_ARROW, TD_MINUS_ARROW };

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

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_EQUAL_ARROW] = ACTION_TAP_DANCE_FN(equal_arrow),
    [TD_MINUS_ARROW] = ACTION_TAP_DANCE_FN(minus_arrow)
};

enum custom_keycodes {
    NORMAL = SAFE_RANGE,

    SW_WIN,

    CAPSWRD,
    SNKCASE,
    KBBCASE,

    VSC_CLA,
    VSC_FER,
    VSC_FEL,
    VSC_MER,
    VSC_MEL
};

#define R_MOU   LT(_MOUSE, KC_R)
#define U_SYM   LT(_SYMBOL, KC_U)
#define F_NAV   LT(_NAVIGATION, KC_F)
#define J_NUM   LT(_NUMBER, KC_J)
#define Z_SCT   LT(_SHORTCUT, KC_Z)
#define V_FUN   LT(_FUNCTION, KC_V)
#define SLS_SCT LT(_SHORTCUT, KC_SLSH)
#define MOUSE   TO(_MOUSE)

#define BSP_SFT LSFT_T(KC_BSPC)
#define SPC_SFT LSFT_T(KC_SPC)
#define A_GUI   LGUI_T(KC_A)
#define S_ALT   LALT_T(KC_S)
#define D_CTL   LCTL_T(KC_D)
#define K_CTL   LCTL_T(KC_K)
#define L_ALT   LALT_T(KC_L)
#define QUO_GUI LGUI_T(KC_QUOT)

#define EQL_ARR TD(TD_EQUAL_ARROW)
#define MIN_ARR TD(TD_MINUS_ARROW)
#define UND_MIN TD(TD_UNDERSCORE_MINUS)

#define WS_LEFT LCA(KC_LEFT)
#define WS_RGHT LCA(KC_RGHT)
#define WSM_LFT MEH(KC_LEFT)
#define WSM_RGT MEH(KC_RGHT)
#define WS_DOWN LCA(KC_DOWN)

#define VSC_NEW MEH(KC_N)
#define VSC_BAK LCA(KC_MINS)

#define UNDO    C(KC_Z)
#define CUT     C(KC_X)
#define COPY    C(KC_C)
#define PASTE   C(KC_V)
#define REDO    C(KC_Y)
#define SEL_ALL C(KC_A)
#define SAVE    C(KC_S)
#define FIND    C(KC_F)

const uint16_t PROGMEM tab_combo[] = { S_ALT, D_CTL, COMBO_END };
const uint16_t PROGMEM esc_combo[] = { KC_W, KC_E, COMBO_END };
const uint16_t PROGMEM del_combo[] = { KC_X, KC_C, COMBO_END };
const uint16_t PROGMEM ent_combo[] = { L_ALT, K_CTL, COMBO_END };
const uint16_t PROGMEM bsp_combo[] = { KC_O, KC_I, COMBO_END };

combo_t key_combos[COMBO_COUNT] = {
    [COMBO_TAB] = COMBO(tab_combo, KC_TAB),
    [COMBO_ESC] = COMBO(esc_combo, KC_ESC),
    [COMBO_DEL] = COMBO(del_combo, KC_DEL),
    [COMBO_ENT] = COMBO(ent_combo, KC_ENT),
    [COMBO_BSP] = COMBO(bsp_combo, KC_BSPC),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_Q,    KC_W,    KC_E,    R_MOU,   KC_T,    KC_Y,    U_SYM,   KC_I,    KC_O,    KC_P,
        A_GUI,   S_ALT,   D_CTL,   F_NAV,   KC_G,    KC_H,    J_NUM,   K_CTL,   L_ALT,   QUO_GUI,
        Z_SCT,   KC_X,    KC_C,    V_FUN,   KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  SLS_SCT,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, BSP_SFT, SPC_SFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [_NUMBER] = LAYOUT(
        KC_5,    KC_4,    KC_3,    KC_2,    KC_1,    _______, _______, _______, _______, _______,
        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, _______, KC_LCTL, KC_LALT, KC_LGUI,
        KC_GRV,  KC_BSLS, KC_SCLN, KC_LBRC, KC_RBRC, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_SYMBOL] = LAYOUT(
        KC_EXLM, KC_AT,   KC_HASH, KC_PERC, KC_CIRC, _______, _______, KC_LCTL, KC_LALT, KC_LGUI,
        KC_DLR,  KC_AMPR, MIN_ARR, KC_UNDS, KC_SCLN, _______, _______, _______, _______, _______,
        KC_ASTR, KC_SLSH, EQL_ARR, KC_LT,   KC_GT,   _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_NAVIGATION] = LAYOUT(
        _______, _______, _______, _______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  MOUSE,
        KC_LGUI, KC_LALT, KC_LCTL, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, SW_WIN,
        _______, _______, _______, _______, _______, WSM_LFT, WS_LEFT, WS_RGHT, WSM_RGT, WS_DOWN,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_FUNCTION] = LAYOUT(
        _______, _______, _______, _______, _______, KC_PSCR, KC_F1,   KC_F2,   KC_F3,   KC_F4,
        _______, _______, _______, _______, _______, KC_INS,  KC_F5,   KC_F6,   KC_F7,   KC_F8,
        KC_LGUI, KC_LALT, KC_LCTL, _______, _______, KC_CAPS, KC_F9,   KC_F10,  KC_F11,  KC_F12,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_MOUSE] = LAYOUT(
        KC_LGUI, KC_LALT, KC_LCTL, _______, _______, KC_WH_U, KC_WH_L, KC_MS_U, KC_WH_R, NORMAL,
        SEL_ALL, SAVE,    _______, FIND,    _______, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, SW_WIN,
        UNDO,    CUT,     COPY,    PASTE,   REDO,    _______, _______, _______, _______, _______,
        _______, _______, KC_BTN2, _______, KC_BTN1, KC_BTN1, _______, KC_BTN2, _______, _______
    ),

    [_SHORTCUT] = LAYOUT(
        RESET,   KC_MUTE, KC_MNXT, KC_VOLU, KC_BRIU, VSC_NEW, KC_F12,  VSC_BAK, _______, VSC_CLA,
        _______, _______, KC_MPLY, KC_VOLD, KC_BRID, VSC_MEL, VSC_FEL, VSC_FER, VSC_MER, _______,
        _______, _______, _______, _______, _______, CAPSWRD, SNKCASE, KBBCASE, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
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
        case SPC_SFT:
        case BSP_SFT:
            return TAPPING_TERM + 15;
        case A_GUI:
            return TAPPING_TERM + 25;
        default:
            return TAPPING_TERM;
    }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case A_GUI:
        case S_ALT:
            return false;
        default:
            return true;
    }
}
