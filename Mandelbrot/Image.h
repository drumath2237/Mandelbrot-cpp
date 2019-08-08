#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct RGB
{
public:
	int r, g, b;
};

class Image {
public:
	int width, height;
	vector<RGB> datas;

	Image() :width(800), height(800) {
		datas = vector<RGB>(800 * 800, { 0,0,0 });
	}

	Image(int w, int h) :width(w), height(h) {
		datas = vector<RGB>(w * h, { 0,0,0 });
	}

	RGB getPixel(int x, int y) {
		return datas[width * y + x];
	}

	void setPixel(int x, int y, RGB color) {
		datas[width * y + x] = color;
	}

	void ppm_out(string filename) {
		ofstream file(filename);

		file << "P3" << endl;
		file << width << " " << height << endl;
		file << 255 << endl;

		for (int j = 0; j < height; j++)for (int i = 0; i < width; i++) {
			RGB color = getPixel(i, j);
			file << color.r << " "
				<< color.g << " "
				<< color.b << endl;
		}

		file.close();
	}
};
