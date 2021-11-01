//
// Created by leon on 13.07.18.
//

#ifndef MATRIXIFACE_LAVA_H
#define MATRIXIFACE_LAVA_H

#include "MatrixApp.h"
#include "MatrixDefines.h"

#include <cstdlib>
#include <math.h>

class LavaApp : public MatrixApp {
private:
    class Blob {
    public:
        float x;
        float y;
        float velocity;
        float angle;
        float strength;

        Blob();

        float valueFunction(int _x, int _y);
    };
public:
    LavaApp(matrix_t *inMatrix);

    virtual void drawFrame(float dt);
    float getPixelValue(int x, int y);

private:
    FloatProperty m_FlowRate;
    FloatProperty m_Size;

    std::vector<>
};

extern "C" MatrixApp* create(matrix_t *inMatrix) {
    return new LavaApp(inMatrix);
}

extern "C" void destroy(MatrixApp* app) {
    delete app;
}

#endif //MATRIXIFACE_LAVA_H
