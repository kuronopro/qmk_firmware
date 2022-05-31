#include QMK_KEYBOARD_H

#include "features/autocorrection.h"
#include "features/swapper.h"

enum layers {
    _QWERTY,
    _NAVIGATION,
    _SYMBOL,
    _NUMBER,
    _MOUSE
};

enum custom_keycodes {
    NORMAL = SAFE_RANGE,
    SW_WIN, // GUI + TAB
    SW_APP // ALT + TAB
};

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

// Shortcut
#define UNDO    G(KC_Z)
#define CUT     G(KC_X)
#define COPY    G(KC_C)
#define PASTE   G(KC_V)
#define REDO    G(S(KC_Z))
#define TAB_L   G(S(KC_LCBR))
#define TAB_R   G(S(KC_RCBR))
#define SPC_L   C(KC_LEFT)
#define SPC_R   C(KC_RIGHT)
#define BACK    G(KC_LEFT)
#define FWD     G(KC_RIGHT)

// Mod tap
#define Z_SFT   MT(MOD_LSFT, KC_Z)
#define SLS_SFT MT(MOD_RSFT, KC_SLSH)
#define TAB_GUI MT(MOD_LGUI, KC_TAB)
#define ENT_GUI MT(MOD_RGUI, KC_ENT)
#define F6_CTL  MT(MOD_LCTL, KC_F6)
#define F7_ALT  MT(MOD_LALT, KC_F7)
#define F8_GUI  MT(MOD_LGUI, KC_F8)
#define F9_SFT  MT(MOD_LSFT, KC_F9)
#define N7_SFT  MT(MOD_RSFT, KC_7)
#define N8_GUI  MT(MOD_RGUI, KC_8)
#define N9_ALT  MT(MOD_RALT, KC_9)
#define N0_CTL  MT(MOD_RCTL, KC_0)


// Layer tap
#define Q_MOUS  LT(_MOUSE, KC_Q)
#define BSP_NAV LT(_NAVIGATION, KC_BSPC)
#define SPC_SYM LT(_SYMBOL, KC_SPC)
#define MOUSE   TO(_MOUSE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_kuronopro(
        Q_MOUS,  KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT,
        Z_SFT,   KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  SLS_SFT,
        KC_LCTL, KC_LALT, TAB_GUI,          BSP_NAV, SPC_SYM,          ENT_GUI, KC_RALT, KC_RCTL
    ),

    [_NAVIGATION] = LAYOUT_kuronopro(
        KC_ESC,  TAB_L,   TAB_R,   BACK,    FWD,     KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_ESC,
        KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_DEL,
        SW_WIN,  SPC_L,   SPC_R,   _______, _______, VSC_LFT, VSC_DWN, VSC_UP,  VSC_RGT, SW_APP,
        MOUSE,   _______, _______,          _______, _______,          _______, _______, _______
    ),

    [_SYMBOL] = LAYOUT_kuronopro(
        KC_LPRN, KC_LBRC, KC_COLN, KC_RBRC, KC_RPRN, KC_EXLM, KC_AT,   KC_HASH, KC_PERC, KC_CIRC,
        KC_DLR,  KC_DQUO, MIN_ARR, KC_UNDS, KC_SCLN, KC_AMPR, KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL,
        KC_LCBR, LT_PHP,  EQL_ARR, GT_PHP,  KC_RCBR, KC_ASTR, KC_PLUS, KC_PIPE, KC_TILD, KC_QUES,
        KC_GRV,  KC_BSLS, _______,          _______, _______,          _______, _______, _______
    ),

    [_NUMBER] = LAYOUT_kuronopro(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
        F6_CTL,  F7_ALT,  F8_GUI,  F9_SFT,  KC_F10,  KC_6,    N7_SFT,  N8_GUI,  N9_ALT,  N0_CTL,
        KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_EQL,  KC_PLUS, KC_MINS, KC_ASTR, KC_SLSH,
        KC_F19,  _______, _______,          _______, _______,          _______, _______, RESET
    ),

    [_MOUSE] = LAYOUT_kuronopro(
        KC_ESC,  _______, _______, _______, _______, KC_WH_D, KC_WH_R, KC_MS_U, KC_WH_L, SW_WIN,
        KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, _______, KC_WH_U, KC_MS_L, KC_MS_D, KC_MS_R, SW_APP,
        UNDO,    CUT,     COPY,    PASTE,   REDO,    _______, _______, _______, SPC_L,   SPC_R,
        NORMAL,  _______, KC_BTN2,          KC_BTN1, KC_BTN1,          KC_BTN2, _______, _______
    )
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

bool sw_win_active = false;
bool sw_app_active = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_autocorrection(keycode, record)) { return false; }

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
    }

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _SYMBOL, _NAVIGATION, _NUMBER);
}