#include "CImg.h"
#include <iostream>
using namespace cimg_library;
int main()
{
    unsigned char purple[] = { 255,0,255 };
    CImg<unsigned char> image("girl.bmp"), visu(500, 400, 1, 3, 0);
    const unsigned char red[] = { 255,0,0 }, green[] = { 0,255,0 }, blue[] = { 0,0,255 };


    return 0;
}