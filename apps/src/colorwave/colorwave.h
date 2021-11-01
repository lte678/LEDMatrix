//
// Created by leon on 14.07.18.
//

#ifndef MATRIXIFACE_COLORWAVE_H
#define MATRIXIFACE_COLORWAVE_H


#include "MatrixApp.h"
#include "MatrixDefines.h"

#include <cstdlib>
#include <iostream>
//#include <algorithm> STD::CLAMP not implemented in C++14. SHit.
#include "fastnoise/FastNoise.h"

class ColorwaveApp : public MatrixApp {
public:
    explicit ColorwaveApp(matrix_t *inMatrix);

    void drawFrame(float dt) override;
private:
    FastNoise noiseGenR, noiseGenG, noiseGenB;
    FloatProperty m_FadeSpeed;
    float time;
};


extern "C" MatrixApp* create(matrix_t *inMatrix) {
    return new ColorwaveApp(inMatrix);
}

extern "C" void destroy(MatrixApp* app) {
    delete app;
}


#endif //MATRIXIFACE_COLORWAVE_H
