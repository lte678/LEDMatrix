//
// Created by leon on 15.07.18.
//

#ifndef MATRIXIFACE_IMAGELOADER_H
#define MATRIXIFACE_IMAGELOADER_H

#include <cinttypes>
#include <iostream>

struct Image {
    uint8_t* raw;
    uint32_t width;
    uint32_t height;

    uint32_t getPixel(uint32_t x, uint32_t y) { return raw[y * width + x]; }
};

Image loadImage(char const *filename) {
    Image image;
    FILE* imageFile  = fopen(filename, "rb");
    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, imageFile);

    int width = *(int*)&header[18];
    int height = *(int*)&header[22];

    std::cout << "Image size: " << width << "x" << height << std::endl;

    return image;
}


#endif //MATRIXIFACE_IMAGELOADER_H
