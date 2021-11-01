//
// Created by leon on 13.07.18.
//

#ifndef MATRIXIFACE_WIPE_H
#define MATRIXIFACE_WIPE_H

#include "MatrixApp.h"
#include "MatrixDefines.h"

#include <cstdlib>
#include <math.h>

class WipeApp : public MatrixApp {
public:
    WipeApp(matrix_t *inMatrix);

    virtual void drawFrame(float dt);
    void fillDiagonal(float n_x, float n_y, float p_x, float p_y);
    void newWipe();
private:
    FloatProperty m_WipeRate;
    FloatProperty m_Dithering;

    float m_MatrixRadius; // Doesn't change, just as a cache

    pixel_t m_PreviousColor;
    pixel_t m_CurrentColor;
    float m_CurrentNormalX;
    float m_CurrentNormalY;
    float m_CurrentPosition;
};


extern "C" MatrixApp* create(matrix_t *inMatrix) {
    return new WipeApp(inMatrix);
}

extern "C" void destroy(MatrixApp* app) {
    delete app;
}

#endif //MATRIXIFACE_WIPE_H
