//
// Created by leon on 13.07.18.
//

#ifndef MATRIXIFACE_LIGHTSPEED_H
#define MATRIXIFACE_LIGHTSPEED_H

#include "MatrixApp.h"
#include "MatrixDefines.h"

#include <cstdlib>
#include <math.h>
#include <vector>
#include <iostream>

class LightspeedApp : public MatrixApp {
public:
    LightspeedApp(matrix_t *inMatrix);

    virtual void drawFrame(float dt);
    virtual void initApp();
private:
    struct LightRay {
        float heading; // Angle around center in radians
        float radius; // Distance from center
        float distance; // Distance from camera
    };

    FloatProperty m_Speed;
    //FloatProperty m_Length;
    IntProperty m_Number;

    float m_FOV;
    float m_StartingDistance;
    float m_MaxRadius; //Beyond this radial distance our star is never visible
    float m_MatrixRadius;

    std::vector<LightRay> m_Rays;
    
    void drawRay(const LightRay& ray);
    void newRay();
    bool rayInBounds(const LightRay& ray);
};


extern "C" MatrixApp* create(matrix_t *inMatrix) {
    return new LightspeedApp(inMatrix);
}

extern "C" void destroy(MatrixApp* app) {
    delete app;
}

#endif //MATRIXIFACE_LIGHTSPEED_H
