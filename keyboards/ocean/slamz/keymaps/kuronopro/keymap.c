#include QMK_KEYBOARD_H

#include "features/casemodes.h"
#include "features/autocorrection.h"
#include "features/select_word.h"
#include "features/swapper.h"

enum layers {
    _QWERTY,
    _SYMBOL,
    _NUMBER,
    _NAVIGATION,
    _FUNCTION,
    _MACRO,
    _MOUSE
};

enum custom_keycodes {
    NORMAL = SAFE_RANGE,
    CAPSWRD,
    SNKCASE,
    KBBCASE,
    SELWORD,
    SW_WIN
};

// Mod tap
#define A_CTL   LCTL_T(KC_A)
#define S_OPT   LOPT_T(KC_S)
#define D_CMD   LCMD_T(KC_D)
#define K_CMD   LCMD_T(KC_K)
#define L_OPT   LOPT_T(KC_L)
#define QUO_CTL LCTL_T(KC_QUOT)
#define BSP_SFT LSFT_T(KC_BSPC)
#define SPC_SFT LSFT_T(KC_SPC)
#define BSL_SFT LSFT_T(KC_BSLS)
#define N0_SFT  LSFT_T(KC_0)

// Untuk hexadecimal
#define CAPS_A  S(KC_A)
#define CAPS_B  S(KC_B)
#define CAPS_C  S(KC_C)
#define CAPS_D  S(KC_D)
#define CAPS_E  S(KC_E)
#define CAPS_F  S(KC_F)

// Layer tap etc
#define Q_MCR   LT(_MACRO, KC_Q)
#define F_NAV   LT(_NAVIGATION, KC_F)
#define G_FUN   LT(_FUNCTION, KC_G)
#define H_NUM   LT(_NUMBER, KC_H)
#define J_SYM   LT(_SYMBOL, KC_J)
#define Z_NUM   LT(_NUMBER, KC_Z)
#define TAB_MOU LT(_MOUSE, KC_TAB)
#define ENT_NAV LT(_NAVIGATION, KC_ENT)
#define TO_MOUS TO(_MOUSE)

// Shortcut
#define UNDO    G(KC_Z)
#define CUT     G(KC_X)
#define COPY    G(KC_C)
#define PASTE   G(KC_V)
#define REDO    G(S(KC_Z))

// Tap dance
enum {
    TD_EQUAL_ARROW, // single tap =, double tap =>
    TD_MINUS_ARROW, // single tap -, double tap ->
    TD_LT_PHP, // single tap <, double tap <?
    TD_GT_PHP, // single tap >, double tap ?>
    TD_VSCODE_EDITOR_LEFT, // single tap pindah fokus ke kiri, double tap pindah editor ke kiri
    TD_VSCODE_EDITOR_RIGHT, // single tap pindah fokus ke kanan, double tap pindah editor ke kanan
    TD_VSCODE_EDITOR_UP, // single tap pindah fokus ke kiri, double tap pindah editor ke kiri
    TD_VSCODE_EDITOR_DOWN, // single tap pindah fokus ke kiri, double tap pindah editor ke kiri
    TD_LCBR_NUM // single tap {, hold momentary layer _NUMBER
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP
} td_state_t;

static td_state_t td_state;

td_state_t cur_dance(qk_tap_dance_state_t *state);

void equal_arrow(qk_tap_dance_state_t *state, void *user_data);
void minus_arrow(qk_tap_dance_state_t *state, void *user_data);
void lt_php(qk_tap_dance_state_t *state, void *user_data);
void gt_php(qk_tap_dance_state_t *state, void *user_data);
void vscode_editor_left(qk_tap_dance_state_t *state, void *user_data);
void vscode_editor_right(qk_tap_dance_state_t *state, void *user_data);
void vscode_editor_up(qk_tap_dance_state_t *state, void *user_data);
void vscode_editor_down(qk_tap_dance_state_t *state, void *user_data);
void lcbr_num_finished(qk_tap_dance_state_t *state, void *user_data);
void lcbr_num_reset(qk_tap_dance_state_t *state, void *user_data);

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_EQUAL_ARROW]         = ACTION_TAP_DANCE_FN(equal_arrow),
    [TD_MINUS_ARROW]         = ACTION_TAP_DANCE_FN(minus_arrow),
    [TD_LT_PHP]              = ACTION_TAP_DANCE_FN(lt_php),
    [TD_GT_PHP]              = ACTION_TAP_DANCE_FN(gt_php),
    [TD_VSCODE_EDITOR_LEFT]  = ACTION_TAP_DANCE_FN(vscode_editor_left),
    [TD_VSCODE_EDITOR_RIGHT] = ACTION_TAP_DANCE_FN(vscode_editor_right),
    [TD_VSCODE_EDITOR_UP]    = ACTION_TAP_DANCE_FN(vscode_editor_up),
    [TD_VSCODE_EDITOR_DOWN]  = ACTION_TAP_DANCE_FN(vscode_editor_down),
    [TD_LCBR_NUM]            = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lcbr_num_finished, lcbr_num_reset)
};

#define MIN_ARR TD(TD_MINUS_ARROW)
#define EQL_ARR TD(TD_EQUAL_ARROW)
#define LT_PHP  TD(TD_LT_PHP)
#define GT_PHP  TD(TD_GT_PHP)
#define VSC_LFT TD(TD_VSCODE_EDITOR_LEFT)
#define VSC_RGT TD(TD_VSCODE_EDITOR_RIGHT)
#define VSC_UP  TD(TD_VSCODE_EDITOR_UP)
#define VSC_DWN TD(TD_VSCODE_EDITOR_DOWN)
#define LCBRNUM TD(TD_LCBR_NUM)

// Keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_kuronopro(
        Q_MCR,   KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        A_CTL,   S_OPT,   D_CMD,   F_NAV,   G_FUN,            H_NUM,   J_SYM,   K_CMD,   L_OPT,   QUO_CTL,
        Z_NUM,   KC_X,    KC_C,    KC_V,    KC_B,             KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                          TAB_MOU,          BSP_SFT,          SPC_SFT,          ENT_NAV
    ),

    [_SYMBOL] = LAYOUT_kuronopro(
        KC_LPRN, KC_LBRC, KC_COLN, KC_RBRC, KC_RPRN,          _______, _______, KC_EXLM, KC_AT,   KC_HASH,
        KC_DLR,  KC_DQUO, MIN_ARR, KC_UNDS, KC_SCLN,          _______, _______, KC_LCMD, KC_LOPT, KC_LCTL,
        LCBRNUM, LT_PHP,  EQL_ARR, GT_PHP,  KC_RCBR,          _______, _______, KC_AMPR, KC_PERC, KC_CIRC,
                          KC_GRV,           BSL_SFT,          _______,          _______
    ),

    [_NUMBER] = LAYOUT_kuronopro(
        KC_MINS, KC_7,    KC_8,    KC_9,    KC_PLUS,          _______, _______, CAPS_A,  CAPS_B,  CAPS_C,
        KC_EQL,  KC_4,    KC_5,    KC_6,    KC_ASTR,          _______, _______, KC_LCMD, KC_LOPT, KC_LCTL,
        KC_COLN, KC_1,    KC_2,    KC_3,    KC_SLSH,          _______, _______, CAPS_D,  CAPS_E,  CAPS_F,
                          KC_DOT,           N0_SFT,           _______,          _______
    ),

    [_NAVIGATION] = LAYOUT_kuronopro(
        TO_MOUS, _______, _______, _______, _______,          KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_ESC,
        KC_LCTL, KC_LOPT, KC_LCMD, _______, _______,          KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL,
        _______, _______, _______, _______, _______,          KC_TAB,  _______, _______, _______, KC_ENT,
                          _______,          _______,          _______,          _______
    ),

    [_FUNCTION] = LAYOUT_kuronopro(
        _______, _______, _______, _______, _______,          KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,
        KC_LCTL, KC_LOPT, KC_LCMD, KC_F19,  _______,          KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
        _______, _______, _______, _______, _______,          KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,
                          _______,          _______,          _______,          _______
    ),

    [_MACRO] = LAYOUT_kuronopro(
        _______, CAPSWRD, SNKCASE, KBBCASE, SW_WIN,           RESET,   _______, _______, _______, _______,
        _______, _______, _______, _______, _______,          VSC_LFT, VSC_DWN, VSC_UP,  VSC_RGT, SELWORD,
        _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,
                          _______,          _______,          _______,          _______
    ),

    [_MOUSE] = LAYOUT_kuronopro(
        // Mouse scroll posisinya terbalik karena settting natural scrolling di MacOS
        NORMAL,  _______, _______, _______, SW_WIN,           KC_WH_D, KC_WH_R, KC_MS_U, KC_WH_L, _______,
        KC_LCTL, KC_LOPT, KC_LCMD, KC_LSFT, _______,          KC_WH_U, KC_MS_L, KC_MS_D, KC_MS_R, _______,
        UNDO,    CUT,     COPY,    PASTE,   REDO,             _______, _______, _______, _______, _______,
                          KC_BTN2,          KC_BTN1,          KC_BTN1,          KC_BTN2
    ),
};

// Implementasi tap dance
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    }

    if (state->count == 2) return TD_DOUBLE_TAP;
    else return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}

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

void lcbr_num_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            tap_code16(KC_LCBR);
            break;
        case TD_SINGLE_HOLD:
            layer_on(_NUMBER);
            break;
        case TD_DOUBLE_TAP:
            tap_code16(KC_LCBR);
            tap_code16(KC_LCBR);
            break;
        default:
            break;
    }
}

void lcbr_num_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
            unregister_code16(KC_LCBR);
            break;
        case TD_SINGLE_HOLD:
            layer_off(_NUMBER);
            break;
        default:
            break;
    }
}

// Combo
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
const uint16_t PROGMEM undo_combo[] = { Z_NUM, KC_X, COMBO_END };
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

// Macro etc
bool sw_win_active = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_autocorrection(keycode, record)) { return false; }
    if (!process_select_word(keycode, record, SELWORD)) { return false; }

    update_swapper(
        &sw_win_active, KC_LCMD, KC_TAB, SW_WIN,
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
            return TAPPING_TERM + 15;
        case Q_MCR:
        case H_NUM:
        case J_SYM:
        case Z_NUM:
        case LCBRNUM:
            return TAPPING_TERM - 50;
        default:
            return TAPPING_TERM;
    }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case Q_MCR:
        case H_NUM:
        case J_SYM:
        case Z_NUM:
        case LCBRNUM:
            // Immediately select the hold action when another key is pressed.
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}