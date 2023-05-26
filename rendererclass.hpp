#ifndef RENDERERCLASS_H
#define RENDERERCLASS_H

#include "cameraclass.hpp"
#include "vectorclass.hpp"
#include "pixelarray.hpp"
#include "triangledata.hpp"

template<typename T>
class Renderer{
public:
    PixelMatrix window;
    Renderer (const uint32_t& width, const uint32_t& hight)
        : window(width, hight),
          pixelMatrixWidth(width), pixelMatrixHight(hight),
          vectorArray(hight, std::vector<Vector3<T>>(width))
          {}

    void render(const Camera<T>& camera, const std::vector<TriangleAndColor<T>>& trianglesAndColors){
        projectRays(camera);
        renderTriangles(camera, trianglesAndColors);
    }
private:
    uint32_t pixelMatrixWidth;
    uint32_t pixelMatrixHight;
    std::vector<std::vector<Vector3<T>>> vectorArray;
    //project rays through pixels
    void projectRays(const Camera<T>& camera)
    {
        auto calcRayX= [](uint32_t x, uint32_t width) {
            return ( 2.0 * ((x+0.5) / width) - 1.0 );
        };
        auto calcRayY= [](uint32_t y, uint32_t hight) {
            return ( 1.0 - ((y+0.5) / hight) * 2.0 );
        };
        for(uint32_t x = 0; x < pixelMatrixWidth; ++x){
            for(uint32_t y = 0; y < pixelMatrixHight; ++y){
                //adjust x to aspect ratio by multiplying it to pixelMatrixWidth/pixelMatrixHight
                Vector3f vec(calcRayX(x, pixelMatrixWidth) * ((float)pixelMatrixWidth/pixelMatrixHight), calcRayY(y, pixelMatrixHight), -1.0);
                vec = vec * camera.getRotationMatrix();
                vectorArray[y][x] = vec.normalize();
            }
        }
    }
    //render triangles in window
    void renderTriangles(const Camera<T>& camera, const std::vector<TriangleAndColor<T>>& trianglesAndColors) {
        for(uint32_t i = 0; i < pixelMatrixHight; ++i){
            for(uint32_t j = 0; j < pixelMatrixWidth; ++j){
                //check if the point, at which the ray intersects the triangle's plane is within the triangle
                for(auto& triangleAndColor : trianglesAndColors){
                    if(triangleAndColor.triangle.rayIntersectsTriangle(camera.getPosition(), vectorArray[i][j])) {
                        window.setPixel(j, i, triangleAndColor.color);
                    }
                }
            }
        }
    }
};

using RendererF = Renderer<float>;
#endif // RENDERERCLASS_H
