// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Custom keycode for left-only Hyper on hold, Esc on tap
enum custom_keycodes {
    LHYP_ESC = SAFE_RANGE,
};

// State for LHYP_ESC tap-hold behavior
static bool     lhyp_down = false;
static bool     lhyp_hold = false;
static uint16_t lhyp_timer = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // If any other key is pressed while LHYP_ESC is down and not yet a hold,
    // convert to hold and register left-only Hyper mods immediately.
    if (lhyp_down && !lhyp_hold && record->event.pressed && keycode != LHYP_ESC) {
        lhyp_hold = true;
        // Ensure only left-side mods are set for Hyper
        register_mods(MOD_BIT_LCTRL | MOD_BIT_LALT | MOD_BIT_LGUI | MOD_BIT_LSHIFT);
        // If right shift is present for any reason, remove it
        del_mods(MOD_BIT_RSHIFT);
    }

    switch (keycode) {
        case LHYP_ESC:
            if (record->event.pressed) {
                lhyp_down  = true;
                lhyp_hold  = false;
                lhyp_timer = timer_read();
            } else {
                // On release: decide tap vs hold
                if (lhyp_hold) {
                    // Unregister left-only Hyper mods
                    unregister_mods(MOD_BIT_LCTRL | MOD_BIT_LALT | MOD_BIT_LGUI | MOD_BIT_LSHIFT);
                } else {
                    // Treat as tap (Esc)
                    tap_code(KC_ESC);
                }
                lhyp_down = false;
                lhyp_hold = false;
            }
            return false; // We handled LHYP_ESC
    }
    return true;
}

void matrix_scan_user(void) {
    // If LHYP_ESC is held past tapping term without other key presses, treat as hold
    if (lhyp_down && !lhyp_hold && timer_elapsed(lhyp_timer) > TAPPING_TERM) {
        lhyp_hold = true;
        register_mods(MOD_BIT_LCTRL | MOD_BIT_LALT | MOD_BIT_LGUI | MOD_BIT_LSHIFT);
        del_mods(MOD_BIT_RSHIFT);
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                                            KC_LGUI, LHYP_ESC,            LT(1, KC_SPC),    LT(2, KC_BSPC), KC_SPC,  KC_ENT
    ),

    [1] = LAYOUT_split_3x6_3(
        KC_NO,   KC_7,    KC_8,    KC_9,    KC_SLSH, KC_NO,                              KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_DEL,
        KC_NO,   KC_4,    KC_5,    KC_6,    KC_ASTR, KC_NO,                              KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_ENT,
        KC_NO,   KC_1,    KC_2,    KC_3,    KC_MINS, KC_NO,                              KC_PLUS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, KC_NO,
                                            KC_NO,   KC_0,    KC_TRNS,                    KC_DOT,  KC_NO,   KC_NO
    ),

    [2] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_LT,   KC_GT,   KC_MINS, KC_PIPE, KC_TRNS,                            KC_CIRC, KC_LCBR, KC_RCBR, KC_DLR,  KC_TRNS, KC_TRNS,
        KC_TRNS, KC_ASTR, KC_SLSH, KC_EQL,  KC_AMPR, KC_TRNS,                            KC_HASH, KC_LPRN, KC_RPRN, KC_COLN, KC_DQUO, KC_TRNS,
        KC_TRNS, KC_PLUS, KC_LBRC, KC_RBRC, KC_PERC, KC_TRNS,                            KC_AT,   KC_SCLN, KC_DOT,  KC_COMM, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_EXLM, KC_TRNS,                    KC_TRNS, KC_TILD, KC_TRNS
    ),

    [3] = LAYOUT_split_3x6_3(
        QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        KC_TRNS, KC_BRID, KC_BRIU, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F12,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD, KC_VOLU,                            KC_MPRV, KC_MPLY, KC_MNXT, KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,                    KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [4] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,                    KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [5] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,                    MS_BTN2, MS_BTN1, MS_BTN3
    )
};
