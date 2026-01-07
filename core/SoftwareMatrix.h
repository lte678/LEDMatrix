#pragma once

#include "Matrix.h"

#include <SDL3/SDL_video.h>


class SoftwareMatrix : public Matrix {
private:
    SDL_Window* m_Window;
    SDL_Surface* m_WindowSurface;
public:
    explicit SoftwareMatrix() {}

    bool init() override;
    void shutdown() override;
    void render(const matrix_t &) override;
    void setBrightness(uint8_t brightness) override;
};