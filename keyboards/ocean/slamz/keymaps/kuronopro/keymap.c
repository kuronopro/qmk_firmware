#include QMK_KEYBOARD_H

#include "casemodes.h"
#include "swapper.h"

enum layers {_QWERTY, _COLEMAK, _LOWER, _RAISE, _NUMBER, _SYMBOL, _NAVIGATION, _FUNCTION, _MOUSE, _SHORTCUT };

enum combos { TAB_QWER, TAB_CLMK, ESC_QWER, ESC_CLMK, DEL, ENT_QWER, ENT_CLMK, BSP_QWER, BSP_CLMK, C_BSP_QWER, C_BSP_CLMK };

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
    QWERTY = SAFE_RANGE,
    COLEMAK,
    NORMAL,

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

#define BSP_SFT LSFT_T(KC_BSPC)
#define SPC_SFT LSFT_T(KC_SPC)
#define U_NUM   LT(_NUMBER, KC_U)
#define F_NAV   LT(_NAVIGATION, KC_F)
#define J_SYM   LT(_SYMBOL, KC_J)
#define Z_SCT   LT(_SHORTCUT, KC_Z)
#define V_MOU   LT(_MOUSE, KC_V)
#define M_FUN   LT(_FUNCTION, KC_M)
#define SLS_SCT LT(_SHORTCUT, KC_SLSH)
#define L_NUM   LT(_NUMBER, KC_L)
#define T_NAV   LT(_NAVIGATION, KC_T)
#define N_SYM   LT(_SYMBOL, KC_N)
#define MOUSE   TO(_MOUSE)

#define A_GUI   LGUI_T(KC_A)
#define S_ALT   LALT_T(KC_S)
#define D_CTL   LCTL_T(KC_D)
#define K_CTL   LCTL_T(KC_K)
#define L_ALT   LALT_T(KC_L)
#define QUO_GUI LGUI_T(KC_QUOT)
#define R_ALT   LALT_T(KC_R)
#define S_CTL   LCTL_T(KC_S)
#define E_CTL   LCTL_T(KC_E)
#define I_ALT   LALT_T(KC_I)
#define O_GUI   LGUI_T(KC_O)

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

const uint16_t PROGMEM tab_qwer_combo[] = { S_ALT, D_CTL, COMBO_END };
const uint16_t PROGMEM tab_clmk_combo[] = { R_ALT, S_CTL, COMBO_END };
const uint16_t PROGMEM esc_qwer_combo[] = { KC_W, KC_E, COMBO_END };
const uint16_t PROGMEM esc_clmk_combo[] = { KC_W, KC_F, COMBO_END };
const uint16_t PROGMEM del_combo[] = { KC_X, KC_C, COMBO_END };
const uint16_t PROGMEM ent_qwer_combo[] = { K_CTL, L_ALT, COMBO_END };
const uint16_t PROGMEM ent_clmk_combo[] = { E_CTL, I_ALT, COMBO_END };
const uint16_t PROGMEM bsp_qwer_combo[] = { KC_I, KC_O, COMBO_END };
const uint16_t PROGMEM bsp_clmk_combo[] = { KC_U, KC_Y, COMBO_END };

combo_t key_combos[COMBO_COUNT] = {
    [TAB_QWER] = COMBO(tab_qwer_combo, KC_TAB),
    [TAB_CLMK] = COMBO(tab_clmk_combo, KC_TAB),
    [ESC_QWER] = COMBO(esc_qwer_combo, KC_ESC),
    [ESC_CLMK] = COMBO(esc_clmk_combo, KC_ESC),
    [DEL] = COMBO(del_combo, KC_DEL),
    [ENT_QWER] = COMBO(ent_qwer_combo, KC_ENT),
    [ENT_CLMK] = COMBO(ent_clmk_combo, KC_ENT),
    [BSP_QWER] = COMBO(bsp_qwer_combo, KC_BSPC),
    [BSP_CLMK] = COMBO(bsp_clmk_combo, KC_BSPC)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    U_NUM,   KC_I,    KC_O,    KC_P,
        A_GUI,   S_ALT,   D_CTL,   F_NAV,   KC_G,    KC_H,    J_SYM,   K_CTL,   L_ALT,   QUO_GUI,
        Z_SCT,   KC_X,    KC_C,    V_MOU,   KC_B,    KC_N,    M_FUN,   KC_COMM, KC_DOT,  SLS_SCT,
        XXXXXXX, XXXXXXX, KC_TAB,  XXXXXXX, BSP_SFT, SPC_SFT, XXXXXXX, KC_ENT,  XXXXXXX, XXXXXXX
    ),

    [_COLEMAK] = LAYOUT(
        KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    L_NUM,   KC_U,    KC_Y,    KC_QUOT,
        A_GUI,   R_ALT,   S_CTL,   T_NAV,   KC_D,    KC_H,    N_SYM,   E_CTL,   I_ALT,   O_GUI,
        Z_SCT,   KC_X,    KC_C,    V_MOU,   KC_B,    KC_K,    M_FUN,   KC_COMM, KC_DOT,  SLS_SCT,
        XXXXXXX, XXXXXXX, KC_TAB,  XXXXXXX, BSP_SFT, SPC_SFT, XXXXXXX, KC_ENT,  XXXXXXX, XXXXXXX
    ),

    [_NUMBER] = LAYOUT(
        KC_GRV,  KC_7,    KC_8,    KC_9,    KC_BSLS, _______, _______, KC_LCTL, KC_LALT, KC_LGUI,
        _______, KC_4,    KC_5,    KC_6,    _______, _______, _______, _______, _______, _______,
        KC_0,    KC_1,    KC_2,    KC_3,    _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_SYMBOL] = LAYOUT(
        KC_LPRN, KC_LBRC, KC_COLN, KC_RBRC, KC_RPRN, _______, _______, _______, _______, _______,
        KC_DLR,  KC_AMPR, MIN_ARR, KC_UNDS, KC_SCLN, _______, _______, KC_LCTL, KC_LALT, KC_LGUI,
        KC_LCBR, KC_LT,   EQL_ARR, KC_GT,   KC_RCBR, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_FUNCTION] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______, _______, _______, _______,
        KC_F6,   KC_7,    KC_F8,   KC_F9,   KC_F10,  _______, _______, _______, _______, _______,
        KC_F11,  KC_F12,  KC_PSCR, KC_INS,  KC_CAPS, _______, _______, KC_LCTL, KC_LALT, KC_LGUI,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_NAVIGATION] = LAYOUT(
        _______, _______, _______, _______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  MOUSE,
        KC_LGUI, KC_LALT, KC_LCTL, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, SW_WIN,
        _______, _______, _______, _______, _______, WSM_LFT, WS_LEFT, WS_RGHT, WSM_RGT, WS_DOWN,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_MOUSE] = LAYOUT(
        UNDO,    CUT,     COPY,    PASTE,   REDO,    KC_WH_U, KC_WH_L, KC_MS_U, KC_WH_R, NORMAL,
        SEL_ALL, SAVE,    _______, FIND,    _______, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, SW_WIN,
        KC_LGUI, KC_LALT, KC_LCTL, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, KC_BTN2, _______, KC_BTN1, KC_BTN1, _______, KC_BTN2, _______, _______
    ),

    [_SHORTCUT] = LAYOUT(
        RESET,   KC_MUTE, KC_MNXT, KC_VOLU, KC_BRIU, VSC_NEW, KC_F12,  VSC_BAK, _______, VSC_CLA,
        _______, _______, KC_MPLY, KC_VOLD, KC_BRID, VSC_MEL, VSC_FEL, VSC_FER, VSC_MER, _______,
        COLEMAK, _______, _______, _______, _______, CAPSWRD, SNKCASE, KBBCASE, _______, QWERTY,
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
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;

        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;

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
