// Mandelbrot.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <complex>

#include "Image.h"

using namespace std;

#define MAN_X 2.0
#define MAN_Y 2.0

#define LOOP_COUNT 500

bool calcMandel(complex<double>);

int main()
{
	Image img = Image();

#pragma omp parallel for
	for (int j = 0; j < img.height; j++) for (int i = 0; i < img.width; i++) {
		double x = 4. / (float)img.width * i - 2.;
		double y = 4. / (float)img.height * j - 2.;
		auto c = complex<double>(x, y);
		if (calcMandel(c)) {
			img.setPixel(i, j, { 255,255,255 });
		}
		else {
			img.setPixel(i, j, { 0,0,0 });
		}
	}

	img.ppm_out("result.ppm");
}

bool calcMandel(complex<double> c) {
	auto z = complex<double>(0);
	for (int i = 0; i < LOOP_COUNT; i++) {
		z = z * z + c;
		if (z.imag() * z.imag() + z.real() * z.real() > 4.) {
			return false;
		}
	}
	return true;
}