//
// Created by leon on 13.07.18.
//

#ifndef MATRIX_DEFINES_H
#define MATRIX_DEFINES_H

#include <cstdint>
#include <cstring>

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
    pixel_t& operator=(uint8_t value) { r = value; g = value; b = value; w = value; return *this; };
    pixel_t operator*(float scalar) {
        return {
            static_cast<uint8_t>(r*scalar),
            static_cast<uint8_t>(g*scalar),
            static_cast<uint8_t>(b*scalar),
            static_cast<uint8_t>(w*scalar)
        };
    };
    pixel_t operator+(pixel_t other) {
        return {
            static_cast<uint8_t>(r + other.r),
            static_cast<uint8_t>(g + other.g),
            static_cast<uint8_t>(b + other.b),
            static_cast<uint8_t>(w + other.w)
        };
    };
};

typedef pixel_t matrix_t[LED_WIDTH][LED_HEIGHT];



static void blend_frames(matrix_t out, float factor, matrix_t frame_a, matrix_t frame_b) {
    for(int i = 0; i < LED_WIDTH; i++) {
        for(int j = 0; j < LED_HEIGHT; j++) {
            out[i][j] = frame_a[i][j] * (1.0f - factor) + frame_b[i][j] * factor;
        }
    }
}

static void copy_frame(matrix_t to, matrix_t from) {
    memcpy(to, from, sizeof(pixel_t) * LED_WIDTH * LED_HEIGHT);
}

#endif