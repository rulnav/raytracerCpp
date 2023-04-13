#include <cstdint>
#include <stdio.h>
#include <array>
#include <fstream>
#include <iostream>
#include "vectorclass.hpp"
#include "pixelarray.hpp"
#include "triangleclass.hpp"

const uint32_t pixelMatrixHight_g = 400;
const uint32_t pixelMatrixWidth_g = 600;

void projectRays(std::vector<std::vector<Vector3f>>& vectorArray, PixelMatrix& window)
{
    uint32_t width = window.getWidth();
    uint32_t hight = window.getHight();
    auto calcRayX= [](uint32_t x, uint32_t width) {
        return ( 2.0 * ((x+0.5) / width) - 1.0 );
    };
    auto calcRayY= [](uint32_t y, uint32_t hight) {
        return ( 1.0 - ((y+0.5) / hight) * 2.0 );
    };
    for(uint32_t x = 0; x < width; ++x){
        for(uint32_t y = 0; y < hight; ++y){

            Vector3f vec(calcRayX(x, width), calcRayY(y, hight), -1.0);
            vectorArray[y][x] = vec.normalize();
        }
    }
}

void renderTriangles(std::vector<std::vector<Vector3f>>& vectorArray, PixelMatrix& window, const Vector3f& origin, const std::vector<Triangle3f>& triangles, Pixel color = 0xff00ff){
    uint32_t width = window.getWidth();
    uint32_t hight = window.getHight();
    for(uint32_t i = 0; i < hight; ++i){
        for(uint32_t j = 0; j < width; ++j){
            //check if the point, at which the ray intersects the triangle's plane is within the triangle
            for(auto& triangle : triangles){
                if(triangle.rayIntersectsTriangle(origin, vectorArray[i][j])) {
                    window.setPixel(j, i, color);
                }
            }
        }
        printf("\n");
    }
}

int main()
{
    std::vector<std::vector<Vector3f>> vectorArray
            (pixelMatrixHight_g, std::vector<Vector3f>(pixelMatrixWidth_g));
	PixelMatrix window(pixelMatrixWidth_g, pixelMatrixHight_g);
    Vector3f origin (0.0,0.0,0.0);
    std::vector<Triangle3f> triangleArray;
    window.fillPixelMatrix(0x00ff00);
    projectRays(vectorArray, window);

    renderTriangles(vectorArray, window, origin, { {{-1.75, -1.75, -3}, {1.75, -1.75, -3}, {0, 1.75, -3}} });
    window.fillPpmFile("./triangle1.ppm");

    window.fillPixelMatrix(0x00ff00);
    renderTriangles(vectorArray, window, origin, { {{-2.25, 0, -4}, {2.25, -2.25, -3}, {0, 2.25, -3}} });
    window.fillPpmFile("./triangle2.ppm");

    triangleArray = {
        { {-1, -2, -3 }, {-2, -1, -3}, {-3, -3, -3} },
        { {1, 2, -3}, {2, 1, -3}, {3, 3, -3} },
    };
    window.fillPixelMatrix(0x00ff00);
    renderTriangles(vectorArray, window, origin, triangleArray);
    window.fillPpmFile("./twoTriangles.ppm");
    return 0;
}
