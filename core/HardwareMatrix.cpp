//
// Created by leon on 07.05.19.
//

#include "HardwareMatrix.h"
    
static int matrixToStrip(int x, int y) {
    x = LED_WIDTH - (x + 1);
    int index = LED_HEIGHT * x;
    if(x % 2 == 0) {
        index += y;
    } else {
        index += (LED_HEIGHT - 1) - y;
    }
    return index;
}
    
bool HardwareMatrix::init() {
    m_Matrix.freq = WS2811_TARGET_FREQ;
    m_Matrix.dmanum = 10;
    
    ws2811_channel_t mainChannel = {};
    mainChannel.gpionum = m_GpioPin;
    mainChannel.count = LED_COUNT;
    mainChannel.invert = 0;
    mainChannel.brightness = 255;
    mainChannel.strip_type = SK6812_STRIP_RGBW;
    
    ws2811_channel_t unused = {};
    unused.gpionum = 0;
    unused.count = 0;
    unused.invert = 0;
    unused.brightness = 0;
    
    m_Matrix.channel[0] = mainChannel;
    m_Matrix.channel[1] = unused;
    
    ws2811_return_t returnVal = ws2811_init(&m_Matrix);
    if(returnVal != WS2811_SUCCESS) {
        perror("Failed to initialize LED matrix");
        return false;
    }
    return true;
}

void HardwareMatrix::shutdown() {
    ws2811_fini(&m_Matrix);
}

void HardwareMatrix::render(const matrix_t &matrixData) {
    for (int i = 0; i < LED_WIDTH; i++) {
        for (int j = 0; j < LED_HEIGHT; j++) {
            m_Matrix.channel[0].leds[matrixToStrip(i, j)] = matrixData[i][j].data;
        }
    }
    
    ws2811_return_t returnVal = ws2811_render(&m_Matrix);
    if(returnVal != WS2811_SUCCESS) {
        perror("Failed to render image");
    }
}

void HardwareMatrix::setBrightness(uint8_t brightness) {
    m_Matrix.channel[0].brightness = brightness;
}