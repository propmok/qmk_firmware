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
//quantum layer script

//#define ENCODER_DIRECTION_FLIP


// Define layer names
#define _BLEN 0
#define _ILL1 1
#define _PROC 2

// Define Macro names
enum custom_keycodes 
{
    PROG = SAFE_RANGE,
};


 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(LCTL(KC_S), KC_PPLS, KC_PENT, TO(1), KC_NUM, KC_PMNS, KC_P0, KC_PDOT, KC_P9, KC_P6, KC_P3, KC_PAST, KC_P8, KC_P5, KC_P2, KC_PSLS, KC_P7, KC_P4, KC_P1),

    [1] = LAYOUT(LCTL(KC_LBRC), LCTL(KC_RBRC), KC_I, TO(2), KC_M, KC_X, LCTL(KC_V), KC_DEL, KC_R, KC_Y, LCTL(KC_C), LCTL(KC_K), KC_A, KC_P, LCTL(KC_Z), KC_K, KC_V, KC_N, KC_Q),

    [2] = LAYOUT(LGUI(KC_LBRC), LGUI(KC_RBRC), LGUI(KC_J), TO(0), LGUI(KC_NO), KC_X, LGUI(KC_X), LGUI(KC_K), KC_V, KC_C, LGUI(KC_C), KC_L, LGUI(KC_D), KC_E, LGUI(KC_Z), LGUI(KC_O), KC_S, KC_B, KC_SPC) 

};

//Rotary Encoder

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), },
    [1] = { ENCODER_CCW_CW(LCTL(KC_MINS), LCTL(KC_EQUAL)), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), },
    [2] = { ENCODER_CCW_CW(KC_LBRC, KC_RBRC), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), },
};
#endif



// OLED Screen

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_0; }

// Include bitmaps that show the mapped keys on each layer

    #include "l1_blender_text.c"
    #include "l2_illustrator_text.c"
    #include "l3_procreate_text.c"

    // Render the correct image for each layer

    bool oled_task_user(void) 
    {

        switch (get_highest_layer(layer_state)) 
            {
                case _BLEN:
                    render_blen_keymap_1();
                    break;
                case _ILL1:
                    render_ai_keymap_1();
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
  rgblight_sethsv(255,0,255);  // Set it to pink by default
  rgblight_mode(RGBLIGHT_MODE_STATIC_GRADIENT + 9);  // Set it to static gradient
}

layer_state_t layer_state_set_user(layer_state_t state) {
  rgblight_config_t rgblight_config;
  switch(biton32(state)) {
  default:
    // Blender, purple/blue gradient
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(188,149,219);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_GRADIENT + 8);
    break;
  case _ILL1:
    // Illustrator Layer 1, orange
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(10,255,255);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    break;
  case _PROC:
    // Procreate, pink/purple gradient
    //Read RGB Light State
    rgblight_config.raw = eeconfig_read_rgblight();
    //If enabled, set white
    if (rgblight_config.enable) {
        rgblight_sethsv_noeeprom(235,255,255);
                rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_GRADIENT + 9);
    } else { //Otherwise go back to disabled
        rgblight_disable_noeeprom();
    }
    break;
}
return state;
}
