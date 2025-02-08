#include QMK_KEYBOARD_H

#include "features/casemodes.h"
#include "features/autocorrection.h"
#include "features/swapper.h"

enum layers { _QWERTY, _SYMBOL, _NUMBER, _NAVIGATION, _FUNCTION, _MOUSE };

enum custom_keycodes { NORMAL = SAFE_RANGE, SNKCASE, KBBCASE, SW_WIN };

enum { TD_LT_PHP, TD_GT_PHP };

void lt_php(tap_dance_state_t *state, void *user_data);
void gt_php(tap_dance_state_t *state, void *user_data);

tap_dance_action_t tap_dance_actions[] = {
    [TD_LT_PHP] = ACTION_TAP_DANCE_FN(lt_php),
    [TD_GT_PHP] = ACTION_TAP_DANCE_FN(gt_php),
};

#define CAPSWRD CW_TOGG
#define RESET   QK_BOOT

#define LT_PHP  TD(TD_LT_PHP)
#define GT_PHP  TD(TD_GT_PHP)

#define TAB_LFT G(S(KC_LBRC))
#define TAB_RGT G(S(KC_RBRC))
#define SPC_LFT C(KC_LEFT)
#define SPC_RGT C(KC_RGHT)
#define APPWNDW C(KC_DOWN)
#define MSNCTRL C(KC_UP)
#define BACK    G(KC_LBRC)
#define FWD     G(KC_RBRC)

#define A_CTL   LCTL_T(KC_A)
#define S_OPT   LALT_T(KC_S)
#define D_CMD   LGUI_T(KC_D)
#define K_CMD   RGUI_T(KC_K)
#define L_OPT   LALT_T(KC_L)
#define QUO_CTL RCTL_T(KC_QUOT)
#define BSP_SFT LSFT_T(KC_BSPC)
#define SPC_SFT RSFT_T(KC_SPC)

#define Q_MOUS  LT(_MOUSE, KC_Q)
#define F_NAV   LT(_NAVIGATION, KC_F)
#define G_NUM   LT(_NUMBER, KC_G)
#define H_FUN   LT(_FUNCTION, KC_H)
#define J_SYM   LT(_SYMBOL, KC_J)
#define MOUSE   TO(_MOUSE)

#define TO_SYM  TO(_SYMBOL)
#define TO_NUM  TO(_NUMBER)
#define TO_NAV  TO(_NAVIGATION)
#define TO_FUN  TO(_FUNCTION)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_kuronopro(
        Q_MOUS,  KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        A_CTL,   S_OPT,   D_CMD,   F_NAV,   G_NUM,   H_FUN,   J_SYM,   K_CMD,   L_OPT,   QUO_CTL,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
        KC_HYPR, TO_FUN,           KC_TAB,  BSP_SFT, SPC_SFT, KC_ENT,           TO_NAV,  NORMAL
    ),

    [_SYMBOL] = LAYOUT_kuronopro(
        KC_LPRN, KC_LBRC, KC_COLN, KC_RBRC, KC_RPRN, _______, KC_CIRC, KC_EXLM, KC_AT,   KC_HASH,
        KC_DLR,  KC_DQUO, KC_MINS, KC_UNDS, KC_SCLN, _______, _______, KC_RCMD, KC_LOPT, KC_RCTL,
        KC_LCBR, LT_PHP,  KC_EQL,  GT_PHP,  KC_RCBR, _______, _______, KC_AMPR, KC_PERC, KC_QUES,
        _______, _______,          KC_GRV,  KC_BSLS, _______, _______,          _______, _______
    ),

    [_NUMBER] = LAYOUT_kuronopro(
        _______, _______, _______, _______, _______, KC_7,    KC_8,    KC_9,    KC_COLN, KC_EQL,
        KC_LCTL, KC_LOPT, KC_LCMD, _______, _______, KC_4,    KC_5,    KC_6,    KC_PLUS, KC_ASTR,
        _______, _______, _______, _______, _______, KC_1,    KC_2,    KC_3,    KC_MINS, KC_SLSH,
        _______, _______,          _______, _______, KC_0,    KC_DOT,           _______, _______
    ),

    [_NAVIGATION] = LAYOUT_kuronopro(
        KC_ESC,  TAB_LFT, TAB_RGT, MOUSE,   _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  _______,
        KC_LCTL, KC_LOPT, KC_LCMD, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_DEL,
        SW_WIN,  BACK,    FWD,     _______, _______, _______, _______, _______, _______, _______,
        _______, _______,          _______, _______, _______, _______,          _______, _______
    ),

    [_FUNCTION] = LAYOUT_kuronopro(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______, CAPSWRD, SNKCASE, KBBCASE,
        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, _______, KC_RCMD, KC_LOPT, KC_RCTL,
        KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  _______, _______, _______, _______, RESET,
        _______, _______,          _______, KC_F19,  _______, _______,          _______, _______
    ),

    [_MOUSE] = LAYOUT_kuronopro(
        _______, SPC_LFT, APPWNDW, MSNCTRL, SPC_RGT, KC_WH_U, KC_WH_L, KC_MS_U, KC_WH_R, _______,
        _______, KC_LCTL, KC_LOPT, KC_LCMD, KC_LSFT, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, _______,
        _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,
        _______, _______,          KC_BTN2, KC_BTN1, KC_BTN1, KC_BTN2,          _______, _______
    ),
};

void lt_php(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 2:
            tap_code16(KC_LT);
            tap_code16(KC_QUES);
            break;
        default:
            tap_code16(KC_LT);
            break;
    }

    reset_tap_dance(state);
}

void gt_php(tap_dance_state_t *state, void *user_data) {
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

bool sw_win_active = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_autocorrection(keycode, record)) {
        return false;
    }

    update_swapper(&sw_win_active, KC_LCMD, KC_TAB, SW_WIN, keycode, record);

    switch (keycode) {
        case NORMAL:
            layer_clear();
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
        case A_CTL:
        case S_OPT:
        case L_OPT:
            return TAPPING_TERM + 60;
        case SPC_SFT:
            return TAPPING_TERM + 10;
        case G_NUM:
        case J_SYM:
            return TAPPING_TERM - 50;
        default:
            return TAPPING_TERM;
    }
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case G_NUM:
        case J_SYM:
        case SPC_SFT:
            return true;
        default:
            return false;
    }
}

enum combos {
    MCOM_MINS,
    COMDOT_SCLN
};

const uint16_t PROGMEM mcom_combo[] = {KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM comdot_combo[] = {KC_COMM, KC_DOT, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [MCOM_MINS] = COMBO(mcom_combo, KC_MINS),
    [COMDOT_SCLN] = COMBO(comdot_combo, KC_SCLN)
};
