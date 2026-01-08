//
// Created by leon on 13.07.18.
//

//The colors are arranged by: WWGGRRBB

#include "wipe.h"

WipeApp::WipeApp(matrix_t *inMatrix) : MatrixApp(inMatrix, "wipe"),
    m_WipeRate("wiperate", 5.0f),
    m_Dithering("dithering", 2.0f) {

    registerProperty(&m_WipeRate);
    registerProperty(&m_Dithering); // Linear dithering

    m_FrameRate = 60; //Override defualt framerate of 10fps

    // The half-diagonal of the matrix (or radius if inscribed in circle), used to make sure our wipe starts outside the draw area
    m_MatrixRadius = sqrt(((float)LED_WIDTH)*((float)LED_WIDTH)*0.25f + ((float)LED_HEIGHT)*((float)LED_HEIGHT)*0.25f);
    newWipe();
}

void WipeApp::drawFrame(float dt) {
    m_CurrentPosition += dt*(float)m_WipeRate;
    float lineX = (float)LED_WIDTH / 2.0f + m_CurrentPosition * m_CurrentNormalX;
    float lineY = (float)LED_HEIGHT / 2.0f + m_CurrentPosition * m_CurrentNormalY;
    fillDiagonal(m_CurrentNormalX, m_CurrentNormalY, lineX, lineY);

    // Start wiping again from another position outside the matrix
    if (m_CurrentPosition >= m_MatrixRadius) {
        newWipe();
    }
}

void WipeApp::fillDiagonal(float n_x, float n_y, float p_x, float p_y) {
    // Fills the space behing the diagonal defined by the normal vector n and point p
    // Coordinate system starts at bottom left of matrix

    for (int x = 0; x < LED_WIDTH; x++) {
        for(int y = 0; y < LED_HEIGHT; y++) {
            // A vector from the current pixel to a point on the line
            float v_x  = x - p_x;
            float v_y = y - p_y;
            // The distance of the point to the line. This is the dot product with the normal
            float dist = v_x * n_x + v_y * n_y;
            // side = 0: new side. side = 1: old side.
            float side = 0.0f;
            if(m_Dithering != 0.0f) {
                side = (dist / m_Dithering + 1.0f) * 0.5f;
                if(side < 0.0f) side = 0.0f;
                if(side > 1.0f) side = 1.0f;
            } else {
                side = dist <= 0.0f ? 0.0f : 1.0f;
            }
            pixel_t color(side * m_PreviousColor.r + (1.0f - side) * m_CurrentColor.r,
                          side * m_PreviousColor.g + (1.0f - side) * m_CurrentColor.g,
                          side * m_PreviousColor.b + (1.0f - side) * m_CurrentColor.b,
                          side * m_PreviousColor.w + (1.0f - side) * m_CurrentColor.w);
            (*m_Matrix)[x][y] = color;
        }
    }
}

void WipeApp::newWipe() {
    float angle = (rand() % 1000) / 1000.0f * 2 * 3.14159f;
    m_CurrentNormalX = sin(angle);
    m_CurrentNormalY = cos(angle);
    m_CurrentPosition = -m_MatrixRadius;

    m_PreviousColor = m_CurrentColor;
    m_CurrentColor = MatrixApp::randomRGB();
}