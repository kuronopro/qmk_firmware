#include QMK_KEYBOARD_H

#include "features/casemodes.h"
#include "features/autocorrection.h"
#include "features/select_word.h"

enum layers {
    _QWERTY,
    _SYMBOL,
    _NUMBER,
    _NAVIGATION,
    _FUNCTION,
    _MOUSE
};

enum custom_keycodes {
    NORMAL = SAFE_RANGE,
    CAPSWRD,
    SNKCASE,
    KBBCASE,
    SELWORD
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

#define Q_MOU   LT(_MOUSE, KC_Q)
#define F_NAV   LT(_NAVIGATION, KC_F)
#define G_NUM   LT(_NUMBER, KC_G)
#define H_FUN   LT(_FUNCTION, KC_H)
#define J_SYM   LT(_SYMBOL, KC_J)
#define TAB_FUN LT(_FUNCTION, KC_TAB)
#define ENT_NAV LT(_NAVIGATION, KC_ENT)
#define MOUSE   TO(_MOUSE)

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
    [_QWERTY] = LAYOUT_kuronopro(
        Q_MOU,   KC_W,    KC_E,    KC_R,    KC_T,           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        A_CTL,   S_OPT,   D_CMD,   F_NAV,   G_NUM,          H_FUN,   J_SYM,   K_CMD,   L_OPT,   QUO_CTL,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,           KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                          TAB_FUN,          BSP_SFT,        SPC_SFT,          ENT_NAV
    ),

    [_SYMBOL] = LAYOUT_kuronopro(
        KC_LPRN, KC_LBRC, KC_COLN, KC_RBRC, KC_RPRN,        _______, _______, KC_EXLM, KC_AT,   KC_HASH,
        KC_DLR,  KC_DQUO, MIN_ARR, KC_UNDS, KC_SCLN,        _______, _______, KC_LCMD, KC_LOPT, KC_LCTL,
        KC_LCBR, LT_PHP,  EQL_ARR, GT_PHP,  KC_RCBR,        _______, _______, KC_PERC, KC_AMPR, KC_CIRC,
                          KC_GRV,           BSL_SFT,        _______,          _______
    ),

    [_NUMBER] = LAYOUT_kuronopro(
        _______, _______, _______, _______, _______,        KC_7,    KC_8,    KC_9,    KC_EQL,  KC_COLN,
        KC_LCTL, KC_LOPT, KC_LCMD, _______, _______,        KC_4,    KC_5,    KC_6,    KC_PLUS, KC_ASTR,
        _______, _______, _______, _______, _______,        KC_1,    KC_2,    KC_3,    KC_MINS, KC_SLSH,
                          _______,          _______,        N0_SFT,           KC_DOT
    ),

    [_NAVIGATION] = LAYOUT_kuronopro(
        KC_ESC,  _______, _______, _______, _______,        KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_ESC,
        KC_LCTL, KC_LOPT, KC_LCMD, _______, _______,        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_DEL, 
        _______, _______, _______, _______, _______,        VSC_LFT, VSC_DWN, VSC_UP,  VSC_RGT, SELWORD,
                          _______,          _______,        _______,          _______
    ),

    [_FUNCTION] = LAYOUT_kuronopro(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,          RESET,   _______, CAPSWRD, SNKCASE, KBBCASE,
        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,         _______, KC_F19,  KC_LCMD, KC_LOPT, KC_LCTL,
        KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,         _______, _______, _______, _______, MOUSE,
                          _______,          _______,        _______,          _______
    ),

    [_MOUSE] = LAYOUT_kuronopro(
        KC_LCTL, KC_LOPT, KC_LCMD, KC_LSFT, _______,        KC_WH_D, KC_WH_R, KC_MS_U, KC_WH_L, KC_ESC,
        SEL_ALL, SAVE,    _______, FIND,    _______,        KC_WH_U, KC_MS_L, KC_MS_D, KC_MS_R, _______,
        UNDO,    CUT,     COPY,    PASTE,   REDO,           _______, _______, _______, _______, NORMAL,
                          KC_BTN2,          KC_BTN1,        KC_BTN1,          KC_BTN2
    )
};

enum combo_events {
    COMBO_ESC,
    COMBO_TAB,
    COMBO_DEL,
    COMBO_ENT,
    COMBO_UNDO,
    COMBO_REDO,
    COMBO_COPY,
    COMBO_PASTE,
    COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM esc_combo[] = { KC_X, KC_C, COMBO_END };
const uint16_t PROGMEM tab_combo[] = { KC_C, KC_V, COMBO_END };
const uint16_t PROGMEM del_combo[] = { KC_COMM, KC_DOT, COMBO_END };
const uint16_t PROGMEM ent_combo[] = { KC_M, KC_COMM, COMBO_END };
const uint16_t PROGMEM undo_combo[] = { KC_Z, KC_X, COMBO_END };
const uint16_t PROGMEM redo_combo[] = { KC_DOT, KC_SLSH, COMBO_END };
const uint16_t PROGMEM copy_combo[] = { KC_V, KC_B, COMBO_END };
const uint16_t PROGMEM paste_combo[] = { KC_N, KC_M, COMBO_END };

combo_t key_combos[] = {
    [COMBO_ESC] = COMBO(esc_combo, KC_ESC),
    [COMBO_TAB] = COMBO(tab_combo, KC_TAB),
    [COMBO_DEL] = COMBO(del_combo, KC_DEL),
    [COMBO_ENT] = COMBO(ent_combo, KC_ENT),
    [COMBO_UNDO] = COMBO_ACTION(undo_combo),
    [COMBO_REDO] = COMBO_ACTION(redo_combo),
    [COMBO_COPY] = COMBO_ACTION(copy_combo),
    [COMBO_PASTE] = COMBO_ACTION(paste_combo)
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch(combo_index) {
        case COMBO_UNDO:
            if (pressed) {
                register_code(KC_LCMD);
                tap_code(KC_Z);
            } else {
                unregister_code(KC_LCMD);
            }
            break;
        case COMBO_REDO:
            if (pressed) {
                register_code(KC_LCMD);
                register_code(KC_LSFT);
                tap_code(KC_Z);
            } else {
                unregister_code(KC_LCMD);
                unregister_code(KC_LSFT);
            }
            break;
        case COMBO_COPY:
            if (pressed) {
                register_code(KC_LCMD);
                tap_code(KC_C);
            } else {
                unregister_code(KC_LCMD);
            }
            break;
        case COMBO_PASTE:
            if (pressed) {
                register_code(KC_LCMD);
                tap_code(KC_V);
            } else {
                unregister_code(KC_LCMD);
            }
            break;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_autocorrection(keycode, record)) { return false; }
    if (!process_select_word(keycode, record, SELWORD)) { return false; }
    
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
    }

    if (!process_case_modes(keycode, record)) {
        return false;
    }

    return true;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) { 
        case J_SYM:
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
        case G_NUM:
            // Immediately select the hold action when another key is tapped.
            return true;
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
}