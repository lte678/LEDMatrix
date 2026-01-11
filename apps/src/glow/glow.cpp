//
// Created by leon on 14.07.18.
//

#include "glow.h"


GlowApp::GlowApp(matrix_t *inMatrix) : MatrixApp(inMatrix, "glow"),
    m_Color("color", 40, 0, 0, 255) {
    registerProperty(&m_Color);
}

void GlowApp::drawFrame(float dt) {
    for (int i = 0; i < LED_WIDTH; i++) {
        for (int j = 0; j < LED_HEIGHT; j++) {
            (*m_Matrix)[i][j].r = (u_char)m_Color.getR();
            (*m_Matrix)[i][j].g = (u_char)m_Color.getG();
            (*m_Matrix)[i][j].b = (u_char)m_Color.getB();
            (*m_Matrix)[i][j].w = (u_char)m_Color.getW();
        }
    }
}