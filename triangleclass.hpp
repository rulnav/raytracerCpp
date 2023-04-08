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
    Triangle3() : vertex1(), vertex2(), vertex3(), edge1(), edge2() {};
    Triangle3(const Vector3<T> &p1, const Vector3<T> &p2, const Vector3<T> &p3) : vertex1(p1), vertex2(p2), vertex3(p3) {
        calculateEdges();
    }
    //properties
    T area() const{
        return crossProduct(edge1, edge2).length() / 2;
    }

    Vector3<T> normalVector() const{
        return crossProduct(edge1, edge2);
    }

private:
    //triangle edges
    Vector3<T> edge1;
    Vector3<T> edge2;

    void calculateEdges(){
        edge1 = vertex2 - vertex1;
        edge2 = vertex3 - vertex1;
    }
};

using Triangle3f = Triangle3<float>;
#endif // TRIANGLE_HPP
