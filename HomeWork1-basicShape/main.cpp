#include <cstdint>
#include <stdio.h>
#include <array>
#include <fstream>
#include <iostream>

const uint32_t pixelMatrixHight_g = 400;
const uint32_t pixelMatrixWidth_g = 600;

std::array<std::array<uint32_t, pixelMatrixWidth_g>, pixelMatrixHight_g> pixelMatrixArray_g;

bool fillPpmFile(std::string file_path)
{
	std::ofstream ppm_file;
	ppm_file.open(file_path);
	if(!ppm_file.is_open()) return 1;
	ppm_file<<"P3\n";
	ppm_file<<pixelMatrixWidth_g<<" "<<pixelMatrixHight_g<<'\n';
	ppm_file<<0xFF<<'\n';
	for(auto& row : pixelMatrixArray_g){
		for(auto& pixel : row){
			ppm_file<<((pixel>>8*2)&0xFF)<<' '
				<<((pixel>>8*1)&0xFF)<<' '
				<<((pixel>>8*0)&0xFF)<<' ';
		}
		ppm_file << '\n';
	}
	ppm_file.close();
	return 0;
}

void fillRectangle(uint32_t rx1, uint32_t ry1, uint32_t rw, uint32_t rh, uint32_t color)
{
	uint32_t rx2 = rx1+rw;
	uint32_t ry2 = ry1+rh;
	if( (ry2> pixelMatrixHight_g) || (rx2 > pixelMatrixWidth_g) ) return;
	for(uint32_t y = ry1; y < ry2; ++y){
		for(uint32_t x = rx1; x < rx2; ++x){
			pixelMatrixArray_g[y][x] = color;			
		}
	}
}

void checkers()
{
	uint32_t rectangle_width = pixelMatrixWidth_g/5;
	uint32_t rectangle_hight = pixelMatrixHight_g/5;
	uint32_t color = 0xff0000;

	for (uint32_t y = 0; y < pixelMatrixHight_g; y+=rectangle_hight){
		for(uint32_t x = 0; x < pixelMatrixWidth_g; x+=rectangle_width){
			fillRectangle(x, y, rectangle_width, rectangle_hight, color);
			color = rand() % 0x1000000;
		}
	}
}
void fillPixelMatrix(uint32_t color)
{
	for(auto& row : pixelMatrixArray_g){
		for(auto& pixel : row){
			pixel = color;
		}
	}
}

void fillCircle(uint32_t cx, uint32_t cy, uint32_t cr, uint32_t color)
{
	uint32_t x1 = (cr < cx) ? cx - cr : 0;
	uint32_t x2 = cx + cr;
	uint32_t y1 = (cr < cy) ? cy - cr : 0;
	uint32_t y2 = cy + cr; 
	uint32_t dx, dy;
	for(uint32_t xi = x1; xi <= x2; ++xi){
		if (xi >= pixelMatrixWidth_g) break;
		dx = abs(cx-xi);
		for(uint32_t yi = y1; yi <= y2; ++yi){
			if (yi >= pixelMatrixHight_g) break;
			dy = abs(cy-yi);
			if( dx*dx + dy*dy <= cr*cr){
				pixelMatrixArray_g[yi][xi] = color;
			}
		}
	}
}

int main()
{
	checkers();
	fillPpmFile("./checkers.ppm");
	fillPixelMatrix(0xffffff);
	fillCircle(pixelMatrixWidth_g/2, pixelMatrixHight_g/2, pixelMatrixHight_g/8, 0xff0000);
	fillPpmFile("./circle.ppm");
	return 0;
}
