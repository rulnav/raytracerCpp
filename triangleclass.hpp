#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "vectorclass.hpp"

template<typename T>
class Triangle3 : public Vector3<T>
{
public:
    //triangle vertexs
    Vector3<T> vertex1;
    Vector3<T> vertex2;
    Vector3<T> vertex3;
    //constructors
    Triangle3() : vertex1(), vertex2(), vertex3(), edge1(), edge2(), edge3() {};
    Triangle3(const Vector3<T> &p1, const Vector3<T> &p2, const Vector3<T> &p3) : vertex1(p1), vertex2(p2), vertex3(p3) {
        calculateEdges();
    }
    //properties
    T area() const{
        return normalVector().calculateLength() / 2;
    }

    Vector3<T> normalVector() const{
        return crossProduct(edge1, Vector3<T>(0) - edge3);
    }

    Vector3<T> rayFromOriginToPointInPlane(const Vector3<T>& origin, const Vector3<T>& dirRay) const{
        T dirRayLen = dirRay.calculateLength();
        return origin + Vector3<T>( dirRay * Vector3<T>(dirRayLen * vertex1.z / dirRay.z));
    }

private:
    //triangle edges
    Vector3<T> edge1;
    Vector3<T> edge2;
    Vector3<T> edge3;

    void calculateEdges(){
        edge1 = vertex2 - vertex1;
        edge2 = vertex3 - vertex2;
        edge3 = vertex1 - vertex3;
    }
};

using Triangle3f = Triangle3<float>;
#endif // TRIANGLE_HPP
