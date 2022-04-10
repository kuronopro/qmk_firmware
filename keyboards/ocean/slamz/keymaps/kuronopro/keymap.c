#include QMK_KEYBOARD_H

#include "features/casemodes.h"
#include "features/autocorrection.h"
#include "features/select_word.h"

enum layers {
    _QWERTY,
    _COLEMAK,
    _SYMBOL,
    _NUMBER,
    _NAVIGATION,
    _FUNCTION,
    _MOUSE
};

enum custom_keycodes {
    NORMAL = SAFE_RANGE,
    QWERTY,
    COLEMAK,
    CAPSWRD,
    SNKCASE,
    KBBCASE,
    SELWORD
};

enum combos {
    COMBO_ESC,
    COMBO_TAB,
    COMBO_DEL,
    COMBO_ENT,
    COMBO_ESC_COLEMAK,
    COMBO_TAB_COLEMAK,
    COMBO_DEL_COLEMAK,
    COMBO_ENT_COLEMAK
};

enum {
    TD_EQUAL_ARROW,
    TD_MINUS_ARROW,
    TD_LT_PHP,
    TD_GT_PHP,
    TD_VSCODE_EDITOR_LEFT,
    TD_VSCODE_EDITOR_RIGHT,
    TD_VSCODE_EDITOR_UP,
    TD_VSCODE_EDITOR_DOWN
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

void vscode_editor_left(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 2:
            register_code(KC_LCMD);
            tap_code(KC_K);
            register_code(KC_LCTL);
            tap_code(KC_LEFT);
            unregister_code(KC_LCMD);
            unregister_code(KC_LCTL);
            break;
        default:
            register_code(KC_LCMD);
            tap_code(KC_K);
            tap_code(KC_LEFT);
            unregister_code(KC_LCMD);
            break;
    }

    reset_tap_dance(state);
}

void vscode_editor_right(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 2:
            register_code(KC_LCMD);
            tap_code(KC_K);
            register_code(KC_LCTL);
            tap_code(KC_RGHT);
            unregister_code(KC_LCMD);
            unregister_code(KC_LCTL);
            break;
        default:
            register_code(KC_LCMD);
            tap_code(KC_K);
            tap_code(KC_RGHT);
            unregister_code(KC_LCMD);
            break;
    }

    reset_tap_dance(state);
}

void vscode_editor_up(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 2:
            register_code(KC_LCMD);
            tap_code(KC_K);
            register_code(KC_LCTL);
            tap_code(KC_UP);
            unregister_code(KC_LCMD);
            unregister_code(KC_LCTL);
            break;
        default:
            register_code(KC_LCMD);
            tap_code(KC_K);
            tap_code(KC_UP);
            unregister_code(KC_LCMD);
            break;
    }

    reset_tap_dance(state);
}

void vscode_editor_down(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 2:
            register_code(KC_LCMD);
            tap_code(KC_K);
            register_code(KC_LCTL);
            tap_code(KC_DOWN);
            unregister_code(KC_LCMD);
            unregister_code(KC_LCTL);
            break;
        default:
            register_code(KC_LCMD);
            tap_code(KC_K);
            tap_code(KC_DOWN);
            unregister_code(KC_LCMD);
            break;
    }

    reset_tap_dance(state);
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_EQUAL_ARROW]         = ACTION_TAP_DANCE_FN(equal_arrow),
    [TD_MINUS_ARROW]         = ACTION_TAP_DANCE_FN(minus_arrow),
    [TD_LT_PHP]              = ACTION_TAP_DANCE_FN(lt_php),
    [TD_GT_PHP]              = ACTION_TAP_DANCE_FN(gt_php),
    [TD_VSCODE_EDITOR_LEFT]  = ACTION_TAP_DANCE_FN(vscode_editor_left),
    [TD_VSCODE_EDITOR_RIGHT] = ACTION_TAP_DANCE_FN(vscode_editor_right),
    [TD_VSCODE_EDITOR_UP]    = ACTION_TAP_DANCE_FN(vscode_editor_up),
    [TD_VSCODE_EDITOR_DOWN]  = ACTION_TAP_DANCE_FN(vscode_editor_down)
};

#define A_CTL   LCTL_T(KC_A)
#define S_OPT   LOPT_T(KC_S)
#define D_CMD   LCMD_T(KC_D)
#define K_CMD   LCMD_T(KC_K)
#define L_OPT   LOPT_T(KC_L)
#define QUO_CTL LCTL_T(KC_QUOT)
#define BSP_SFT LSFT_T(KC_BSPC)
#define SPC_SFT LSFT_T(KC_SPC)
#define N0_SFT  LSFT_T(KC_0)
#define BSL_SFT LSFT_T(KC_BSLS)

#define A_CTL   LCTL_T(KC_A)
#define R_OPT   LOPT_T(KC_R)
#define S_CMD   LCMD_T(KC_S)
#define E_CMD   LCMD_T(KC_E)
#define I_OPT   LOPT_T(KC_I)
#define O_CTL   LCTL_T(KC_O)

#define Q_MOU   LT(_MOUSE, KC_Q)
#define F_NAV   LT(_NAVIGATION, KC_F)
#define G_NUM   LT(_NUMBER, KC_G)
#define H_FUN   LT(_FUNCTION, KC_H)
#define J_SYM   LT(_SYMBOL, KC_J)
#define TAB_NUM LT(_NUMBER, KC_TAB)
#define ENT_FUN LT(_FUNCTION, KC_ENT)
#define MOUSE   TO(_MOUSE)

#define T_NAV   LT(_NAVIGATION, KC_T)
#define M_FUN   LT(_FUNCTION, KC_M)
#define N_SYM   LT(_SYMBOL, KC_N)

#define SEL_ALL G(KC_A)
#define SAVE    G(KC_S)
#define UNDO    G(KC_Z)
#define CUT     G(KC_X)
#define COPY    G(KC_C)
#define PASTE   G(KC_V)
#define REDO    G(S(KC_Z))
#define FIND    G(KC_F)

#define MIN_ARR TD(TD_MINUS_ARROW)
#define EQL_ARR TD(TD_EQUAL_ARROW)
#define LT_PHP  TD(TD_LT_PHP)
#define GT_PHP  TD(TD_GT_PHP)
#define VSC_LFT TD(TD_VSCODE_EDITOR_LEFT)
#define VSC_RGT TD(TD_VSCODE_EDITOR_RIGHT)
#define VSC_UP  TD(TD_VSCODE_EDITOR_UP)
#define VSC_DWN TD(TD_VSCODE_EDITOR_DOWN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        Q_MOU,   KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        A_CTL,   S_OPT,   D_CMD,   F_NAV,   G_NUM,   H_FUN,   J_SYM,   K_CMD,   L_OPT,   QUO_CTL,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
        KC_ESC,  _______, TAB_NUM, XXXXXXX, BSP_SFT, SPC_SFT, XXXXXXX, ENT_FUN, _______, KC_DEL
    ),

    [_COLEMAK] = LAYOUT(
        Q_MOU,   KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,
        A_CTL,   R_OPT,   S_CMD,   T_NAV,   G_NUM,   M_FUN,   N_SYM,   E_CMD,   I_OPT,   O_CTL,
        KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH,
        KC_ESC,  _______, TAB_NUM, XXXXXXX, BSP_SFT, SPC_SFT, XXXXXXX, ENT_FUN, _______, KC_DEL
    ),

    [_SYMBOL] = LAYOUT(
        KC_LPRN, KC_LBRC, KC_COLN, KC_RBRC, KC_RPRN, _______, _______, KC_EXLM, KC_AT,   KC_HASH,
        KC_DLR,  KC_DQUO, MIN_ARR, KC_UNDS, KC_SCLN, _______, _______, KC_LCMD, KC_LOPT, KC_LCTL,
        KC_LCBR, LT_PHP,  EQL_ARR, GT_PHP,  KC_RCBR, _______, _______, KC_PERC, KC_AMPR, KC_CIRC,
        _______, _______, KC_GRV,  _______, BSL_SFT, _______, _______, _______, _______, _______
    ),

    [_NUMBER] = LAYOUT(
        _______, _______, _______, _______, _______, KC_7,    KC_8,    KC_9,    KC_COLN, KC_EQL,
        KC_LCTL, KC_LOPT, KC_LCMD, _______, _______, KC_4,    KC_5,    KC_6,    KC_PLUS, KC_ASTR,
        _______, _______, _______, _______, _______, KC_1,    KC_2,    KC_3,    KC_MINS, KC_SLSH,
        _______, _______, _______, _______, _______, N0_SFT,  _______, KC_DOT,  _______, _______
    ),

    [_NAVIGATION] = LAYOUT(
        KC_ESC,  _______, _______, _______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_ESC,
        KC_LCTL, KC_LOPT, KC_LCMD, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_DEL, 
        _______, _______, _______, _______, _______, VSC_LFT, VSC_DWN, VSC_UP,  VSC_RGT, SELWORD,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_FUNCTION] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   RESET,   _______, CAPSWRD, SNKCASE, KBBCASE,
        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, KC_F19,  KC_LCMD, KC_LOPT, KC_LCTL,
        KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  _______, _______, QWERTY,  COLEMAK, MOUSE,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_MOUSE] = LAYOUT(
        KC_LCTL, KC_LOPT, KC_LCMD, KC_LSFT, _______, KC_WH_D, KC_WH_R, KC_MS_U, KC_WH_L, KC_ESC,
        SEL_ALL, SAVE,    _______, FIND,    _______, KC_WH_U, KC_MS_L, KC_MS_D, KC_MS_R, _______,
        UNDO,    CUT,     COPY,    PASTE,   REDO,    _______, _______, _______, _______, NORMAL,
        _______, _______, KC_BTN2, _______, KC_BTN1, KC_BTN1, _______, KC_BTN2, _______, _______
    )
};

const uint16_t PROGMEM esc_combo[] = { KC_W, KC_E, KC_R, COMBO_END };
const uint16_t PROGMEM tab_combo[] = { KC_X, KC_C, KC_V, COMBO_END };
const uint16_t PROGMEM del_combo[] = { KC_U, KC_I, KC_O, COMBO_END };
const uint16_t PROGMEM ent_combo[] = { KC_M, KC_COMM, KC_DOT, COMBO_END };
const uint16_t PROGMEM esc_combo_colemak[] = { KC_W, KC_F, KC_P, COMBO_END };
const uint16_t PROGMEM tab_combo_colemak[] = { KC_X, KC_C, KC_D, COMBO_END };
const uint16_t PROGMEM del_combo_colemak[] = { KC_L, KC_U, KC_Y, COMBO_END };
const uint16_t PROGMEM ent_combo_colemak[] = { KC_H, KC_COMM, KC_DOT, COMBO_END };

combo_t key_combos[COMBO_COUNT] = {
    [COMBO_ESC] = COMBO(esc_combo, KC_ESC),
    [COMBO_TAB] = COMBO(tab_combo, KC_TAB),
    [COMBO_DEL] = COMBO(del_combo, KC_DEL),
    [COMBO_ENT] = COMBO(ent_combo, KC_ENT),
    [COMBO_ESC_COLEMAK] = COMBO(esc_combo_colemak, KC_ESC),
    [COMBO_TAB_COLEMAK] = COMBO(tab_combo_colemak, KC_TAB),
    [COMBO_DEL_COLEMAK] = COMBO(del_combo_colemak, KC_DEL),
    [COMBO_ENT_COLEMAK] = COMBO(ent_combo_colemak, KC_ENT)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_autocorrection(keycode, record)) { return false; }
    if (!process_select_word(keycode, record, SELWORD)) { return false; }
    
    switch (keycode) {
        case NORMAL:
            layer_clear();
            return false;

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
        case J_SYM:
        case N_SYM:
        case G_NUM:
            return TAPPING_TERM - 50;
        case BSP_SFT:
        case SPC_SFT:
            return TAPPING_TERM + 15;
        case A_CTL:
        case S_OPT:
        case L_OPT:
            return TAPPING_TERM + 50;
        default:
            return TAPPING_TERM;
    }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case J_SYM:
        case N_SYM:
        case G_NUM:
            // Immediately select the hold action when another key is tapped.
            return true;
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
}