#include <cstdint>
#include <stdio.h>
#include <array>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include "cameraclass.hpp"
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

void projectRays(std::vector<std::vector<Vector3f>>& vectorArray, PixelMatrix& window, Cameraf& camera)
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
            //adjust x to aspect ratio by multiplying it to width/hight
            Vector3f vec(calcRayX(x, width) * ((float)width/hight), calcRayY(y, hight), -1.0);
            vec = vec * camera.getRotationMatrix();
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
    }
}

void repositionRays(std::vector<std::vector<Vector3f>>& vectorArray, Cameraf& camera)
{
    for(auto &elem : vectorArray){
        for(auto &vec : elem){
            vec *= camera.getRotationMatrix();
            vec.normalize();
        }
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
    Cameraf debugCamera(origin, Matrix3f ());

    //tasks 1 and 2
    debugCamera.truck({0,0,4});
    //debugCamera.pan(15.0);
    debugCamera.tilt(-30);
    projectRays(vectorArray, window, debugCamera);
    renderTriangles(vectorArray, window, debugCamera.getPosition(),  { { {{-1.75, -1.75, -3}, {1.75, -1.75, -3}, {0, 1.75, -3}}, 0xff00ff } } );
    window.fillPpmFile("./task1&2.ppm");

    //task 3
    //Hollow pyramid, the green triangle should not be seen
    int i = 0;
    debugCamera = Cameraf(origin, Matrix3f ());
    projectRays(vectorArray, window, debugCamera);
    triangleArray = {
        { { {-2, -1, -3 }, {2, -1, -2.75}, {0, 2, -3.75} }, 0xff0000 },
        { { {2, -1, -2.75 }, {2.75, -0.25, -4.5}, {0, 2, -3.75} }, 0x5500ff },
        { { {-2.75, -0.25, -4.75 }, {2.75, -0.25, -4.5}, {0, 2, -3.75} }, 0x00ff00 },
        { { {-2.75, -0.25, -4.75 }, {-2, -1, -3 }, {0, 2, -3.75} }, 0x777777 },
    };
    debugCamera.truck({0,0,2});
    do{
        repositionRays(vectorArray, debugCamera);
        Vector3f position = debugCamera.getPosition();
        //sorting, so that the most distanced triangles will be rendered first
        std::sort(triangleArray.begin(), triangleArray.end(), [position](const TriangleAndColor& A, const TriangleAndColor& B){
                return ( A.triangle.calculateDistanceFromVertexOriginToPlane(position) < B.triangle.calculateDistanceFromVertexOriginToPlane(position) );
                });
        window.fillPixelMatrix(0xffffff);
        renderTriangles(vectorArray, window, position, triangleArray);
        std::string filename = "./complexShape"+std::to_string(i)+".ppm";
        window.fillPpmFile(filename);

        debugCamera.tilt(4);
        debugCamera.truck({0,-1,0});
        ++i;
    }while(i<10);
    return 0;
}
