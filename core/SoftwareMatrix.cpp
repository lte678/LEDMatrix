//
// Created by leon on 07.05.19.
//

#include "MatrixManager.h"
#include "SoftwareMatrix.h"
#include "SDL3/SDL_video.h"

#include <iostream>
#include <SDL3/SDL.h>


bool SoftwareMatrix::init() {
    if(!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL failed to initialize." << std::endl;
        exit(1);
    }

    m_Window = SDL_CreateWindow("LED Matrix Simulator", 320, 640, 0);
    if(m_Window == nullptr) {
        std::cerr << "Failed to create window." << std::endl;
        exit(1);
    }

    m_WindowSurface = SDL_GetWindowSurface(m_Window);
    if(m_WindowSurface == nullptr) {
        std::cerr << "Failed to create window surface." << std::endl;
        exit(1);
    }

    return true;
}

void SoftwareMatrix::shutdown() {
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

    SDL_UpdateWindowSurface(m_Window);
}

void SoftwareMatrix::setBrightness(uint8_t brightness) {
}