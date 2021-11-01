//
// Created by leon on 13.07.18.
//

//The colors are arranged by: WWGGRRBB

#include "lava.h"

LavaApp::Blob::Blob() {
    x =
    velocity = random(maxVelocity);
    angle = random(2*PI);
    strength = _strength;
}

float LavaApp::Blob::valueFunction(int _x, int _y) {
    float distance = sqrt((_x - x)*(_x - x) +(_y - y)*(_y - y)) * 0.02f;
    return 1.0f / ((distance + distance*distance*distance) * strength);
}

LavaApp::LavaApp(matrix_t *inMatrix) : MatrixApp(inMatrix, "lava"),
    m_FlowRate("flowrate", 0.1f),
    m_Size("size", 2.0f) {

    registerProperty(&m_FlowRate);
    registerProperty(&m_Size);

    m_FrameRate = 60; //Override defualt framerate of 10fps
}

void LavaApp::drawFrame(float dt) {
    for (int i = 0; i < LED_WIDTH; i++) {
        for (int j = 0; j < LED_HEIGHT; j++) {
            float pixelValue = getPixelValue(i, j);
        }
    }
}

float LavaApp::getPixelValue(int x, int y) {

}