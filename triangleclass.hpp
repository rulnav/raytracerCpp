#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "vectorclass.hpp"

template<typename T>
class Triangle3 : public MyVec::Vector3<T>
{
public:
    //triangle vertexs
    MyVec::Vector3<T> vertex1;
    MyVec::Vector3<T> vertex2;
    MyVec::Vector3<T> vertex3;
    //constructors
    Triangle3() : vertex1(), vertex2(), vertex3(), edge1(), edge2() {};
    Triangle3(const MyVec::Vector3<T> &p1, const MyVec::Vector3<T> &p2, const MyVec::Vector3<T> &p3) : vertex1(p1), vertex2(p2), vertex3(p3) {
        calculateEdges();
    }
    //properties
    T area(){
        return faceBetween(edge1, edge2);
    }

    MyVec::Vector3<T> normalVector(){
        return MyVec::crossProduct(edge1, edge2);
    }

private:
    //triangle edges
    MyVec::Vector3<T> edge1;
    MyVec::Vector3<T> edge2;

    void calculateEdges(){
        edge1 = vertex2 - vertex1;
        edge2 = vertex3 - vertex1;
    }
};

using Triangle3f = Triangle3<float>;
#endif // TRIANGLE_HPP
