//
// Created by leon on 13.07.18.
//

//The colors are arranged by: WWGGRRBB

#include "sparkles.h"


SparklesApp::SparklesApp(matrix_t *inMatrix) : MatrixApp(inMatrix, "sparkles"),
    m_FadeSpeed("fadespeed", 1.0),
    m_SparkleRate("sparklerate", 15){

    registerProperty(&m_FadeSpeed);
    registerProperty(&m_SparkleRate);
}

void SparklesApp::drawFrame(float dt) {
    sparkleCount += m_SparkleRate * dt;
    while(sparkleCount >= 1.0f) {
        (*m_Matrix)[rand() % LED_WIDTH][rand() % LED_HEIGHT] = pixel_t(255, 100, 200, 50);
        sparkleCount--;
    }
    MatrixApp::multiplyMatrix(m_Matrix, std::max(0.0f, 1.0f - m_FadeSpeed*dt));
}