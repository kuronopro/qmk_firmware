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
    _MOUSE
};

enum custom_keycodes {
    NORMAL = SAFE_RANGE,
    CAPSWRD,
    SNKCASE,
    KBBCASE,
    SELWORD,
    SW_WIN,
    SW_APP
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

// Layer tap etc
#define Q_MOUS  LT(_MOUSE, KC_Q)
#define F_NAV   LT(_NAVIGATION, KC_F)
#define V_NUM   LT(_NUMBER, KC_V)
#define M_FUN   LT(_FUNCTION, KC_M)
#define J_SYM   LT(_SYMBOL, KC_J)
#define TO_MOUS TO(_MOUSE)

// Shortcut
#define UNDO    G(KC_Z)
#define CUT     G(KC_X)
#define COPY    G(KC_C)
#define PASTE   G(KC_V)
#define REDO    G(S(KC_Z))
#define SPC_LFT C(KC_LEFT)
#define SPC_RGT C(KC_RGHT)

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
};

void equal_arrow(qk_tap_dance_state_t *state, void *user_data);
void minus_arrow(qk_tap_dance_state_t *state, void *user_data);
void lt_php(qk_tap_dance_state_t *state, void *user_data);
void gt_php(qk_tap_dance_state_t *state, void *user_data);
void vscode_editor_left(qk_tap_dance_state_t *state, void *user_data);
void vscode_editor_right(qk_tap_dance_state_t *state, void *user_data);
void vscode_editor_up(qk_tap_dance_state_t *state, void *user_data);
void vscode_editor_down(qk_tap_dance_state_t *state, void *user_data);

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_EQUAL_ARROW]         = ACTION_TAP_DANCE_FN(equal_arrow),
    [TD_MINUS_ARROW]         = ACTION_TAP_DANCE_FN(minus_arrow),
    [TD_LT_PHP]              = ACTION_TAP_DANCE_FN(lt_php),
    [TD_GT_PHP]              = ACTION_TAP_DANCE_FN(gt_php),
    [TD_VSCODE_EDITOR_LEFT]  = ACTION_TAP_DANCE_FN(vscode_editor_left),
    [TD_VSCODE_EDITOR_RIGHT] = ACTION_TAP_DANCE_FN(vscode_editor_right),
    [TD_VSCODE_EDITOR_UP]    = ACTION_TAP_DANCE_FN(vscode_editor_up),
    [TD_VSCODE_EDITOR_DOWN]  = ACTION_TAP_DANCE_FN(vscode_editor_down),
};

#define MIN_ARR TD(TD_MINUS_ARROW)
#define EQL_ARR TD(TD_EQUAL_ARROW)
#define LT_PHP  TD(TD_LT_PHP)
#define GT_PHP  TD(TD_GT_PHP)
#define VSC_LFT TD(TD_VSCODE_EDITOR_LEFT)
#define VSC_RGT TD(TD_VSCODE_EDITOR_RIGHT)
#define VSC_UP  TD(TD_VSCODE_EDITOR_UP)
#define VSC_DWN TD(TD_VSCODE_EDITOR_DOWN)

// Keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_kuronopro(
        Q_MOUS,  KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        A_CTL,   S_OPT,   D_CMD,   F_NAV,   KC_G,             KC_H,    J_SYM,   K_CMD,   L_OPT,   QUO_CTL,
        KC_Z,    KC_X,    KC_C,    V_NUM,   KC_B,             KC_N,    M_FUN,   KC_COMM, KC_DOT,  KC_SLSH,
        KC_ESC,  XXXXXXX, KC_TAB,           BSP_SFT,          SPC_SFT,          KC_ENT,  XXXXXXX, KC_DEL
    ),

    [_SYMBOL] = LAYOUT_kuronopro(
        KC_LPRN, KC_LBRC, KC_COLN, KC_RBRC, KC_RPRN,          _______, KC_QUES, KC_EXLM, KC_AT,   KC_HASH,
        KC_DLR,  KC_DQUO, MIN_ARR, KC_UNDS, KC_SCLN,          _______, _______, KC_LCMD, KC_LOPT, KC_LCTL,
        KC_LCBR, LT_PHP,  EQL_ARR, GT_PHP,  KC_RCBR,          _______, _______, KC_AMPR, KC_PERC, KC_CIRC,
        KC_GRV,  KC_BSLS, _______,          _______,          _______,          _______, KC_PLUS, KC_ASTR
    ),

    [_NUMBER] = LAYOUT_kuronopro(
        KC_D,    KC_E,    KC_F,    _______, _______,          KC_7,    KC_8,    KC_9,    KC_COLN, KC_EQL,
        KC_LCTL, KC_LOPT, KC_LCMD, _______, _______,          KC_4,    KC_5,    KC_6,    KC_PLUS, KC_ASTR,
        KC_A,    KC_B,    KC_C,    _______, _______,          KC_1,    KC_2,    KC_3,    KC_MINS, KC_SLSH,
        _______, _______, _______,          _______,          N0_SFT,           KC_DOT,  _______, _______
    ),

    [_NAVIGATION] = LAYOUT_kuronopro(
        TO_MOUS, SPC_LFT, SPC_RGT, _______, _______,          KC_HOME, KC_PGUP, KC_PGDN, KC_END,  SW_WIN,
        KC_LCTL, KC_LOPT, KC_LCMD, _______, _______,          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, SW_APP,
        _______, _______, _______, _______, _______,          VSC_LFT, VSC_DWN, VSC_UP,  VSC_RGT, SELWORD,
        _______, _______, _______,          _______,          _______,          _______, _______, _______
    ),

    [_FUNCTION] = LAYOUT_kuronopro(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,            _______, _______, _______, _______, RESET,
        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,           _______, KC_F19,  KC_LCMD, KC_LOPT, KC_LCTL,
        KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,           _______, _______, CAPSWRD, SNKCASE, KBBCASE,
        _______, _______, _______,          _______,          _______,          _______, _______, _______
    ),

    [_MOUSE] = LAYOUT_kuronopro(
        // Mouse scroll posisinya terbalik karena settting natural scrolling di MacOS
        NORMAL,  _______, _______, _______, _______,          KC_WH_D, KC_WH_R, KC_MS_U, KC_WH_L, SW_WIN,
        KC_LCTL, KC_LOPT, KC_LCMD, KC_LSFT, _______,          KC_WH_U, KC_MS_L, KC_MS_D, KC_MS_R, SW_APP,
        UNDO,    CUT,     COPY,    PASTE,   REDO,             _______, _______, _______, _______, _______,
        _______, _______, KC_BTN2,          KC_BTN1,          KC_BTN1,          KC_BTN2, _______, _______
    ),
};

// Implementasi tap dance
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

// Macro etc
bool sw_win_active = false;
bool sw_app_active = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_autocorrection(keycode, record)) { return false; }
    if (!process_select_word(keycode, record, SELWORD)) { return false; }

    update_swapper(
        &sw_win_active, KC_LCMD, KC_TAB, SW_WIN,
        keycode, record
    );
    update_swapper(
        &sw_app_active, KC_LOPT, KC_TAB, SW_APP,
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
        case V_NUM:
        case J_SYM:
            return TAPPING_TERM - 50;
        default:
            return TAPPING_TERM;
    }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case V_NUM:
        case J_SYM:
            // Immediately select the hold action when another key is pressed.
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}