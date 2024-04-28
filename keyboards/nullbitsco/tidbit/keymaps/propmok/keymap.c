/* Copyright 2021 Jay Greco
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
// Define layer names
#define _STOR 0
#define _BLEN 1
#define _PROC 2
// Define Macro names
enum custom_keycodes 
{
    PROG = SAFE_RANGE,
};
//Layer Keymaps
 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(LCTL(LSFT(KC_R)), LCTL(KC_B), LCTL(KC_S), TO(1), LALT(KC_E), LCTL(KC_V), LALT(KC_F), KC_S, LALT(KC_B), LCTL(KC_C), KC_G, KC_D, LALT(KC_D), LCTL(KC_X), LALT(KC_C), KC_P, LALT(KC_T), LALT(KC_S), LCTL(KC_Z)),
    [1] = LAYOUT(KC_P5, KC_PDOT, LCTL(KC_S), TO(2), KC_PSLS, LSFT(KC_TAB), LCTL(KC_V), KC_Q, KC_Z, LSFT(KC_S), LCTL(KC_C), KC_DOT, KC_Y, KC_G, LCTL(KC_X), KC_TAB, KC_X, LSFT(KC_D), KC_Z),
    [2] = LAYOUT(LGUI(KC_LBRC), LGUI(KC_RBRC), LGUI(KC_J), TO(0), LGUI(KC_NO), KC_X, LGUI(KC_X), LGUI(KC_K), KC_V, KC_C, LGUI(KC_C), KC_L, LGUI(KC_D), KC_E, LGUI(KC_Z), LGUI(KC_O), KC_S, KC_B, KC_SPC) 
};
//Rotary Encoder
#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_F, KC_A), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), },
    [1] = { ENCODER_CCW_CW(KC_GRV, KC_P0), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), },
    [2] = { ENCODER_CCW_CW(KC_RBRC, KC_LBRC), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), },
};
#endif
// OLED Screen
#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_0; }
// Include bitmaps that show the mapped keys on each layer
    #include "l1_storyboard_text.c"
    #include "l2_blender_text.c"
    #include "l3_procreate_text.c"
    // Render the correct image for each layer
    bool oled_task_user(void) 
    {
        switch (get_highest_layer(layer_state)) 
            {
                case _STOR:
                    render_stor_keymap_1();
                    break;
                case _BLEN:
                    render_blen_keymap_1();
                    break;
                case _PROC:
                    render_proc_keymap_1();
                    break;
                default:
                    // Or use the write_ln shortcut over adding '\n' to the end of your string
                    oled_write_ln_P(PSTR("Undefined"), false);
            }

        return false;
    }
#endif
// RGB LIGHTING LAYERS
void eeconfig_init_user(void) {  // EEPROM is getting reset!
  // use the non noeeprom versions, to write these values to EEPROM too
  rgblight_enable(); // Enable RGB by default      
  rgblight_sethsv(HSV_CHARTREUSE);  // Set it to pink by default
  rgblight_mode(RGBLIGHT_MODE_BREATHING + 2);  // Set it to static gradient
}

layer_state_t layer_state_set_user(layer_state_t state) {
  rgblight_config_t rgblight_config;
  switch(biton32(state)) {
  default:
    // Storyboard green/yellow gradient
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_CHARTREUSE);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 2);
    break;
  case _BLEN:
    // Blender Layer 1, purple/blue gradient
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_BLUE);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 2);
    break;
  case _PROC:
    // Procreate, pink/purple gradient
    //Read RGB Light State
    rgblight_config.raw = eeconfig_read_rgblight();
    //If enabled, set white
    if (rgblight_config.enable) {
        rgblight_sethsv_noeeprom(HSV_PURPLE);
                rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 2);
    } else { //Otherwise go back to disabled
        rgblight_disable_noeeprom();
    }
    break;
}
return state;
}
