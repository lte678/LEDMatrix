//
// Created by leon on 13.07.18.
//

//The colors are arranged by: WWGGRRBB

#include "lava.h"

LavaApp::Blob::Blob(float _maxVelocity, float _jitter, float _scale) {
    x = random_float(LED_WIDTH);
    y = random_float(LED_HEIGHT);
    velocity = random_float(_maxVelocity);
    angle = random_float(M_PI_2);
    strength = random_float(0.8f) + 0.2f;

    maxVelocity = _maxVelocity;
    jitter = _jitter;
    scale = _scale;
}

float LavaApp::Blob::valueFunction(float _x, float _y) const {
    float distance = sqrt((_x - x)*(_x - x) +(_y - y)*(_y - y)) / scale;
    return 1.0f / ((distance + distance*distance*distance) * strength);
}

void LavaApp::Blob::updateBlob(float dt) {
    // Update acceleration
    float acceleration = maxVelocity / 30.0f; // This is an arbitrary scaling factor
    velocity += random_float(-acceleration,  acceleration) * dt;
    velocity = fmax(fmin(velocity, maxVelocity), 0.0f);

    // Update angle
    angle += random_float(-jitter, jitter) * dt;

    // If we have travelled to far off-screen, turn around.
    if(outOfBounds()) {
        angle += M_PI;
    }

    // Increment positions
    x += velocity * cos(angle) * dt;
    y += velocity * sin(angle) * dt;
}

bool LavaApp::Blob::outOfBounds() const {
    // Defines how many pixels offscreen the blob must be before it changes directions
    float offscreenMargin = 5.0f;
    if(fmax(x - LED_WIDTH, -x) > offscreenMargin) {
        return true;
    }
    if(fmax(y - LED_HEIGHT, -y) > offscreenMargin) {
        return true;
    }
    return false;
}

LavaApp::LavaApp(matrix_t *inMatrix) : MatrixApp(inMatrix, "lava"),
    m_FlowRate("flowrate", 1.0f),
    m_Size("size", 1.5f),
    m_Jitter("jitter", 0.1f),
    m_NumberBlobs("number", 6),
    m_BlobColor("color", 255, 100, 200, 100),
    canvas(AACanvas::X2) {

    registerProperty(&m_FlowRate);
    registerProperty(&m_Size);
    registerProperty(&m_Jitter);
    registerProperty(&m_NumberBlobs);
    registerProperty(&m_BlobColor);

    m_FrameRate = 60; //Override default framerate of 10fps
}

void LavaApp::initApp() {
    // Populate blobs
    m_blobs.clear();
    for(int i = 0; i < m_NumberBlobs; i++) {
        m_blobs.emplace_back(m_FlowRate, m_Jitter, m_Size);
    }
}

void LavaApp::drawFrame(float dt) {
    // Update
    for(Blob &blob : m_blobs) {
        blob.updateBlob(dt);
    }

    // Draw
    float edgeBrightness = 0.0f;
    pixel_t brightColor = pixel_t(m_BlobColor.getR(),
                                  m_BlobColor.getG(),
                                  m_BlobColor.getB(),
                                  m_BlobColor.getW());
    pixel_t darkColor = lerpColor(pixel_t(0), brightColor, edgeBrightness);

    for (int i = 0; i < canvas.getWidth(); i++) {
        for (int j = 0; j < canvas.getHeight(); j++) {
            float pixelValue = getPixelValue(i, j);
            pixel_t new_color = darkColor;
            if(pixelValue > 0.2f) {
                // The pixel should be on and shaded
                float brightness = atan((pixelValue - 0.2f) * 10.0f) / (float)(M_PI/2.0f);
                new_color = lerpColor(darkColor, brightColor, brightness);
            }
            canvas.setPixel(i, j, new_color);
        }
    }

    // Subsample image and render
    canvas.renderToMatrix(m_Matrix);
}

float LavaApp::getPixelValue(float x, float y) {
    x /= AACanvas::X2;
    y /= AACanvas::X2;
    float sum = 0.0f;
    for(Blob blob : m_blobs) {
        sum += blob.valueFunction(x, y);
    }
    return sum;
}