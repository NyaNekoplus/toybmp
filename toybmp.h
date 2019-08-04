/*
MIT License

Copyright (c) 2019 Edward Tsai

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef TOYBMP_H_
#define TOYBMP_H_

/*!
	\def TOYBMP_LINKAGE
	By default this macro is empty.
	User may define this macro as static for static linkage,
	and/or inline in C99/C++, etc.
*/

#ifndef TOYBMP_LINKAGE
#define TOYBMP_LINKAGE //Empty by default, change for static or inline
#endif

#include <stdio.h>
#ifndef TOYBMP_OUTPUT
#define TOYBMP_OUTPUT FILE* fp
#endif

#ifndef TOYBMP_PUT
#define TOYBMP_PUT(u) fputc(u,fp)
#endif

/*!
	\brief Save a RGB/RGBA image in BMP format.
	\param TOYBMP_OUTPUT Output stream (by default using file descriptor).
	\param w Width of the image.
	\param h Height of the image.
	\param img Image pixel data in 24-bit RGB or 32-bit RGBA format.
	\param alpha Whether the image contains alpha channel.
*/
TOYBMP_LINKAGE void toybmp(TOYBMP_OUTPUT, unsigned w, unsigned h, const unsigned char* img, int alpha) {
	unsigned b = ((w * (alpha ? 32 : 24) + 7) >> 3);
	unsigned ROWsize = (b + 3) & (~3);
	unsigned ImageDataSize = ROWsize * h + 54;
	unsigned p = ROWsize - b, i, x, y;	/* pad */
#define TOYBMP_FILE_HEAD(u,l) for(i = 0; i < l; ++i)TOYBMP_PUT((u)[i])
#define TOYBMP_PAD_ZERO(u) for(i=0;i<u;++i)TOYBMP_PUT(0)
#define TOYBMP_U32B(u) do{TOYBMP_PUT((u)&255);TOYBMP_PUT(((u)>>8)&255);TOYBMP_PUT(((u)>>16)&255);TOYBMP_PUT((u)>>24);}while(0)
#define TOYBMP_BGR(u) do{TOYBMP_PUT(*(img + x + 2));TOYBMP_PUT(*(img + 1 + x));TOYBMP_PUT(*(img + x));}while(0)
#define TOYBMP_C24B(u,ua) do{for(y=0;y<h;++y){img -= u;for(x = 0; x < u; x+=3){TOYBMP_BGR(x);}TOYBMP_PAD_ZERO(ua);}}while(0)
#define TOYBMP_C32B(u,ua) do{for(y=0;y<h;++y){img -= u;for(x = 0; x < u; x+=4){TOYBMP_BGR(x);TOYBMP_PUT(*(img + x + 3));}TOYBMP_PAD_ZERO(ua);}}while(0)
	TOYBMP_FILE_HEAD("BM", 2);											/*BitMap File Header*/
	TOYBMP_U32B(ImageDataSize);
	TOYBMP_PAD_ZERO(4);
	TOYBMP_U32B(0x36);													/*bfOffBit*/
																		/*BitMap Info Header*/
	TOYBMP_U32B(0x28);													/*Size of Info Header*/
	TOYBMP_U32B(w); TOYBMP_U32B(h);										/*Width and Height*/
	TOYBMP_PUT(1); TOYBMP_PUT(0);										/*biPlanes*/
	TOYBMP_PUT(alpha?0x20:0x18); TOYBMP_PUT(0);							/*BitCount*/
	TOYBMP_PAD_ZERO(4);
	TOYBMP_U32B(ROWsize*h);
	TOYBMP_PAD_ZERO(16);
	if (alpha) TOYBMP_C32B(b,p);										/*BitMap Data*/
	else TOYBMP_C24B(b,p);
}
#endif TOYBMP_H_ /* TOYBMP_H_ */