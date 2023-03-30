#ifndef PIXELARRAY_HPP
#define PIXELARRAY_HPP

#include <iostream>
#include <cstdint>
#include <fstream>
#include <vector>

namespace MyUtils {
template<typename T>
T diff(const T&a, const T&b) {
    return (a > b) ? (a - b) : (b - a);
}
}

class Pixel {
public:
    uint8_t red, green, blue;

    Pixel() : red{0}, green {0}, blue{0} {}
    Pixel(const uint8_t inRed, const uint8_t inGreen, const uint8_t inBlue) :
        red{inRed}, green{inGreen}, blue{inBlue} {}
    Pixel(const uint32_t inColor) {
        red =   (inColor>>8*2)&0xFF;
        green = (inColor>>8*1)&0xFF;
        blue =  (inColor>>8*0)&0xFF;
    }

    friend std::ostream& operator<<(std::ostream& os, const Pixel& c) {
        os << static_cast<int>(c.red) << ' '
           << static_cast<int>(c.green) << ' '
           << static_cast<int>(c.blue);
        return os;
    }
};

class PixelMatrix {
public:
    PixelMatrix(const uint32_t cols, const uint32_t rows)
        : pixelMatrixArray(rows, std::vector<Pixel>(cols)) {}

    uint32_t getHight() const { return pixelMatrixArray.size(); }
    uint32_t getWidth() const { return pixelMatrixArray.empty() ? 0 : pixelMatrixArray[0].size(); }

    Pixel getPixel(const uint32_t col, const uint32_t row) const {
        return pixelMatrixArray[row][col];
    }

    void setPixel(const uint32_t col, const uint32_t row, const Pixel &color) {
        pixelMatrixArray[row][col] = color;
    }

    bool fillPpmFile(std::string file_path) const {
        std::ofstream ppm_file;
        ppm_file.open(file_path);
        if(!ppm_file.is_open()) return false;
        ppm_file<<"P3\n";
        ppm_file<<getWidth()<<" "<<getHight()<<'\n';
        ppm_file<<0xFF<<'\n';
        for(auto& row : pixelMatrixArray){
            for(auto& pixel : row ){
                ppm_file<<pixel<<' ';
            }
            ppm_file << '\n';
        }
        ppm_file.close();
        return true;
    }

    void fillPixelMatrix(const Pixel &color){
        for(auto& row : pixelMatrixArray){
            for(auto& pixel : row){
                pixel = color;
            }
        }
    }

private:
    std::vector<std::vector<Pixel>> pixelMatrixArray;
};

#endif
