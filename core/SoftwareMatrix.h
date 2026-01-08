#pragma once

#include "Matrix.h"

#include <SDL3/SDL_video.h>


constexpr int WINDOW_WIDTH = 320;
constexpr int LED_GLOW_TEXTURE_SIZE = WINDOW_WIDTH / LED_WIDTH;

class SoftwareMatrix : public Matrix {
private:
    SDL_Window* m_Window;
    SDL_Surface* m_WindowSurface;
    SDL_Surface* m_LedGlowTexture;
    float m_Brightness;
public:
    explicit SoftwareMatrix() : m_Brightness(1.0f) {}

    bool init() override;
    void shutdown() override;
    void render(const matrix_t &) override;
    void setBrightness(uint8_t brightness) override;
};