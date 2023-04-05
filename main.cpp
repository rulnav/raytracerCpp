#include <cstdint>
#include <stdio.h>
#include <array>
#include <fstream>
#include <iostream>
#include "vectorclass.hpp"
#include "pixelarray.hpp"
#include "triangleclass.hpp"

//#define VECTOR_ARRAY_TYPE std::vector<std::vector<VectorF>>


const uint32_t pixelMatrixHight_g = 400;
const uint32_t pixelMatrixWidth_g = 600;

void normalizeRays(std::vector<std::vector<MyVec::Vector3f>>& vectorArray, PixelMatrix& window)
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

            MyVec::Vector3f vec(normalizeX(x, width), normalizeY(y, hight), -1.0);
            window.setPixel(x,y,Pixel(std::abs(vec.x * multiplier),
                                      std::abs(vec.y * multiplier),
                                      0x77));
            vectorArray[x][y] = vec;
        }
    }
}

void printCrossProduct(MyVec::Vector3f A, MyVec::Vector3f B){
    MyVec::Vector3f newVec = MyVec::crossProduct(A, B);
    printf("Cross product: {%f, %f, %f}\n", newVec.x, newVec.y, newVec.z);
}
void printArea(MyVec::Vector3f A, MyVec::Vector3f B){
    MyVec::Vector3f newVec = 2*MyVec::faceBetween(A, B);
    printf("Parallelogram area: {%f, %f, %f}\n", newVec.x, newVec.y, newVec.z);
}
void printTriangleProperties(Triangle3f triangle){
    MyVec::Vector3f normalVector = triangle.normalVector();
    float area = triangle.area();
    printf("normal Vector of triangle: {%f, %f, %f}\n", normalVector.x, normalVector.y, normalVector.z);
    printf("area of triangle: %f\n", area);
}

int main()
{
    std::vector<std::vector<MyVec::Vector3f>> vectorArray
            (pixelMatrixWidth_g, std::vector<MyVec::Vector3f>(pixelMatrixHight_g));
	PixelMatrix window(pixelMatrixWidth_g, pixelMatrixHight_g);
    window.fillPixelMatrix(0xff0000);
    normalizeRays(vectorArray, window);
    window.fillPpmFile("./vectornormalization.ppm");

    printf("\n====Task2====\n");
    printCrossProduct({3.5, 0, 0}, {1.75, 3.5, 0});
    printCrossProduct({3, -3, 1}, {4, 9, 3});
    printArea({3, -3, 1}, {4, 9, 3});
    printArea({3, -3, 1}, {-12, 12, -4});
    printf("\n====Task3====\n");
    printTriangleProperties({{-1.75, -1.75, -3},{1.75, -1.75, -3},{0,1.75,-3}});
    printTriangleProperties({{0, 0, -1},{1, 0, 1},{-1, 0 ,1}});
    printTriangleProperties({{0.56, 1.11, 1.23},{0.44, -2.368, -0.54},{-1.56, 0.15, -1.92}});
    return 0;
}
