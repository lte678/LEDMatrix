//
// Created by leon on 13.07.18.
//

#ifndef MATRIX_DEFINES_H
#define MATRIX_DEFINES_H

#include "ws281x/ws2811.h"

#define LED_WIDTH 10
#define LED_HEIGHT 20
#define LED_COUNT (LED_WIDTH * LED_HEIGHT)

#define GPIO_PIN 18

union pixel_t {
    ws2811_led_t data;
    struct {
        u_char b;
        u_char r;
        u_char g;
        u_char w;
    };

    pixel_t(u_char _r, u_char _g, u_char _b, u_char _w) : r(_r), g(_g), b(_b), w(_w) {}
    explicit pixel_t(ws2811_led_t _data) : data(_data) {}
    pixel_t() : data(0) {}
    pixel_t& operator = (u_char value) { r = value; g = value; b = value; w = value; return *this; };
};

typedef pixel_t matrix_t[LED_WIDTH][LED_HEIGHT];

#endif