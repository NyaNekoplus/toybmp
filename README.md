# toybmp
A simple C funtion for saving RGB/RGBA image as uncompressed BMP.
# Features
+ RGB or RGBA format. (RGBA format can't be displayed correctly in BMP)
- Single function
+ No dependency
# Usage
Basically, you fopen() a binary file for writing, then call this function with the image data. The pixels are packed linearly from bottom to top, left to right.

For 24-bit RGB, parameter alpha should be set to 0, the R, G, B components are stored as `img[(w*y+x)*3]`, `img[(w*y+x)*3+1]`, `img[(w*y+x)*3+2]`, respectively.

For 32-bit RGBA, parameter alpha should be set to 0, the R, G, B, A components are stored as `img[(w*y+x)*4]`, `img[(w*y+x)*4+1]`, `img[(w*y+x)*4+2]`, respectively.
#Example
[test.c](https://github.com/NyaNekoplus/toybmp/blob/master/test.c) saves a RGB aand a RGBA BMP.
#Output
