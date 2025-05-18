//
// Created by leon on 02.11.21.
//

#ifndef MATRIX_AACANVAS_H
#define MATRIX_AACANVAS_H

#include "MatrixDefines.h"
#include <vector>

class AACanvas {
public:
    enum AASamplingScale {
        X1 = 1,
        X2 = 2,
        X4 = 4
    };

    AACanvas(AASamplingScale _scale);

    int getWidth() const;
    int getHeight() const;
    pixel_t getPixel(int x, int y);
    void setPixel(int x, int y, pixel_t pixel);

    void renderToMatrix(matrix_t *matrix);
private:
    int scale;
    unsigned int numPixels;
    std::vector<pixel_t> pixels;

private:
    pixel_t samplePixel(int x, int y);
};


#endif //MATRIX_AACANVAS_H
