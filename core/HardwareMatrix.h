#pragma once

#include "Matrix.h"
#include "ws281x/ws2811.h"


class HardwareMatrix : public Matrix {
private:
    ws2811_t m_Matrix;
    int m_GpioPin;
public:
    explicit HardwareMatrix(int gpioPin) : m_GpioPin(gpioPin), m_Matrix() {}

    bool init() override;
    void shutdown() override;
    void render(const matrix_t &) override;
    void setBrightness(uint8_t brightness) override;
};