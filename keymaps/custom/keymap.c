// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _NUMBERS,
    _SYMBOLS,
    _MACROS,
    _NAV,
    _MOUSE
};

enum combo_events {
    COMBO_NAV,
    COMBO_MOUSE,
    COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM nav_combo[] = {LT(_NUMBERS, KC_SPC), KC_LCTL, COMBO_END};
const uint16_t PROGMEM mouse_combo[] = {LT(_SYMBOLS, KC_BSPC), KC_COMM, COMBO_END};

combo_t key_combos[] = {
    [COMBO_NAV] = COMBO_ACTION(nav_combo),
    [COMBO_MOUSE] = COMBO_ACTION(mouse_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch(combo_index) {
        case COMBO_NAV:
            if (pressed) {
                layer_on(_NAV);
            } else {
                layer_off(_NAV);
            }
            break;
        case COMBO_MOUSE:
            if (pressed) {
                layer_on(_MOUSE);
            } else {
                layer_off(_MOUSE);
            }
            break;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                                            KC_LGUI, MT(MOD_HYPR, KC_ESC), LT(_NUMBERS, KC_SPC),    LT(_SYMBOLS, KC_BSPC), KC_SPC,  KC_RALT
    ),

    [_NUMBERS] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_7,    KC_8,    KC_9,    KC_SLSH, KC_TRNS,                            KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_DEL,
        KC_TRNS, KC_4,    KC_5,    KC_6,    KC_ASTR, KC_TRNS,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_ENT,
        KC_TRNS, KC_1,    KC_2,    KC_3,    KC_MINS, KC_TRNS,                            KC_PLUS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, KC_TRNS,
                                            KC_TRNS, KC_0,    KC_TRNS,                    KC_DOT,  KC_TRNS, KC_TRNS
    ),

    [_SYMBOLS] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_LT,   KC_GT,   KC_MINS, KC_PIPE, KC_TRNS,                            KC_CIRC, KC_LCBR, KC_RCBR, KC_DLR,  KC_TRNS, KC_TRNS,
        KC_TRNS, KC_ASTR, KC_SLSH, KC_EQL,  KC_AMPR, KC_TRNS,                            KC_HASH, KC_LPRN, KC_RPRN, KC_COLN, KC_DQUO, KC_TRNS,
        KC_TRNS, KC_PLUS, KC_LBRC, KC_RBRC, KC_PERC, KC_TRNS,                            KC_AT,   KC_SCLN, KC_DOT,  KC_COMM, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_EXLM, KC_TRNS,                    KC_TRNS, KC_TILD, KC_TRNS
    ),

    [_MACROS] = LAYOUT_split_3x6_3(
        QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        KC_TRNS, KC_BRID, KC_BRIU, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F12,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD, KC_VOLU,                            KC_MPRV, KC_MPLY, KC_MNXT, KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,                    KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [_NAV] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,                    KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [_MOUSE] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,                    KC_BTN2, KC_BTN1, KC_BTN3
    )
};