#include "CImg.h"
#include <iostream>
#include <vector>
#include <math.h>
using namespace cimg_library;

struct Point
{
    int x;
    int y;
    Point():x(0), y(0){}
    Point(int x, int y) : x(x), y(y) {}
};
struct BackgroundSearcher
{
    const CImg<unsigned char> &img;
    Point startPixel;
    Point size;
    std::vector<bool> was;
    std::vector<Point> res, neighbors;
    BackgroundSearcher(const CImg<unsigned char> &img): img(img), size(img.width(), img.height())
    {
        was = std::vector<bool>(size.x*size.y);
    }
    int getDistance(Point pixel1, Point pixel2)
    {
        return std::abs(img(pixel1.x, pixel1.y) - img(pixel2.x, pixel2.y))
            + std::abs(img(pixel1.x, pixel1.y, 0, 1) - img(pixel2.x, pixel2.y, 0, 1))
            + std::abs(img(pixel1.x, pixel1.y, 2) - img(pixel2.x, pixel2.y, 2));
    }
    int getDistance(Point pixel)
    {
        return getDistance(startPixel, pixel);
    }
    bool inside(Point a)
    {
        return (a.x >= 0 && a.x < size.x && a.y >= 0 && a.y < size.y);
    }
    int getIndex(Point pixel)
    {
        return pixel.y * size.x + pixel.x;
    }
    bool isTruePixel(Point prev_pixel, Point pixel, int threshold = 3)
    {
        return (inside(pixel) && !was[getIndex(pixel)] && getDistance(prev_pixel, pixel) <= threshold);
    }
    bool isTruePixel(Point pixel, int threshold = 50)
    {
        return isTruePixel(startPixel, pixel, threshold);
    }
    void push_and_visit(Point pixel)
    {
        was[getIndex(pixel)] = true;
        res.push_back(pixel);
        neighbors.push_back(pixel);
    }
    void setNeighbors(Point prevPixel)
    {
        std::vector<Point> localNeighbors = {Point(prevPixel.x - 1, prevPixel.y), Point(prevPixel.x, prevPixel.y - 1),
                                             Point(prevPixel.x + 1, prevPixel.y), Point(prevPixel.x, prevPixel.y + 1)};
        for (Point &p : localNeighbors)
            if (isTruePixel(p))
                push_and_visit(p);
    }
    std::vector<Point>&& search(Point _startPixel)
    {
        std::cout << "res size before search " << res.size() << "\n";
        startPixel = _startPixel;
        push_and_visit(startPixel);
        while (neighbors.size() > 0)
        {
            Point pixel = neighbors.back();
            neighbors.pop_back();
            setNeighbors(pixel);
        }
        neighbors.clear();
        was = std::vector<bool>(size.x*size.y);
        return std::move(res);
    }
};
void setPixel(const CImg<unsigned char> &img, Point p, CImg<unsigned char> &res)
{
    res(p.x, p.y) = img(p.x, p.y);
    res(p.x, p.y, 0, 1) = img(p.x, p.y, 0, 1);
    res(p.x, p.y, 2) = img(p.x, p.y, 2);
}

int main()
{
    CImg<unsigned char> image("girl.bmp"), res(image.width(), image.height(), 1, 3);
    res.fill(255, 255, 255);
    const int w = image.width() / 5, h = image.height() / 5;
    CImgDisplay main_disp(w, h, "Click a point"), draw_disp(w, h, "Res");
    image.blur(2.5);
    main_disp.display(image);
    draw_disp.display(res);
    BackgroundSearcher searcher(image);
    while (!main_disp.is_closed() && !draw_disp.is_closed())
    {
        main_disp.wait();
        if (main_disp.button() && main_disp.mouse_y() >= 0 && main_disp.mouse_x() >= 0) {
            const int x = main_disp.mouse_x() * image.width() / (double)(main_disp.width());
            const int y = main_disp.mouse_y() * image.height() / (double)(main_disp.height());
            auto pixs = searcher.search(Point(x, y));
            std::cout << "x = " << x << " y = " << y << " res size after search = " << pixs.size() << "\n";
            for (auto pix : pixs)
                setPixel(image, pix, res);
            draw_disp.display(res);
        }
    }
    return 0;
}