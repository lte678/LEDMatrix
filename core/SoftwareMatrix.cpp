//
// Created by leon on 07.05.19.
//

#include "MatrixDefines.h"
#include "Globals.h"
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

    // Create hardware-accelerated renderer
    m_Renderer = SDL_CreateRenderer(m_Window, nullptr);
    if(m_Renderer == nullptr) {
        std::cerr << "Failed to create renderer." << std::endl;
        exit(1);
    }

    // Create a circular blur effect
    SDL_Surface* tempSurface = SDL_CreateSurface(LED_GLOW_TEXTURE_SIZE, LED_GLOW_TEXTURE_SIZE, SDL_PIXELFORMAT_RGBA32);    
    for (int i = 0; i < LED_GLOW_TEXTURE_SIZE; i++) {
        for (int j = 0; j < LED_GLOW_TEXTURE_SIZE; j++) {
            float x = 2 * ((i - 0.5f*LED_GLOW_TEXTURE_SIZE) / LED_GLOW_TEXTURE_SIZE);
            float y = 2 * ((j - 0.5f*LED_GLOW_TEXTURE_SIZE) / LED_GLOW_TEXTURE_SIZE);
            float value = std::max(0.0f, static_cast<float>(std::exp((-std::pow(x*x + y*y, 1.5)) - std::exp(-1.0f)) / (1.0f - std::exp(-1.0f))));
            SDL_WriteSurfacePixelFloat(tempSurface, i, j, value, value, value, 1.0f);
        }
    }

    // Convert surface to hardware texture
    m_LedGlowTexture = SDL_CreateTextureFromSurface(m_Renderer, tempSurface);
    SDL_DestroySurface(tempSurface);
    
    SDL_SetTextureBlendMode(m_LedGlowTexture, SDL_BLENDMODE_ADD);
    
    return true;
}

void SoftwareMatrix::shutdown() {
    SDL_DestroyTexture(m_LedGlowTexture);
    m_LedGlowTexture = nullptr;

    SDL_DestroyWindow(m_Window);
    m_Window = nullptr;
    m_WindowSurface = nullptr;

    SDL_Quit();
}

void SoftwareMatrix::render(const matrix_t &matrixData) {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        if(e.type == SDL_EVENT_QUIT) exitapp(0);
    }

    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_Renderer);
    
    float stride = static_cast<float>(WINDOW_WIDTH) / LED_WIDTH;
    for (int i = 0; i < LED_WIDTH; i++) {
        for (int j = 0; j < LED_HEIGHT; j++) {
            int center_x = 0.5 * stride + stride * i;
            int center_y = 0.5 * stride + stride * j;
            SDL_FRect target = {
                center_x - 0.5f*LED_GLOW_TEXTURE_SIZE,
                center_y - 0.5f*LED_GLOW_TEXTURE_SIZE,
                static_cast<float>(LED_GLOW_TEXTURE_SIZE),
                static_cast<float>(LED_GLOW_TEXTURE_SIZE)
            };
            
            pixel_t pixel = matrixData[i][j];
            uint8_t r, g, b;
            std::tie(r, g, b) = map_rgbw_to_rgb(pixel.r, pixel.g, pixel.b, pixel.w);
            SDL_SetTextureColorMod(m_LedGlowTexture, r * m_Brightness, g * m_Brightness, b * m_Brightness);
            SDL_RenderTexture(m_Renderer, m_LedGlowTexture, nullptr, &target);
        }
    }
    SDL_RenderPresent(m_Renderer);
}

void SoftwareMatrix::setBrightness(uint8_t brightness) {
    m_Brightness = static_cast<float>(brightness) / 255.0f;
}