#include "CImg.h"
#include <iostream>
using namespace cimg_library;
int main()
{
    unsigned char purple[] = { 255,0,255 };
    CImg<unsigned char> image("girl.bmp"), visu(500, 400, 1, 3, 0);
    const unsigned char red[] = { 255,0,0 }, green[] = { 0,255,0 }, blue[] = { 0,0,255 };
    //image.blur(2.5);

    CImgDisplay main_disp(image.width() / 5, image.height() / 5, "Click a point"), draw_disp(visu, "Intensity profile");
    main_disp.display(image);
    while (!main_disp.is_closed() && !draw_disp.is_closed()) 
    {
        main_disp.wait();
        if (main_disp.button() && main_disp.mouse_y() >= 0) {
            const int y = main_disp.mouse_y()*image.height() / (double)(main_disp.height());
            const int x = main_disp.mouse_x()*image.width() / (double)(main_disp.width());
            visu.fill(0);
            visu.draw_graph(image.get_crop(0, y, 0, 0, image.width() - 1, y, 0, 0), red, 1, 1, 0, 255, 0);
            visu.draw_graph(image.get_crop(0, y, 0, 1, image.width() - 1, y, 0, 1), green, 1, 1, 0, 255, 0);
            visu.draw_graph(image.get_crop(0, y, 0, 2, image.width() - 1, y, 0, 2), blue, 1, 1, 0, 255, 0);
            visu.display(draw_disp);
            unsigned char my_red = image(x, y);
            unsigned char my_green = image(x, y, 1);
            unsigned char my_blue = image(x, y, 2);
            std::cout << "x:" << x << " y:" << y << " red:" << (int)my_red << " green:" << (int)my_green << " blue:" << (int)my_blue << "\n";
        }
    }
    return 0;
}