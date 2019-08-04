#include <stdio.h>
#include "toybmp.h"
#pragma warning(disable:4996)

unsigned char rgb[256 * 256 * 3];
unsigned char rgba[256 * 256 * 4];
int main(void) {
	unsigned char* p = rgb;
	unsigned char* pa = rgba;
	for (int y = 0; y < 256; ++y) {
		for (int x = 0; x < 256; ++x) {
			*p++ = (unsigned char)x;
			*p++ = (unsigned char)y;
			*p++ = (unsigned char)128;
		}
	}
	for (int y = 0; y < 256; ++y) {
		for (int x = 0; x < 256; ++x) {
			*pa++ = (unsigned char)x;
			*pa++ = (unsigned char)y;
			*pa++ = (unsigned char)128;
			*pa++ = (unsigned char)((x + y) / 2);	// A
		}
	}
	toybmp(fopen("rgb.bmp", "wb"), 256, 256, p, 0);
	toybmp(fopen("rgba.bmp", "wb"), 256, 256, pa, 1);
}