//
// Created by leon on 13.07.18.
//

#ifndef MATRIXIFACE_SPARKLES_H
#define MATRIXIFACE_SPARKLES_H

#include "MatrixApp.h"
#include "MatrixDefines.h"

#include <cstdlib>

class SparklesApp : public MatrixApp {
public:
    SparklesApp(matrix_t *inMatrix);

    virtual void drawFrame(float dt);
private:
    float sparkleCount;

    FloatProperty m_FadeSpeed;
    FloatProperty m_SparkleRate;
};


extern "C" MatrixApp* create(matrix_t *inMatrix) {
    return new SparklesApp(inMatrix);
}

extern "C" void destroy(MatrixApp* app) {
    delete app;
}

#endif //MATRIXIFACE_SPARKLES_H
