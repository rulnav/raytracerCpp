#include <cstdint>
#include <stdio.h>
#include <array>
#include <fstream>
#include <iostream>
#include "vectorclass.hpp"
#include "pixelarray.hpp"

#define VECTOR_ARRAY_TYPE std::vector<std::vector<VectorF>>

const uint32_t pixelMatrixHight_g = 400;
const uint32_t pixelMatrixWidth_g = 600;

void normalizeRays(std::vector<std::vector<VectorF>>& vectorArray, PixelMatrix& window)
{
    uint32_t width = window.getWidth();
    uint32_t hight = window.getHight();
    float multiplier = 255.0;

    auto normalizeX = [](uint32_t x, uint32_t width) {
        return ( 2.0 * ((x+0.5) / width) - 1.0 );
    };

    auto normalizeY = [](uint32_t y, uint32_t hight) {
        return ( 1.0 - ((y+0.5) / hight) * 2.0 );
    };

    for(uint32_t x = 0; x < width; ++x){
        for(uint32_t y = 0; y < hight; ++y){

            VectorF vec(normalizeX(x, width), normalizeY(y, hight), -1.0);
            window.setPixel(x,y,Pixel(std::abs(vec.getX() * multiplier),
                                      std::abs(vec.getY() * multiplier),
                                      0x77));
            vectorArray[x][y] = vec;
        }
    }
}

int main()
{
    std::vector<std::vector<VectorF>> vectorArray
            (pixelMatrixWidth_g, std::vector<VectorF>(pixelMatrixHight_g));
	PixelMatrix window(pixelMatrixWidth_g, pixelMatrixHight_g);
    window.fillPixelMatrix(0xff0000);
    normalizeRays(vectorArray, window);
    return window.fillPpmFile("./vectornormalization.ppm");
}
