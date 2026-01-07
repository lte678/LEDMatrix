#pragma once

#include "Matrix.h"

class SoftwareMatrix : public Matrix {
public:
    explicit SoftwareMatrix() {}

    bool init() override;
    void shutdown() override;
    void render(const matrix_t &) override;
    void setBrightness(uint8_t brightness) override;
};