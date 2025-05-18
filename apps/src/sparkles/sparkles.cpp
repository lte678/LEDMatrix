//
// Created by leon on 13.07.18.
//

//The colors are arranged by: WWGGRRBB

#include "sparkles.h"

SparklesApp::SparklesApp(matrix_t *inMatrix) : MatrixApp(inMatrix, "sparkles"),
    m_FadeSpeed("fadespeed", 0.15),
    m_SparkleRate("sparklerate", 30){
    m_FrameRate = 25; //Override defualt framerate of 10fps

    registerProperty(&m_FadeSpeed);
    registerProperty(&m_SparkleRate);
}

void SparklesApp::drawFrame(float dt) {
    sparkleCount += m_SparkleRate * dt;
    while(sparkleCount >= 1.0f) {
        (*m_Matrix)[rand() % LED_WIDTH][rand() % LED_HEIGHT] = pixel_t(255, 100, 200, 50);
        sparkleCount--;
    }
    MatrixApp::multiplyMatrix(m_Matrix, 1.0f - m_FadeSpeed);
}