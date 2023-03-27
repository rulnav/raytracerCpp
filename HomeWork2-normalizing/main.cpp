#include <cstdint>
#include <stdio.h>
#include <array>
#include <fstream>
#include <iostream>
#include "vectorclass.hpp"
#include "pixelarray.hpp"

const uint32_t pixelMatrixHight_g = 400;
const uint32_t pixelMatrixWidth_g = 600;

void normalizeRays()
{

}

int main()
{
	PixelMatrix window(pixelMatrixWidth_g, pixelMatrixHight_g);
    window.fillPixelMatrix(0xff0000);
    return window.fillPpmFile("./vectornormalization.ppm");
}
