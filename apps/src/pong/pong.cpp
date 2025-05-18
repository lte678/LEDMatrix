//
// Created by leon on 29.05.19.
//

#include "pong.h"

PongApp::PongApp(matrix_t* inMatrix) : MatrixApp(inMatrix, "pong") {
    newGame();
}

void PongApp::newGame() {
    m_BallX = (LED_WIDTH - 1) / 2.0f;
    m_BallY = (LED_HEIGHT - 1) / 2.0f;

    float maxAngle = 3.141f / 4.0f; //About 45 degrees in each direction
    float angle = (((std::rand() % 201 - 100) / 100.0f) - 1.0f) * maxAngle;

    m_BallXV = angle;
    m_BallYV = 0.0f;
}