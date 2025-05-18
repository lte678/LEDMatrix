//
// Created by leon on 13.07.18.
//

#ifndef MATRIXIFACE_LAVA_H
#define MATRIXIFACE_LAVA_H

#include "MatrixApp.h"
#include "MatrixDefines.h"
#include "AACanvas.h"

#include <cstdlib>
#include <cmath>

class LavaApp : public MatrixApp {
private:
    class Blob {
    public:
        // State variables
        float x;
        float y;
        float velocity;
        float angle;
        float strength;

        // Runtime constants
        float maxVelocity;
        float jitter;
        float scale;

    public:
        Blob(float _maxVelocity, float _jitter, float _scale);

        float valueFunction(float _x, float _y) const;
        void updateBlob(float dt);
        bool outOfBounds() const;
    };
public:
    explicit LavaApp(matrix_t *inMatrix);

    void initApp() override;
    void drawFrame(float dt) override;
    float getPixelValue(float x, float y);
private:
    FloatProperty m_FlowRate;
    FloatProperty m_Size;
    FloatProperty m_Jitter;
    IntProperty m_NumberBlobs;
    ColorProperty m_BlobColor;

    std::vector<Blob> m_blobs;

    AACanvas canvas;
};

extern "C" MatrixApp* create(matrix_t *inMatrix) {
    return new LavaApp(inMatrix);
}

extern "C" void destroy(MatrixApp* app) {
    delete app;
}

#endif //MATRIXIFACE_LAVA_H
