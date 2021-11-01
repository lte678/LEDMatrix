//
// Created by leon on 14.07.18.
//

#ifndef MATRIXIFACE_GLOW_H
#define MATRIXIFACE_GLOW_H


#include "MatrixApp.h"
#include "MatrixDefines.h"

#include <cstdlib>
#include <cctype>
#include <iostream>

class GlowApp : public MatrixApp {
public:
    explicit GlowApp(matrix_t *inMatrix);

    void drawFrame(float dt) override;
private:
    ColorProperty m_Color;
};


extern "C" MatrixApp* create(matrix_t *inMatrix) {
    return new GlowApp(inMatrix);
}

extern "C" void destroy(MatrixApp* app) {
    delete app;
}


#endif //MATRIXIFACE_GLOW_H
