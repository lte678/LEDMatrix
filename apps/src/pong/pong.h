//
// Created by leon on 29.05.19.
//

#ifndef MATRIX_APPS_PONG_H
#define MATRIX_APPS_PONG_H

#include "MatrixApp.h"

#include <cstdlib>
//#include <cmath>

class PongApp : public MatrixApp {
public:
    explicit PongApp(matrix_t *inMatrix);

    void drawFrame(float dt) override;

private:
    void updateAI();
    void updateGame();
    void drawElements();
    void newGame();

    bool m_P1_AI;
    bool m_P2_AI;

    float m_P1_Paddle;
    float m_P2_Paddle;

    float m_BallSpeed;
    float m_BallX;
    float m_BallY;
    float m_BallXV;
    float m_BallYV;
};

#endif //MATRIX_APPS_PONG_H
