#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "vectorclass.hpp"

template<typename T>
class Triangle3D : public Vector3D<T>
{
public:
    //constructors
    Triangle3D() : point1(), point2(), point3() {};
    Triangle3D(const Vector3D<T> &p1, const Vector3D<T> &p2, const Vector3D<T> &p3) : point1(p1), point2(p2), point3(p3) {};

    //set methods
    void setPoint1(Vector3D<T> p1) { point1(p1); }
    void setPoint2(Vector3D<T> p2) { point2(p2); }
    void setPoint3(Vector3D<T> p3) { point3(p3); }

    //get methods
    T getPoint1() { return point1; }
    T getPoint2() { return point2; }
    T setPoint3() { return point3; }
private:
    Vector3D<T> point1;
    Vector3D<T> point2;
    Vector3D<T> point3;
};

using TriangleF = Triangle3D<float>;
#endif // TRIANGLE_HPP
