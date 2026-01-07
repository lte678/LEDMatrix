//
// Created by leon on 13.07.18.
//

#ifndef MATRIX_DEFINES_H
#define MATRIX_DEFINES_H

#include <cstdint>

#define LED_WIDTH 10
#define LED_HEIGHT 20
#define LED_COUNT (LED_WIDTH * LED_HEIGHT)

#define GPIO_PIN 18

// Compatible with ws2811_led_t structure.
union pixel_t {
    uint32_t data;
    struct {
        uint8_t b;
        uint8_t r;
        uint8_t g;
        uint8_t w;
    };

    pixel_t(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _w) : r(_r), g(_g), b(_b), w(_w) {}
    explicit pixel_t(uint32_t _data) : data(_data) {}
    pixel_t() : data(0) {}
    pixel_t& operator = (uint8_t value) { r = value; g = value; b = value; w = value; return *this; };
};

typedef pixel_t matrix_t[LED_WIDTH][LED_HEIGHT];

#endif