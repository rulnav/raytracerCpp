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
//#include "triangleclass.hpp"
#include "rendererclass.hpp"
#include "triangledata.hpp"

const uint32_t pixelMatrixHight_g = 400;
const uint32_t pixelMatrixWidth_g = 600;

//func to calculate rotation parameters, input distance r, that you want to keep, and angle that you want to spin. 
//output the distance you need to move
//Note: you get and insert absolute units
float calcMovement(const float& r, const float& angleRad){
    return (r*sin(angleRad/2)*2);
}

int main()
{
    RendererF pixelMatrix (pixelMatrixWidth_g, pixelMatrixHight_g);
    Vector3f origin (0.0,0.0,0.0);
    std::vector<TriangleAndColorF> triangleArray;
    pixelMatrix.window.fillPixelMatrix(0x00ff00);
    Cameraf debugCamera(origin, Matrix3f (), pixelMatrixWidth_g, pixelMatrixHight_g);

    //tasks 1 and 2
    debugCamera.truck({0,0,4});
    //debugCamera.pan(15.0);
    debugCamera.tilt(-30);
    pixelMatrix.render(debugCamera, { { {{-1.75, -1.75, -3}, {1.75, -1.75, -3}, {0, 1.75, -3}}, 0xff00ff } } );
    pixelMatrix.window.fillPpmFile("./task1&2.ppm");

    //task 3
    //Hollow, doublesided pyramid, moving the camera so it seems the pyramid is revolving around the x axis
    int i = 0;
    debugCamera = Cameraf(origin, Matrix3f (), pixelMatrixWidth_g, pixelMatrixHight_g);
    triangleArray = {
        { { {-2, -1, -3 }, {2, -1, -2.75}, {0, 2, -3.75} }, 0xff0000 },
        { { {2, -1, -2.75}, {-2, -1, -3 }, {0, 2, -3.75} }, 0xff0000 },
        { { {2, -1, -2.75 }, {2.75, -0.25, -4.5}, {0, 2, -3.75} }, 0x5500ff },
        { { {2.75, -0.25, -4.5}, {2, -1, -2.75 }, {0, 2, -3.75} }, 0x5500ff },
        { { {-2.75, -0.25, -4.75 }, {2.75, -0.25, -4.5}, {0, 2, -3.75} }, 0x00ff00 },
        { { {2.75, -0.25, -4.5}, {-2.75, -0.25, -4.75 }, {0, 2, -3.75} }, 0x00ff00 },
        { { {-2.75, -0.25, -4.75 }, {-2, -1, -3 }, {0, 2, -3.75} }, 0x777777 },
        { { {-2, -1, -3 }, {-2.75, -0.25, -4.75 }, {0, 2, -3.75} }, 0x777777 },
    };
//    projectRays(vectorArray, window, debugCamera);
    pixelMatrix.render(debugCamera, triangleArray);
    debugCamera.truck({0,0,2});
    float degrees = 20;
    float rads = degrees * (M_PI / 180.0);
    float movement = calcMovement(5.75, rads);
    do{
        Vector3f position = debugCamera.getPosition();
        if(i==18){
            debugCamera = Cameraf(position, Matrix3f (), pixelMatrixWidth_g, pixelMatrixHight_g);
        }
//        projectRays(vectorArray, window, debugCamera);
        //sorting, so that the most distanced triangles will be rendered first
        std::sort(triangleArray.begin(), triangleArray.end(), [position](const TriangleAndColorF& A, const TriangleAndColorF& B){
                return ( A.triangle.calculateDistanceFromVertexOriginToPlane(position) < B.triangle.calculateDistanceFromVertexOriginToPlane(position) );
                });
        pixelMatrix.window.fillPixelMatrix(0xffffff);
//        renderTriangles(vectorArray, window, position, triangleArray);
        pixelMatrix.render(debugCamera, triangleArray);
        std::string filename = "./complexShape"+std::to_string(i)+".ppm";
        pixelMatrix.window.fillPpmFile(filename);
        {
            debugCamera.tilt(degrees/2);
            debugCamera.truck({0,-movement,0});
            debugCamera.tilt(degrees/2);
        }
        ++i;
    }while(i<=360/degrees);
    return 0;
}
