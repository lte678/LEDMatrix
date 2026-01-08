//
// Created by leon on 07.05.19.
//

#include "MatrixDefines.h"
#include "MatrixManager.h"
#include "SoftwareMatrix.h"
#include "SDL3/SDL_surface.h"
#include "SDL3/SDL_video.h"

#include <cmath>
#include <iostream>
#include <SDL3/SDL.h>
#include <tuple>


static std::tuple<uint8_t, uint8_t, uint8_t> map_rgbw_to_rgb(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
    return std::make_tuple(r * 0.7 + w * 0.3, g * 0.7 + w * 0.3, b * 0.7 + w * 0.3);
}

bool SoftwareMatrix::init() {
    if(!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL failed to initialize." << std::endl;
        exit(1);
    }

    m_Window = SDL_CreateWindow("LED Matrix Simulator", WINDOW_WIDTH, WINDOW_WIDTH * (LED_HEIGHT / LED_WIDTH), 0);
    if(m_Window == nullptr) {
        std::cerr << "Failed to create window." << std::endl;
        exit(1);
    }

    m_WindowSurface = SDL_GetWindowSurface(m_Window);
    if(m_WindowSurface == nullptr) {
        std::cerr << "Failed to create window surface." << std::endl;
        exit(1);
    }

    // Prepare the led texture
    m_LedGlowTexture = SDL_CreateSurface(LED_GLOW_TEXTURE_SIZE, LED_GLOW_TEXTURE_SIZE, SDL_PIXELFORMAT_RGBA32);
    if(m_LedGlowTexture == nullptr || !SDL_ClearSurface(m_LedGlowTexture, 1.0, 1.0, 1.0, 1.0)) {
        std::cerr << "Failed to create texture." << std::endl;
        exit(1);
    }

    // Create a circular blur effect
    for (int i = 0; i < LED_GLOW_TEXTURE_SIZE; i++) {
        for (int j = 0; j < LED_GLOW_TEXTURE_SIZE; j++) {
            float x = 2 * ((i - 0.5f*LED_GLOW_TEXTURE_SIZE) / LED_GLOW_TEXTURE_SIZE);
            float y = 2 * ((j - 0.5f*LED_GLOW_TEXTURE_SIZE) / LED_GLOW_TEXTURE_SIZE);
            float value = std::min((float)std::exp(-2*x*x -2*y*y), 1.0f - std::sqrt(x*x + y*y));
            SDL_WriteSurfacePixelFloat(m_LedGlowTexture, i, j, 1.0, 1.0, 1.0, value);
        }
    }
    SDL_SetSurfaceBlendMode(m_LedGlowTexture, SDL_BLENDMODE_ADD);

    return true;
}

void SoftwareMatrix::shutdown() {
    SDL_DestroySurface(m_LedGlowTexture);
    m_LedGlowTexture = nullptr;

    SDL_DestroyWindow(m_Window);
    m_Window = nullptr;
    m_WindowSurface = nullptr;

    SDL_Quit();
}

void SoftwareMatrix::render(const matrix_t &matrixData) {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        if(e.type == SDL_EVENT_QUIT) {
            g_MatrixManager->stop();
        }
    }

    SDL_ClearSurface(m_WindowSurface, 0.0, 0.0, 0.0, 1.0);
    float stride = static_cast<float>(WINDOW_WIDTH) / LED_WIDTH;
    for (int i = 0; i < LED_WIDTH; i++) {
        for (int j = 0; j < LED_HEIGHT; j++) {
            int center_x = 0.5 * stride + stride * i;
            int center_y = 0.5 * stride + stride * j;
            SDL_Rect target = SDL_Rect{
                static_cast<int>(center_x - 0.5*LED_GLOW_TEXTURE_SIZE),
                static_cast<int>(center_y - 0.5*LED_GLOW_TEXTURE_SIZE),
                LED_GLOW_TEXTURE_SIZE,
                LED_GLOW_TEXTURE_SIZE
            };
            
            pixel_t pixel = matrixData[i][j];
            uint8_t r, g, b;
            std::tie(r, g, b) = map_rgbw_to_rgb(pixel.r, pixel.g, pixel.b, pixel.w);
            SDL_SetSurfaceColorMod(m_LedGlowTexture, r, g, b);
            SDL_BlitSurface(m_LedGlowTexture, nullptr, m_WindowSurface, &target);
        }
    }
    SDL_UpdateWindowSurface(m_Window);
}

void SoftwareMatrix::setBrightness(uint8_t brightness) {
}