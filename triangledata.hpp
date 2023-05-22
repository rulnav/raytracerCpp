#ifndef TRIANGLEDATA_HPP
#define TRIANGLEDATA_HPP

#include "triangleclass.hpp"
#include "pixelarray.hpp"

template<typename T>
struct TriangleAndColor {
    Triangle3<T> triangle;
    Pixel color;
    TriangleAndColor(const Triangle3<T>& tri, const Pixel&  pix) : triangle(tri), color(pix){};
};

using TriangleAndColorF = TriangleAndColor<float>;
#endif // TRIANGLEDATA_HPP
