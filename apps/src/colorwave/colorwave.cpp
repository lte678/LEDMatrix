//
// Created by leon on 14.07.18.
//

#include "colorwave.h"


ColorwaveApp::ColorwaveApp(matrix_t *inMatrix) : MatrixApp(inMatrix, "colorwave"),
    m_FadeSpeed("fadespeed", 25) {

    registerProperty(&m_FadeSpeed);

    m_FrameRate = 25; //Override default framerate of 10fps
    time = 0.0f;

    noiseGenR.SetNoiseType(FastNoise::Perlin);
    noiseGenG.SetNoiseType(FastNoise::Perlin);
    noiseGenG.SetSeed(102310230);
    noiseGenB.SetNoiseType(FastNoise::Perlin);
    noiseGenB.SetSeed(-23123);
}

void ColorwaveApp::drawFrame(float dt) {
    time+=dt;
    for (int i = 0; i < LED_WIDTH; i++) {
        for (int j = 0; j < LED_HEIGHT; j++) {
            /*
            (*m_matrix)[i][j].r = (u_char)((noiseGenR.GetNoise(i*20, j*20, time * stof(m_Properties["rate@float"])) + 0.5f)  * 256.0f);
            (*m_matrix)[i][j].g = (u_char)((noiseGenG.GetNoise(i*20, j*20, time * stof(m_Properties["rate@float"]) + 10000.0f) + 0.5f)  * 256.0f);
            (*m_matrix)[i][j].b = (u_char)((noiseGenB.GetNoise(i*20, j*20, time * stof(m_Properties["rate@float"]) + 20000.0f) + 0.5f)  * 256.0f);
            Produces cool effect
            */
            float rval = (noiseGenR.GetNoise(i*15, j*15, time * m_FadeSpeed) + 0.5f)  * 256.0f;
            float gval = (noiseGenG.GetNoise(i*15, j*15, time * m_FadeSpeed + 10000.0f) + 0.5f)  * 256.0f;
            float bval = (noiseGenB.GetNoise(i*15, j*15, time * m_FadeSpeed + 20000.0f) + 0.5f)  * 256.0f;
            (rval < 0.0f) ? rval = 0.0f : ((rval > 255.0f) ? rval = 255.0f : rval = rval);
            (gval < 0.0f) ? gval = 0.0f : ((gval > 255.0f) ? gval = 255.0f : gval = gval);
            (bval < 0.0f) ? bval = 0.0f : ((bval > 255.0f) ? bval = 255.0f : bval = bval);
            (*m_Matrix)[i][j].r = (u_char)rval;
            (*m_Matrix)[i][j].g = (u_char)gval;
            (*m_Matrix)[i][j].b = (u_char)bval;
        }
    }

    //Code to test/calibrate perlin noise range
    //std::cout << ((noiseGenR.GetNoise(5, 10, time * stof(m_Properties["rate@float"])) + 0.5f)  * 256.0f) << std::endl;
}