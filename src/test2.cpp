#include "CImg.h"
#include <iostream>
#include <vector>
using namespace cimg_library;
void setPixel(const CImg<unsigned char> &img, int x, int y, CImg<unsigned char> &res)
{
    res(x, y) = img(x, y);
    res(x, y) = img(x, y, 0, 1);
    res(x, y) = img(x, y, 2);
}
struct Point
{
    int x = 0;
    int y = 0;
    Point(int x, int y): x(x), y(y){}
};
bool setNeighbors(Point coord, Point size, std::vector<bool> &was, std::vector<Point> &neighbors)
{
    //
    return neighbors.size() > 0;
}
std::vector<Point> search(const CImg<unsigned char> &img, Point coord)
{
    unsigned char red = img(coord.x, coord.y);
    Point size(img.width(), img.height());
    std::vector<Point> neighbors, res;
    std::vector<bool> was;
    while (setNeighbors(coord, size, was, neighbors))
    {
        coord = neighbors.back();
        res.push_back(coord);
        neighbors.pop_back();
    }
    return res;
}

int main()
{
    unsigned char purple[] = { 255,0,255 };
    CImg<unsigned char> image("girl.bmp"), res(image.width(), image.height());
    res.fill(255);
    const int w = image.width() / 5, h = image.height() / 5;
    CImgDisplay main_disp(w, h, "Click a point"), draw_disp(w, h, "Res");
    main_disp.display(image);
    draw_disp.display(res);
    while (!main_disp.is_closed() && !draw_disp.is_closed())
    {
        main_disp.wait();
        if (main_disp.button() && main_disp.mouse_y() >= 0 && main_disp.mouse_x() >= 0) {
            const int x = main_disp.mouse_x() * image.width() / (double)(main_disp.width());
            const int y = main_disp.mouse_y() * image.height() / (double)(main_disp.height());
            setPixel(image, x, y, res);
            draw_disp.display(res);
            std::cout << x << " " << y << " " << "\n";
        }
    }
    return 0;
}