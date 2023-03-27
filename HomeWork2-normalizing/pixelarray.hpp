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

struct Color {
  uint8_t red, green, blue;  

  Color() : red{0}, green {0}, blue{0} {}
  Color(const uint8_t inRed, const uint8_t inGreen, const uint8_t inBlue) :
    red{inRed}, green{inGreen}, blue{inBlue} {}
  Color(const uint32_t inColor) {
    red =   (inColor>>8*2)&0xFF;
    green = (inColor>>8*1)&0xFF;
    blue =  (inColor>>8*0)&0xFF;
  }
};

class PixelMatrix {
public:
  PixelMatrix(const uint32_t hight, const uint32_t width)
  : pixelMatrixArray(width, std::vector<Color>(hight)) {}

  uint32_t getHight() const { return pixelMatrixArray.size(); }
  uint32_t getWidth() const { return pixelMatrixArray.empty() ? 0 : pixelMatrixArray[0].size(); }

  Color getPixel(const uint32_t x, const uint32_t y) const {
    return pixelMatrixArray[x][y];
  }

  void setPixel(const uint32_t x, const uint32_t y, Color &color) {
    pixelMatrixArray[x][y] = color;
  }

  bool fillPpmFile(std::string file_path) const {
    std::ofstream ppm_file;
    ppm_file.open(file_path);
    if(!ppm_file.is_open()) return false;
    ppm_file<<"P3\n";
    ppm_file<<getWidth()<<" "<<getHight()<<'\n';
    ppm_file<<0xFF<<'\n';
    for(auto& col : pixelMatrixArray){
      for(auto& pixel : col){
        ppm_file<<pixel.red<<' '
                <<pixel.blue<<' '
                <<pixel.green<<' ';
      }
      ppm_file << '\n';
    }
    ppm_file.close();
    return true;
  }

  void fillPixelMatrix(uint32_t color){
    for(auto& col : pixelMatrixArray){
      for(auto& pixel : col){
        pixel = color;
      }
    }
  }

  void fillRectangle(const uint32_t rx1, const uint32_t ry1, const uint32_t rw, const uint32_t rh, Color &color) {
    uint32_t rx2 = rx1+rw;
    uint32_t ry2 = ry1+rh;
    if( (ry2> getHight()) || (rx2 > getWidth()) ) return;
    for(uint32_t y = ry1; y < ry2; ++y){
      for(uint32_t x = rx1; x < rx2; ++x){
        setPixel(x, y, color);
      }
    }
  }

  void fillCircle(const uint32_t cx, const uint32_t cy, const uint32_t cr, Color &color) {
    uint32_t x1 = (cr < cx) ? cx - cr : 0;
    uint32_t x2 = cx + cr;
    uint32_t y1 = (cr < cy) ? cy - cr : 0;
    uint32_t y2 = cy + cr; 
    uint32_t dx, dy;
    for(uint32_t xi = x1; xi <= x2; ++xi){
      if (xi >= getWidth()) break;
      dx = MyUtils::diff(cx, xi);
      for(uint32_t yi = y1; yi <= y2; ++yi){
        if (yi >= getHight()) break;
        dy = MyUtils::diff(cy, yi);
        if( dx*dx + dy*dy <= cr*cr){
          setPixel(xi, yi, color);
        }
      }
    }
  }

private:
  std::vector<std::vector<Color>> pixelMatrixArray;
};

#endif
