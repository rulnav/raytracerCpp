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
    unsigned int multiplier = 255;

    auto normalizeX = [](uint32_t x, uint32_t width) constexpr{
        return ( 2.0 * ((x+0.5) / width) - 1.0 );
    };

    auto normalizeY = [](uint32_t y, uint32_t hight) constexpr{
        return ( 1.0 - ((y+0.5) / hight) * 2.0 );
    };

//    VectorF trialVec(normalizeX(399, width), normalizeY(383, hight), -1.0);
//    std::cout<<trialVec.getY();
    for(uint32_t x = 399; x < width; ++x){
        for(uint32_t y = 382; y < hight; ++y){
            VectorF vec(normalizeX(x, width), normalizeY(y, hight), -1.0);
            std::cout<<'\n'<<"x = "<<x << " calculated value is "<<
                       vec.getX()<<" ; y = " <<y <<" calculated value is "<<
                       vec.getY();
            window.setPixel(x,y,Pixel(vec.getX() * multiplier,
                                      vec.getY() * multiplier,
                                      0x77));
            vectorArray[x][y] = vec;
        }
    }
}

int main()
{
    std::vector<std::vector<VectorF>> vectorArray
            (pixelMatrixHight_g, std::vector<VectorF>(pixelMatrixWidth_g));
	PixelMatrix window(pixelMatrixWidth_g, pixelMatrixHight_g);
//    window.fillPixelMatrix(0xff0000);
    normalizeRays(vectorArray, window);
    return window.fillPpmFile("./vectornormalization.ppm");
}
