//
// Created by leon on 13.07.18.
//

#ifndef MATRIXIFACE_MATRIXAPP_H
#define MATRIXIFACE_MATRIXAPP_H

#include <sys/types.h>
#include <map>
#include <vector>

#include "MatrixDefines.h"
#include "property/Property.h"

class MatrixApp : public PropertyInterface {
public:
    typedef MatrixApp* createApp(matrix_t *inMatrix);
    typedef void destroyApp(MatrixApp* app);


    explicit MatrixApp(matrix_t *inMatrix, std::string id) : m_Matrix(inMatrix), PropertyInterface(id), m_FrameRate("framerate", 10.0f) {
        registerProperty(&m_FrameRate);
    }
    virtual ~MatrixApp() = default;

    virtual void initApp() {}
    virtual void drawFrame(float dt) {}
    virtual void stopApp() {}

    virtual float getFrameRate() {
        return m_FrameRate;
    }
protected:
    matrix_t *m_Matrix;

    static void clearMatrix(matrix_t* matrix) {
        for (int i = 0; i < LED_WIDTH; i++) {
            for (int j = 0; j < LED_HEIGHT; j++) {
                (*matrix)[i][j].data = 0;
            }
        }
    }

    static void multiplyMatrix(matrix_t* matrix, float value) {
        for (int i = 0; i < LED_WIDTH; i++) {
            for (int j = 0; j < LED_HEIGHT; j++) {
                (*matrix)[i][j].r = (u_char)((float)(*matrix)[i][j].r * value);
                (*matrix)[i][j].g = (u_char)((float)(*matrix)[i][j].g * value);
                (*matrix)[i][j].b = (u_char)((float)(*matrix)[i][j].b * value);
                (*matrix)[i][j].w = (u_char)((float)(*matrix)[i][j].w * value);
            }
        }
    }

    static pixel_t randomRGB() {
        return pixel_t(rand() % 256, rand() % 256, rand() % 256, 0);
    }

    static pixel_t randomRGBW() {
        return pixel_t(rand() % 256, rand() % 256, rand() % 256, rand() % 256);
    }

    FloatProperty m_FrameRate;
};

#endif //MATRIXIFACE_MATRIXAPP_H
