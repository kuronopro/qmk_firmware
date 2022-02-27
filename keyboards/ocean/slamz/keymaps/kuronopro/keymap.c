#include QMK_KEYBOARD_H

#include "casemodes.h"

enum layers {
    _BASE,
    _NUMBER_SYMBOL,
    _NAVIGATION,
    _MOUSE,
    _FUNCTION,
};

enum custom_keycodes {
    CAPSWRD = SAFE_RANGE,
    SNKCASE,
    KBBCASE
};

enum combos {
    COMBO_ESC,
    COMBO_TAB,
    COMBO_DEL,
    COMBO_ENT
};

enum {
    TD_EQUAL_ARROW,
    TD_MINUS_ARROW
};

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

#define A_CTL   LCTL_T(KC_A)
#define S_OPT   LOPT_T(KC_S)
#define D_CMD   LCMD_T(KC_D)
#define K_CMD   LCMD_T(KC_K)
#define L_OPT   LOPT_T(KC_L)
#define QUO_CTL LCTL_T(KC_QUOT)
#define BSP_SFT LSFT_T(KC_BSPC)
#define SPC_SFT LSFT_T(KC_SPC)

#define F_NAV   LT(_NAVIGATION, KC_F)
#define J_NSYM  LT(_NUMBER_SYMBOL, KC_J)
#define TAB_MOU LT(_MOUSE, KC_TAB)
#define ENT_FUN LT(_FUNCTION, KC_ENT)

#define SEL_ALL G(KC_A)
#define SAVE    G(KC_S)
#define UNDO    G(KC_Z)
#define CUT     G(KC_X)
#define COPY    G(KC_C)
#define PASTE   G(KC_V)
#define REDO    G(S(KC_Z))
#define FIND    G(KC_F)

#define CMDK    G(KC_K)

#define MIN_ARR TD(TD_MINUS_ARROW)
#define EQL_ARR TD(TD_EQUAL_ARROW)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        A_CTL,   S_OPT,   D_CMD,   F_NAV,   KC_G,    KC_H,    J_NSYM,  K_CMD,   L_OPT,   QUO_CTL,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
        XXXXXXX, XXXXXXX, TAB_MOU, XXXXXXX, BSP_SFT, SPC_SFT, XXXXXXX, ENT_FUN, XXXXXXX, XXXXXXX
    ),

    [_NUMBER_SYMBOL] = LAYOUT(
        KC_LBRC, KC_7,    KC_8,    KC_9,    KC_RBRC, _______, _______, _______, _______, _______,
        KC_SCLN, KC_4,    KC_5,    KC_6,    MIN_ARR, _______, _______, KC_LCMD, KC_LOPT, KC_LCTL,
        KC_0,    KC_1,    KC_2,    KC_3,    EQL_ARR, _______, _______, _______, _______, CMDK,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_NAVIGATION] = LAYOUT(
        _______, _______, _______, _______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_ESC, 
        KC_LCTL, KC_LOPT, KC_LCMD, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_DEL, 
        CMDK,    _______, _______, _______, _______, _______, _______, _______, KC_GRV,  KC_BSLS, 
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_MOUSE] = LAYOUT(
        KC_LCTL, KC_LOPT, KC_LCMD, KC_LSFT, _______, KC_WH_U, KC_WH_L, KC_MS_U, KC_WH_R, KC_ESC,
        SEL_ALL, SAVE,    _______, FIND,    _______, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, _______,
        UNDO,    CUT,     COPY,    PASTE,   REDO,    _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, KC_BTN1, _______, KC_BTN2, _______, _______

    ),

    [_FUNCTION] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   RESET,   _______, CAPSWRD, SNKCASE, KBBCASE,
        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, KC_F19,  KC_LCMD, KC_LOPT, KC_LCTL,
        KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};

const uint16_t PROGMEM esc_combo[] = { KC_W, KC_E, COMBO_END };
const uint16_t PROGMEM tab_combo[] = { S_OPT, D_CMD, COMBO_END };
const uint16_t PROGMEM del_combo[] = { KC_O, KC_I, COMBO_END };
const uint16_t PROGMEM ent_combo[] = { L_OPT, K_CMD, COMBO_END };

combo_t key_combos[COMBO_COUNT] = {
    [COMBO_ESC] = COMBO(esc_combo, KC_ESC),
    [COMBO_TAB] = COMBO(tab_combo, KC_TAB),
    [COMBO_DEL] = COMBO(del_combo, KC_DEL),
    [COMBO_ENT] = COMBO(ent_combo, KC_ENT),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
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
    }

    if (!process_case_modes(keycode, record)) {
        return false;
    }

    return true;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case J_NSYM:
            return TAPPING_TERM - 50;
        case S_OPT:
        case BSP_SFT:
        case SPC_SFT:
            return TAPPING_TERM + 15;
        case A_CTL:
            return TAPPING_TERM + 30;
        default:
            return TAPPING_TERM;
    }
}