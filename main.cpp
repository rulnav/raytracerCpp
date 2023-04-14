#include <cstdint>
#include <stdio.h>
#include <array>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "vectorclass.hpp"
#include "pixelarray.hpp"
#include "triangleclass.hpp"

const uint32_t pixelMatrixHight_g = 400;
const uint32_t pixelMatrixWidth_g = 600;

struct TriangleAndColor {
    Triangle3f triangle;
    Pixel color;
    TriangleAndColor(const Triangle3f& tri, const Pixel&  pix) : triangle(tri), color(pix){};
};

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

void renderTriangles(std::vector<std::vector<Vector3f>>& vectorArray, PixelMatrix& window, const Vector3f& origin, const std::vector<TriangleAndColor>& trianglesAndColors) {
    uint32_t width = window.getWidth();
    uint32_t hight = window.getHight();
    for(uint32_t i = 0; i < hight; ++i){
        for(uint32_t j = 0; j < width; ++j){
            //check if the point, at which the ray intersects the triangle's plane is within the triangle
            for(auto& triangleAndColor : trianglesAndColors){
                if(triangleAndColor.triangle.rayIntersectsTriangle(origin, vectorArray[i][j])) {
                    window.setPixel(j, i, triangleAndColor.color);
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
    std::vector<TriangleAndColor> triangleArray;
    window.fillPixelMatrix(0x00ff00);
    projectRays(vectorArray, window);

    renderTriangles(vectorArray, window, origin,  { { {{-1.75, -1.75, -3}, {1.75, -1.75, -3}, {0, 1.75, -3}}, 0xff00ff } } );
    window.fillPpmFile("./triangle1.ppm");

    window.fillPixelMatrix(0x00ff00);
    renderTriangles(vectorArray, window, origin, { { {{-2.25, 0, -3}, {2.25, -2.25, -3}, {0, 2.25, -3}}, 0xff00ff } });
    window.fillPpmFile("./triangle2.ppm");

    triangleArray = {
        { { {1, -2, -3 }, {-2, 1, -3}, {-3, -3, -3} }, 0xff00ff },
        { { {-1, 2, -3}, {2, -1, -3}, {3, 3, -4} }, 0x0044ff },
    };
    window.fillPixelMatrix(0x00ff00);
    renderTriangles(vectorArray, window, origin, triangleArray);
    window.fillPpmFile("./twoTriangles.ppm");

    //Hollow pyramid, the green triangle should not be seen
    triangleArray = {
        { { {-2, -1, -3 }, {2, -1, -2.75}, {0, 2, -3.75} }, 0xff0000 },
        { { {2, -1, -2.75 }, {2.75, -0.25, -4.5}, {0, 2, -3.75} }, 0x990000 },
        { { {-2.75, -0.25, -4.75 }, {2.75, -0.25, -4.5}, {0, 2, -3.75} }, 0x00ff00 },
        { { {-2.75, -0.25, -4.75 }, {-2, -1, -3 }, {0, 2, -3.75} }, 0xff0077 },
    };
    //sorting, so that the most distanced triangles will be rendered first
    std::sort(triangleArray.begin(), triangleArray.end(), [](const TriangleAndColor& A, const TriangleAndColor& B){
        return ( A.triangle.getDistanceFromVertexOriginToPlane() < B.triangle.getDistanceFromVertexOriginToPlane() );
    });
    window.fillPixelMatrix(0xffffff);
    renderTriangles(vectorArray, window, origin, triangleArray);
    window.fillPpmFile("./complexShape.ppm");
    return 0;
}
