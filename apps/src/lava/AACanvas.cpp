//
// Created by leon on 02.11.21.
//

#include "AACanvas.h"

AACanvas::AACanvas(AASamplingScale _scale) {
    scale = _scale;
    numPixels = scale * scale * LED_WIDTH * LED_HEIGHT;

    for(int i = 0; i < numPixels; i++) {
        pixels.emplace_back(0);
    }
}

int AACanvas::getWidth() const {
    return scale * LED_WIDTH;
}

int AACanvas::getHeight() const {
    return scale * LED_HEIGHT;
}

pixel_t AACanvas::getPixel(int x, int y) {
    return pixels.at(x + y * getWidth());
}

void AACanvas::setPixel(int x, int y, pixel_t pixel) {
    pixels.at(x + y * getWidth()) = pixel;
}

void AACanvas::renderToMatrix(matrix_t *matrix) {
    for (int i = 0; i < LED_WIDTH; i++) {
        for (int j = 0; j < LED_HEIGHT; j++) {
            (*matrix)[i][j] = samplePixel(i, j);
        }
    }
}

pixel_t AACanvas::samplePixel(int x, int y) {
    // Input: coordinates of pixel on 20 x 10 matrix canvas.
    // Output: Average of all relevant super-scaled canvas pixels.

    // sup prefix means super scaled index
    int supXmin = x * scale;
    int supXmax = (x + 1) * scale;
    int supYmin = y * scale;
    int supYmax = (y + 1) * scale;

    float s = 1.0f / (float)(scale * scale);
    float newR = 0.0f;
    float newG = 0.0f;
    float newB = 0.0f;
    float newW = 0.0f;
    for (int i = supXmin; i < supXmax; i++) {
        for (int j = supYmin; j < supYmax; j++) {
            pixel_t pixel = getPixel(i, j);
            newR += (float)pixel.r * s;
            newG += (float)pixel.g * s;
            newB += (float)pixel.b * s;
            newW += (float)pixel.w * s;
        }
    }
    return pixel_t((uint8_t)newR, (uint8_t)newG, (uint8_t)newB, (uint8_t)newW);
}