#include QMK_KEYBOARD_H

#include "casemodes.h"
#include "swapper.h"

enum layers { _QWERTY, _NUMBER, _SYMBOL, _NAVIGATION, _FUNCTION, _MOUSE, _SHORTCUT };

enum combos { COMBO_ESC, COMBO_TAB, COMBO_DEL, COMBO_ENT };

enum { TD_EQUAL_ARROW, TD_MINUS_ARROW, TD_LT_PHP, TD_GT_PHP };

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

void lt_php(qk_tap_dance_state_t *state, void *user_data) {
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

void gt_php(qk_tap_dance_state_t *state, void *user_data) {
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
    [TD_EQUAL_ARROW] = ACTION_TAP_DANCE_FN(equal_arrow),
    [TD_MINUS_ARROW] = ACTION_TAP_DANCE_FN(minus_arrow),
    [TD_LT_PHP]      = ACTION_TAP_DANCE_FN(lt_php),
    [TD_GT_PHP]      = ACTION_TAP_DANCE_FN(gt_php)
};

enum custom_keycodes {
    NORMAL = SAFE_RANGE,

    SW_WIN,

    CAPSWRD,
    SNKCASE,
    ANYCASE,

    VSC_CLA,
    VSC_FER,
    VSC_FEL,
    VSC_FEU,
    VSC_FED,
    VSC_MER,
    VSC_MEL,
    VSC_MEU,
    VSC_MED
};

#define F_NAV   LT(_NAVIGATION, KC_F)
#define J_SYM   LT(_SYMBOL, KC_J)
#define V_NUM   LT(_NUMBER, KC_V)
#define M_FUN   LT(_FUNCTION, KC_M)
#define Q_MOU   LT(_MOUSE, KC_Q)
#define QUO_SCT LT(_SHORTCUT, KC_QUOT)
#define MOUSE   TO(_MOUSE)

#define T_NAV   LT(_NAVIGATION, KC_T)
#define N_SYM   LT(_SYMBOL, KC_N)

#define D_CTL   LCTL_T(KC_D)
#define K_CTL   LCTL_T(KC_K)
#define Z_GUI   LGUI_T(KC_Z)
#define X_ALT   LALT_T(KC_X)
#define C_CTL   LCTL_T(KC_C)
#define COM_CTL LCTL_T(KC_COMM)
#define DOT_ALT LALT_T(KC_DOT)
#define SLS_GUI LGUI_T(KC_SLSH)
#define BSP_SFT LSFT_T(KC_BSPC)
#define SPC_SFT LSFT_T(KC_SPC)
#define N0_SFT  LSFT_T(KC_0)
#define BSL_SFT LSFT_T(KC_BSLS)

#define EQL_ARR TD(TD_EQUAL_ARROW)
#define MIN_ARR TD(TD_MINUS_ARROW)
#define LT_PHP  TD(TD_LT_PHP)
#define GT_PHP  TD(TD_GT_PHP)

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

const uint16_t PROGMEM esc_combo[] = { KC_W, KC_E, COMBO_END };
const uint16_t PROGMEM tab_combo[] = { KC_S, D_CTL, COMBO_END };
const uint16_t PROGMEM del_combo[] = { KC_O, KC_I, COMBO_END };
const uint16_t PROGMEM ent_combo[] = { KC_L, K_CTL, COMBO_END };

combo_t key_combos[COMBO_COUNT] = {
    [COMBO_ESC] = COMBO(esc_combo, KC_ESC),
    [COMBO_TAB] = COMBO(tab_combo, KC_TAB),
    [COMBO_DEL] = COMBO(del_combo, KC_DEL),
    [COMBO_ENT] = COMBO(ent_combo, KC_ENT),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        Q_MOU,   KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    D_CTL,   F_NAV,   KC_G,    KC_H,    J_SYM,   K_CTL,   KC_L,    QUO_SCT,
        Z_GUI,   X_ALT,   C_CTL,   V_NUM,   KC_B,    KC_N,    M_FUN,   COM_CTL, DOT_ALT, SLS_GUI,
        XXXXXXX, XXXXXXX, KC_TAB,  XXXXXXX, BSP_SFT, SPC_SFT, XXXXXXX, KC_ENT,  XXXXXXX, XXXXXXX
    ),

    [_NUMBER] = LAYOUT(
        _______, _______, _______, _______, _______, KC_7,    KC_8,    KC_9,    KC_COLN, KC_EQL,
        _______, _______, _______, _______, _______, KC_4,    KC_5,    KC_6,    KC_PLUS, KC_ASTR,
        KC_LGUI, KC_LALT, KC_LCTL, _______, _______, KC_1,    KC_2,    KC_3,    KC_MINS, KC_SLSH,
        _______, _______, _______, _______, _______, N0_SFT,  _______, KC_DOT,  _______, _______
    ),

    [_SYMBOL] = LAYOUT(
        KC_LPRN, KC_LBRC, KC_COLN, KC_RBRC, KC_RPRN, _______, _______, KC_EXLM, KC_AT,   KC_CIRC,
        KC_DLR,  KC_DQUO, MIN_ARR, KC_UNDS, KC_SCLN, _______, _______, KC_LCTL, KC_AMPR, KC_HASH,
        KC_LCBR, LT_PHP,  EQL_ARR, GT_PHP,  KC_RCBR, _______, _______, KC_PERC, KC_LALT, KC_LGUI,
        _______, _______, KC_GRV,  _______, BSL_SFT, _______, _______, _______, _______, _______
    ),

    [_NAVIGATION] = LAYOUT(
        KC_ESC,  _______, _______, _______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_ESC,
        SW_WIN,  _______, KC_LCTL, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, SW_WIN,
        KC_LGUI, KC_LALT, _______, _______, _______, KC_TAB,  KC_ENT,  _______, KC_APP,  KC_DEL,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_FUNCTION] = LAYOUT(
        KC_F11,  KC_F12,  _______,  KC_INS, KC_PSCR, _______, _______, _______, _______, _______,
        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, _______, _______, _______, KC_CAPS,
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______, KC_LCTL, KC_LALT, KC_LGUI,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_MOUSE] = LAYOUT(
        KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______, KC_WH_U, KC_WH_L, KC_MS_U, KC_WH_R, KC_ESC,
        SEL_ALL, SAVE,    _______, FIND,    _______, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, SW_WIN,
        UNDO,    CUT,     COPY,    PASTE,   REDO,    _______, _______, _______, _______, NORMAL,
        _______, _______, KC_BTN2, _______, KC_BTN1, KC_BTN1, _______, KC_BTN2, _______, _______
    ),

    [_SHORTCUT] = LAYOUT(
        RESET,   KC_MUTE, KC_MNXT, KC_VOLU, KC_BRIU, VSC_NEW, KC_F12,  VSC_BAK, VSC_CLA, _______,
        _______, _______, KC_MPLY, KC_VOLD, KC_BRID, VSC_FEL, VSC_FED, VSC_FEU, VSC_FER, _______,
        _______, ANYCASE, SNKCASE, CAPSWRD, _______, VSC_MEL, VSC_MED, VSC_MEU, VSC_MER, MOUSE,
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

        case ANYCASE:
            if (record->event.pressed) {
                enable_xcase();
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
        case VSC_FEU:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_K);
                tap_code(KC_UP);
            } else {
                unregister_code(KC_LCTL);
            }
            break;
        case VSC_FED:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_K);
                tap_code(KC_DOWN);
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
        case VSC_MEU:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_K);
                register_code(KC_LSFT);
                tap_code(KC_UP);
            } else {
                unregister_code(KC_LCTL);
                unregister_code(KC_LSFT);
            }
            break;
        case VSC_MED:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_K);
                register_code(KC_LSFT);
                tap_code(KC_DOWN);
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
