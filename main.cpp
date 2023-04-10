#include <cstdint>
#include <stdio.h>
#include <array>
#include <fstream>
#include <iostream>
#include "vectorclass.hpp"
#include "pixelarray.hpp"
#include "triangleclass.hpp"

const uint32_t pixelMatrixHight_g = 4;
const uint32_t pixelMatrixWidth_g = 6;

void projectRays(std::vector<std::vector<Vector3f>>& vectorArray, PixelMatrix& window)
{
    uint32_t width = window.getWidth();
    uint32_t hight = window.getHight();
    float multiplier = 255.0;

    auto centerX= [](uint32_t x, uint32_t width) {
        return ( 2.0 * ((x+0.5) / width) - 1.0 );
    };

    auto centerY= [](uint32_t y, uint32_t hight) {
        return ( 1.0 - ((y+0.5) / hight) * 2.0 );
    };

    for(uint32_t x = 0; x < width; ++x){
        for(uint32_t y = 0; y < hight; ++y){

            Vector3f vec(centerX(x, width), centerY(y, hight), -1.0);
            window.setPixel(x,y,Pixel(std::abs(vec.x * multiplier),
                                      std::abs(vec.y * multiplier),
                                      0x77));
            vectorArray[y][x] = normal(vec);
        }
    }
}

void renderTriangle(std::vector<std::vector<Vector3f>>& vectorArray, PixelMatrix& window, const Triangle3f& triangle){
    uint32_t width = window.getWidth();
    uint32_t hight = window.getHight();

    for(uint32_t i = 0; i < hight; ++i){
        for(uint32_t j = 0; j < width; ++j){
            Vector3f newVec = triangle.rayFromOriginToPointInPlane(Vector3f(0.0,0.0,0.0),
                                                                   vectorArray[i][j]);
            printf("{%f, %f, %f} ", newVec.x, newVec.y, newVec.z);
        }
        printf("\n");
    }
}

int main()
{
    std::vector<std::vector<Vector3f>> vectorArray
            (pixelMatrixHight_g, std::vector<Vector3f>(pixelMatrixWidth_g));
	PixelMatrix window(pixelMatrixWidth_g, pixelMatrixHight_g);
    window.fillPixelMatrix(0xff0000);
    projectRays(vectorArray, window);
    window.fillPpmFile("./vectornormalization.ppm");

    renderTriangle(vectorArray, window, {{-1.75, -1.75, -3}, {1.75, -1.75, -3}, {0, 1.75, -3}});

    return 0;
}
