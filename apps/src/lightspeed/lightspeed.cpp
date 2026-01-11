//
// Created by leon on 13.07.18.
//

//The colors are arranged by: WWGGRRBB

#include "lightspeed.h"

LightspeedApp::LightspeedApp(matrix_t *inMatrix) : MatrixApp(inMatrix, "lightspeed"),
    m_Speed("speed", 50.0f),
    m_Number("number", 15) {

    registerProperty(&m_Speed);
    registerProperty(&m_Number);

    m_FOV =  atan(3.14159f / 4.0f); // maximum slope of ray from camera when looking a diagonal
    m_StartingDistance = 100.0f;
    m_MaxRadius = m_FOV * m_StartingDistance;
    m_MatrixRadius = sqrt(((float)LED_WIDTH)*((float)LED_WIDTH)*0.25f + ((float)LED_HEIGHT)*((float)LED_HEIGHT)*0.25f);
}

void LightspeedApp::initApp() {
    m_Rays.clear();
    for(int i = 0; i < (int)m_Number; i++) {
        newRay();
    }
}

void LightspeedApp::drawFrame(float dt) {
    clearMatrix(m_Matrix);
    for (int i = m_Rays.size() - 1; i >= 0; i--) {
        if(rayInBounds(m_Rays.at(i))) {
            drawRay(m_Rays.at(i));
        } else {
            m_Rays.erase(m_Rays.begin() + i);
            newRay();
        }
        m_Rays.at(i).distance -= m_Speed * dt;
    }
}

void LightspeedApp::newRay() {
    LightRay ray = {
            ((rand() % 1001) / 1000.0f) * 2 * 3.14159f,
            ((rand() % 1001) / 1000.0f) * m_MaxRadius,
            m_StartingDistance};

    m_Rays.push_back(ray);
}

bool LightspeedApp::rayInBounds(const LightRay &ray) {
    return ray.radius / ray.distance < m_FOV;
}

void LightspeedApp::drawRay(const LightRay &ray) {
    float displayRadius = ((ray.radius / ray.distance) / m_FOV) * m_MatrixRadius;
    int displayX = (int)(displayRadius * sin(ray.heading)) + LED_WIDTH / 2;
    int displayY = (int)(displayRadius * cos(ray.heading)) + LED_HEIGHT / 2;
    int brightness = (1.0f - ray.distance / m_StartingDistance) * 255;
    brightness = brightness > 255 ? 255 : brightness;
    brightness = brightness < 0 ? 0 : brightness;
    //std::cout << displayX << ", " << displayY << std::endl;
    if(displayX >= 0 && displayX < LED_WIDTH && displayY >= 0 && displayY < LED_HEIGHT) {
        (*m_Matrix)[displayX][displayY] = pixel_t(0, 0, brightness * 0.8f, brightness);
    }
}