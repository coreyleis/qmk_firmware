
 /* Copyright 2021 Dane Evans
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
  // SOFLE RGB
#include <stdio.h>

#include QMK_KEYBOARD_H


#define _BASE_LAYER 0 //base
#define _SYMBOLS_LAYER 1 //symbols
#define _MOUSE_LAYER 2 //mouse / media
#define _NAV_LAYER 3 //nav / arrow
#define _LAYER4 4 //placeholder, not really media
enum custom_keycodes {
    LAYER0 = SAFE_RANGE,
    LAYER1,
    LAYER2,
    LAYER3,
    LAYER4,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE_LAYER] = LAYOUT(
KC_EQL, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, 
KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS,
KC_DEL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, LT(2,KC_SCLN), KC_QUOT, 
KC_LSFT, LCTL_T(KC_Z), KC_X, KC_C, KC_V, KC_B, KC_MUTE, KC_RGUI, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
KC_LCTL, KC_LALT, MO(3), KC_BSPC, KC_SPC, KC_TAB, KC_ENT, MO(1), LCTL_T(KC_ESC), MO(2)),

[_SYMBOLS_LAYER] = LAYOUT(
KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
KC_NO, KC_EXLM, KC_AT, KC_LCBR, KC_RCBR, KC_PIPE, KC_NO, KC_P7, KC_P8, KC_P9, KC_PSLS, KC_F12, 
KC_NO, KC_HASH, KC_DLR, KC_LPRN, KC_RPRN, KC_GRV, KC_NO, KC_P4, KC_P5, KC_P6, KC_PAST, KC_NO, //<-- replace this key (?)
KC_NO, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, KC_NO, KC_NO, KC_NO, KC_P1, KC_P2, KC_P3,
KC_PMNS, KC_PEQL, KC_NO, KC_LT, KC_GT, KC_NO, KC_NO, KC_NO, KC_P0, KC_NO, KC_PDOT, KC_PPLS),

[_MOUSE_LAYER] = LAYOUT(
KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
KC_BTN1, KC_MS_U, KC_BTN3, KC_NO, KC_WH_U, KC_BTN2, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_L, KC_WH_D, KC_WH_R, KC_NO, KC_NO, KC_NO, KC_MPLY, KC_NO, KC_NO,
KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MPRV, KC_MNXT, 
KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_T, KC_NO, KC_VOLU, KC_VOLD, KC_MUTE, KC_NO),

[_NAV_LAYER] = LAYOUT(
KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
KC_NO, KC_NO, KC_INS, KC_HOME, KC_PGUP, KC_NO, KC_NO, KC_NO, KC_UP, KC_NO, KC_NO, KC_NO,
KC_NO, KC_NO, KC_DEL, KC_END, KC_PGDN, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO, 
KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),

[_LAYER4] = LAYOUT(
KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
QK_BOOT, KC_NO, DF(0), DF(1), CG_TOGG, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
KC_NO, KC_NO, CG_TOGG, KC_NO, KC_NO, KC_NO, KC_NO, KC_VOLD, KC_MUTE, KC_VOLU, KC_NO, KC_NO, 
KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MPRV, KC_MPLY, KC_MNXT, 
KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS) 

};


#ifdef RGBLIGHT_ENABLE

#define INDICATOR_BRIGHTNESS 20

#define HSV_OVERRIDE_HELP(h, s, v, Override) h, s , Override
#define HSV_OVERRIDE(hsv, Override) HSV_OVERRIDE_HELP(hsv,Override)

/*
Lights adressing based on the build guide PNG
Indicator:1
Drop Lighting: (Underglow) 2-7 (6 total)
Per Key lighting 8-36 (probably not in the order you think.)
Second side should therefore be 36 offset (i think? existing code has 35 offset :/)
https://josefadamcik.github.io/SofleKeyboard/images/build_guide_rgb/board-both.png

Lights are turned on by, i believe, starting with the index of the light you'd like to address,
    adding the number of lights you want to turn on from that position,
    and passing the HSV colour you'd like to give those lights.

I'm still not sure why I'm getting a baseline of red :)
*/
// Light combinations
#define SET_INDICATORS(hsv) \
	{0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
    {35+0, 1, hsv}
#define SET_UNDERGLOW(hsv) \
	{1, 6, hsv}, \
    {35+1, 6,hsv}

//This sets literally every LED
#define SET_LAYER_ID(hsv) 	\
	{0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
    {35+0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
    {35+1, 36, hsv}, \
    {1, 36, hsv}


char layer_state_str[70];
// Now define the array of layers. Later layers take precedence


const rgblight_segment_t PROGMEM layer_qwerty_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    SET_LAYER_ID(HSV_BLUE),
    SET_UNDERGLOW(HSV_YELLOW)
);


const rgblight_segment_t PROGMEM layer_symbol_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    SET_LAYER_ID(HSV_PINK),
	SET_UNDERGLOW(HSV_GREEN)
);

const rgblight_segment_t PROGMEM layer_mouse_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    SET_LAYER_ID(HSV_RED),
	SET_UNDERGLOW(HSV_CYAN)
);

const rgblight_segment_t PROGMEM layer_nav_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    SET_LAYER_ID(HSV_TURQUOISE),
    SET_UNDERGLOW(HSV_MAGENTA)
);



const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(

    layer_qwerty_lights,
	layer_symbol_lights,
	layer_mouse_lights,
    layer_nav_lights
	// layer_numpad_lights,
	// layer_switcher_lights,  // Overrides other layers
	// layer_colemakdh_lights
);

bool led_update_user(led_t led_state) {
    return true;
}
layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _BASE_LAYER));
    return state;
}
layer_state_t layer_state_set_user(layer_state_t state) {
	// rgblight_set_layer_state(0, layer_state_cmp(state, _DEFAULTS) && layer_state_cmp(default_layer_state,_BASE_LAYER));
	// rgblight_set_layer_state(7, layer_state_cmp(state, _DEFAULTS) && layer_state_cmp(default_layer_state,_COLEMAKDH));
	rgblight_set_layer_state(0, layer_state_cmp(state, _BASE_LAYER));
	rgblight_set_layer_state(1, layer_state_cmp(state, _SYMBOLS_LAYER));
	rgblight_set_layer_state(2, layer_state_cmp(state, _MOUSE_LAYER));
	rgblight_set_layer_state(3, layer_state_cmp(state, _NAV_LAYER));
	// rgblight_set_layer_state(4, layer_state_cmp(state, _LAYER4));
	// rgblight_set_layer_state(5, layer_state_cmp(state, _SWITCH));
    return state;
}
void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;

    // skip setting mode, as i think the 'static' animation is what's lighting up whole
    // unskip again.
	rgblight_mode(10);// haven't found a way to set this in a more useful way

}
#endif

#ifdef OLED_ENABLE

int   current_wpm = 0;

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
     0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
     0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
     0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };
    oled_write_P(qmk_logo, false);

//     static const char PROGMEM haloskull[] = {
// // 'haloskull', 64x128px
// 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
// 0xff, 0xff, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x01, 0xff, 0xff, 0xff, 
// 0xff, 0xff, 0xfe, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x7f, 0xff, 0xff, 
// 0xff, 0xff, 0xf8, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x1f, 0xff, 0xff, 
// 0xff, 0xff, 0xf0, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x1f, 0xff, 0xff, 
// 0xff, 0xff, 0xe0, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x0f, 0xff, 0xff, 
// 0xff, 0xff, 0xe0, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x07, 0xff, 0xff, 
// 0xff, 0xff, 0xc0, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x01, 0xff, 0xff, 
// 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xfc, 0x40, 0x00, 0x00, 0x40, 0x7f, 0xff, 
// 0xff, 0xf8, 0x80, 0x00, 0x00, 0x02, 0x3f, 0xff, 0xff, 0xf1, 0x80, 0x00, 0x00, 0x83, 0x9f, 0xff, 
// 0xff, 0xe7, 0x00, 0x00, 0x00, 0x81, 0xc7, 0xff, 0xff, 0x8f, 0x00, 0x00, 0x00, 0xc1, 0xe3, 0xff, 
// 0xff, 0x1f, 0x00, 0x00, 0x00, 0x60, 0xf1, 0xff, 0xfe, 0x3e, 0x00, 0x00, 0x00, 0x30, 0xf8, 0xff, 
// 0xfc, 0x7e, 0x00, 0x00, 0x01, 0x10, 0xfe, 0x7f, 0xf9, 0xfc, 0x00, 0x00, 0x40, 0x10, 0x7f, 0x1f, 
// 0xe3, 0xfc, 0x00, 0x00, 0x20, 0x30, 0x7f, 0x8f, 0xc7, 0xfc, 0x00, 0x00, 0x08, 0x24, 0x7f, 0xc7, 
// 0x8f, 0xfc, 0x00, 0x00, 0x04, 0xa8, 0x3f, 0xe3, 0x1f, 0xf8, 0x00, 0x00, 0x03, 0xf8, 0x3f, 0xf9, 
// 0x7f, 0xf8, 0x00, 0x00, 0x1f, 0xf8, 0x3f, 0xfc, 0x7f, 0xf8, 0x00, 0x00, 0x01, 0xc0, 0x3f, 0xfe, 
// 0x3f, 0xf8, 0x00, 0x00, 0x03, 0xe0, 0x3f, 0xfc, 0x1f, 0xf8, 0x00, 0x00, 0x00, 0xf0, 0x3f, 0xf8, 
// 0x8f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xf1, 0xc7, 0xf8, 0x00, 0x00, 0x01, 0x08, 0x3f, 0xe3, 
// 0xe3, 0xf0, 0x08, 0x00, 0x01, 0x04, 0x1f, 0xc7, 0xf1, 0xf0, 0x08, 0x00, 0x00, 0x82, 0x0f, 0x8f, 
// 0xf8, 0x60, 0x08, 0x00, 0x00, 0x00, 0x0f, 0x1f, 0xfc, 0x20, 0x08, 0x00, 0x00, 0x00, 0x0e, 0x3f, 
// 0xfe, 0x00, 0x10, 0x00, 0x00, 0x00, 0x04, 0x7f, 0xff, 0x80, 0x10, 0x00, 0x00, 0x00, 0x00, 0xff, 
// 0xff, 0xc0, 0x10, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xc0, 0x10, 0x00, 0x00, 0x00, 0x03, 0xff, 
// 0xff, 0xc0, 0x10, 0x00, 0x00, 0x00, 0x07, 0xff, 0x7f, 0xc0, 0x10, 0x00, 0x00, 0x00, 0x07, 0xfe, 
// 0x3f, 0xc0, 0x18, 0x00, 0x00, 0x00, 0x07, 0xfc, 0x1f, 0xc0, 0x08, 0x00, 0x00, 0x00, 0x07, 0xf8, 
// 0x07, 0xc0, 0x0c, 0x00, 0x00, 0x00, 0x07, 0xf0, 0x43, 0xc0, 0x0c, 0x00, 0x00, 0x00, 0x07, 0xc2, 
// 0xf1, 0xc0, 0x06, 0x00, 0x00, 0x00, 0x07, 0x86, 0xf8, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x07, 0x1f, 
// 0xfc, 0x60, 0x03, 0x00, 0x00, 0x00, 0x0e, 0x3f, 0xfe, 0x20, 0x03, 0x80, 0x00, 0x00, 0x0c, 0x7f, 
// 0xff, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x08, 0xff, 0xff, 0x80, 0x00, 0xc0, 0x00, 0x00, 0x01, 0xff, 
// 0xff, 0xc0, 0x00, 0x40, 0x00, 0x00, 0x03, 0xff, 0xff, 0xe0, 0x00, 0x40, 0x00, 0x00, 0x07, 0xff, 
// 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 
// 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 
// 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 
// 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 
// 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 
// 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 
// 0xff, 0xf8, 0x40, 0x00, 0x00, 0x04, 0x3f, 0xff, 0xff, 0xf0, 0x30, 0x00, 0x00, 0x18, 0x3f, 0xff, 
// 0xff, 0xf0, 0x18, 0x00, 0x00, 0x30, 0x1f, 0xff, 0xff, 0xe0, 0x0c, 0x00, 0x00, 0x60, 0x1f, 0xff, 
// 0xff, 0x80, 0x06, 0x00, 0x00, 0xc0, 0x03, 0xff, 0xff, 0x02, 0x03, 0x80, 0x03, 0x80, 0x01, 0xff, 
// 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
// 0xfe, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xfc, 0x01, 0xc0, 0x00, 0x00, 0x07, 0x80, 0x7f, 
// 0xf8, 0x21, 0xe0, 0x00, 0x00, 0x0f, 0x00, 0x1f, 0xe0, 0x00, 0x78, 0x00, 0x00, 0x1c, 0x04, 0x0f, 
// 0xc0, 0x02, 0x7c, 0x00, 0x00, 0x7c, 0x84, 0x07, 0x80, 0x00, 0x2e, 0x00, 0x00, 0xf8, 0x04, 0x03, 
// 0x00, 0x01, 0x0b, 0xcf, 0xe7, 0xb1, 0x04, 0x01, 0x00, 0x20, 0x93, 0xff, 0xff, 0x92, 0x08, 0x00, 
// 0x00, 0x10, 0x23, 0xff, 0xff, 0xc4, 0x10, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xc0, 0x10, 0x00, 
// 0x00, 0x00, 0x0f, 0xff, 0xff, 0xe2, 0x10, 0x00, 0x00, 0x10, 0x5f, 0xff, 0xff, 0xf4, 0x10, 0x00, 
// 0x00, 0x08, 0x75, 0xff, 0xf7, 0xdc, 0x00, 0x00, 0x00, 0x1f, 0x81, 0xff, 0xf7, 0x03, 0xf0, 0x00, 
// 0x00, 0x3f, 0xc0, 0xcf, 0xe6, 0x03, 0xf8, 0x00, 0x00, 0x7f, 0xc0, 0x4f, 0xe4, 0x03, 0xfc, 0x00, 
// 0x00, 0xff, 0xc0, 0x4f, 0xe4, 0x07, 0xfe, 0x00, 0x01, 0xff, 0xc0, 0x4f, 0xe0, 0x07, 0xff, 0x00, 
// 0x07, 0xff, 0xc0, 0x0f, 0xe0, 0x07, 0xff, 0xe0, 0x03, 0xff, 0xe0, 0x0f, 0xf0, 0x07, 0xff, 0xc0, 
// 0x03, 0xff, 0xe0, 0x0f, 0xe0, 0x07, 0xff, 0x80, 0x01, 0xff, 0xc0, 0x07, 0xe0, 0x07, 0xff, 0x80, 
// 0x80, 0xff, 0xc0, 0x07, 0xc0, 0x07, 0xff, 0x01, 0xc0, 0x7f, 0xc0, 0x1f, 0xf0, 0x07, 0xfe, 0x03, 
// 0xc0, 0x3f, 0xe0, 0x3f, 0xf8, 0x07, 0xfc, 0x03, 0xe0, 0x1f, 0xf0, 0x78, 0x3c, 0x1f, 0xf8, 0x07, 
// 0xf0, 0x1f, 0xfc, 0xf8, 0x1e, 0x3f, 0xf0, 0x0f, 0xf8, 0x0f, 0xff, 0xf9, 0x9f, 0xff, 0xf0, 0x1f, 
// 0xfc, 0x07, 0xff, 0xf9, 0x9f, 0xff, 0xe0, 0x3f, 0xfe, 0x03, 0xff, 0xf9, 0x9f, 0xff, 0xc0, 0x7f, 
// 0xff, 0x01, 0xff, 0xf9, 0x9f, 0xff, 0x80, 0xff, 0xff, 0x00, 0xff, 0xf9, 0x9f, 0xff, 0x00, 0xff, 
// 0xff, 0x80, 0x7f, 0xf9, 0x9f, 0xfe, 0x01, 0xff, 0xff, 0xc0, 0x7f, 0xf9, 0x9f, 0xfe, 0x03, 0xff, 
// 0xff, 0xe0, 0x3f, 0xf9, 0x9f, 0xfc, 0x07, 0xff, 0xff, 0xf0, 0x1f, 0xf1, 0x8f, 0xf8, 0x0f, 0xff, 
// 0xff, 0xf8, 0x0f, 0xe1, 0x87, 0xf0, 0x1f, 0xff, 0xff, 0xfc, 0x07, 0xc1, 0x83, 0xe0, 0x3f, 0xff, 
// 0xff, 0xfc, 0x03, 0xc1, 0x83, 0xc0, 0x7f, 0xff, 0xff, 0xfe, 0x00, 0x01, 0x80, 0x00, 0x7f, 0xff, 
// 0xff, 0xff, 0x00, 0x01, 0x80, 0x00, 0xff, 0xff, 0xff, 0xff, 0x80, 0x01, 0x80, 0x01, 0xff, 0xff, 
// 0xff, 0xff, 0xc0, 0x03, 0xc0, 0x03, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x07, 0xe0, 0x07, 0xff, 0xff, 
// 0xff, 0xff, 0xf0, 0x07, 0xe0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x07, 0xe0, 0x1f, 0xff, 0xff, 
// 0xff, 0xff, 0xf8, 0x07, 0xe0, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
// 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
//     };

//     oled_write_raw_P(haloskull,sizeof(haloskull));
    // static const char PROGMEM linux_logo[] = {
    //     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0x27, 0x27, 0x8f, 0x9f, 0x03, 0x73, 0xff, 0x03, 0xf2, 0xfe, 
    //     0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    //     0x1f, 0x19, 0x19, 0x1b, 0x1b, 0x1b, 0x1a, 0x18, 0x18, 0x1f, 0x1f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    // };
    // oled_set_cursor(0, 0);
    // oled_write_raw_P(linux_logo, sizeof(linux_logo));
}

static void print_status_narrow(void) {
    // Print some status stuff around current layer.
    // shove my name here so people know it's my board :)
    oled_write_ln_P(PSTR("Corey\nLeis"), false);
    oled_write_ln_P(PSTR(""), false);
    oled_write_P(PSTR("-----"), false);
    oled_write_ln_P(PSTR(""), false);
    // Print current layer
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case _BASE_LAYER:
            oled_write_ln_P(PSTR("Base "), false);
            break;
        case _SYMBOLS_LAYER:
            oled_write_ln_P(PSTR("Smbls"), false);
            break;
        case _MOUSE_LAYER:
            oled_write_ln_P(PSTR("Mouse"), false);
            break;
        case _NAV_LAYER:
            oled_write_ln_P(PSTR("Arrow"), false);
            break;
        case _LAYER4:
            oled_write_ln_P(PSTR("Media"), false);
            break;

        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }

    #ifdef WPM_ENABLE
    oled_write_P(PSTR("-----"), false);
    oled_write_ln_P(PSTR(""), false);
    current_wpm = get_current_wpm();
    char wpm_st[5];
    snprintf(wpm_st, sizeof(wpm_st), "%d", current_wpm);

    oled_write_ln_P(PSTR("Curr\nWPM:\n"), false);
    oled_write_ln(wpm_st, false);
    #endif
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }
    return false;
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LAYER0:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_BASE_LAYER);
            }
            return false;
        // case KC_COLEMAK:
        //     if (record->event.pressed) {
        //         set_single_persistent_default_layer(_COLEMAK);
        //     }
        //     return false;
        // case KC_COLEMAKDH:
        //     if (record->event.pressed) {
        //         set_single_persistent_default_layer(_COLEMAKDH);
        //     }
        //     return false;
        // case KC_LOWER:
        //     if (record->event.pressed) {
        //         layer_on(_LOWER);
        //         update_tri_layer(_LOWER, _RAISE, _ADJUST);
        //     } else {
        //         layer_off(_LOWER);
        //         update_tri_layer(_LOWER, _RAISE, _ADJUST);
        //     }
        //     return false;
        // case KC_RAISE:
        //     if (record->event.pressed) {
        //         layer_on(_RAISE);
        //         update_tri_layer(_LOWER, _RAISE, _ADJUST);
        //     } else {
        //         layer_off(_RAISE);
        //         update_tri_layer(_LOWER, _RAISE, _ADJUST);
        //     }
        //     return false;
        // case KC_ADJUST:
        //     if (record->event.pressed) {
        //         layer_on(_ADJUST);
        //     } else {
        //         layer_off(_ADJUST);
        //     }
        //     return false;
        // case KC_D_MUTE:
        //     if (record->event.pressed) {
        //         register_mods(mod_config(MOD_MEH));
        //         register_code(KC_UP);
        //     } else {
        //         unregister_mods(mod_config(MOD_MEH));
        //         unregister_code(KC_UP);
        //     }
    }
    return true;
}

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    //returning early for now as something separate seems to be doing volume for me on the encoders, and dual function isn't as fun as it seems
    // return true;
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } 
    if (index == 1) {
        switch (get_highest_layer(layer_state)) {
            case _BASE_LAYER:
                if (clockwise) {
                    tap_code(KC_PGDN);
                } else {
                    tap_code(KC_PGUP);
                }
                break;
            case _MOUSE_LAYER:
            case _NAV_LAYER:
                    if (clockwise) {
                        tap_code(KC_DOWN);
                    } else {
                        tap_code(KC_UP);
                    }
                break;
            case _SYMBOLS_LAYER:
            default:
                    if (clockwise) {
                        tap_code(KC_WH_D);
                    } else {
                        tap_code(KC_WH_U);
                    }
                break;
		}
    }
    return false;
}

#endif
