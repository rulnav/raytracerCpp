#ifndef VECTOR_HPP
#define VECTOR_HPP

#include<math.h>
namespace MyVec{
    template<typename T>
    class Vector3
    {
    public:
        // vector coordinates
        T x, y, z;

        // 3 most basic ways of initializing a vector
        Vector3() : x(T(0)), y(T(0)), z(T(0)) {}
        Vector3(const T &xx) : x(xx), y(xx), z(xx) {}
        Vector3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}

        //vector arithmetics, which should be member functions
        T length(){
            return sqrt(x*x + y*y + z*z);
        }

    private:
    };

    using Vector3f = Vector3<float>;

    //more arithmetics, as free functions
    template<typename T>
    Vector3<T> crossProduct(const Vector3<T>& vec1, const Vector3<T>& vec2) {
        return Vector3<T>(vec1.y*vec2.z - vec1.z*vec2.y, vec1.z*vec2.x - vec1.x*vec2.z, vec1.x*vec2.y - vec1.y*vec2.x);
    }

    template<typename T>
    T faceBetween(const Vector3<T>& vec1, const Vector3<T>& vec2){
        //Heron's formula, to find the area of the triangle (multiply by 2, to get the area of the parallelogram)
        T side1 = vec1.length();
        T side2 = vec2.length();
        T side3 = (vec1 - vec2).length();
        T halfPerimeter = (side1 + side2 + side3)/2;
        return sqrt(halfPerimeter*(halfPerimeter - side1)*(halfPerimeter - side2)*(halfPerimeter - side3));
    }

    //overloads
    template<typename T>
    Vector3<T> operator+(const Vector3<T>& vec1, const Vector3<T>& vec2){
        return Vector3<T>(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
    }

    template<typename T>
    Vector3<T> operator-(const Vector3<T>& vec1, const Vector3<T>& vec2){
        return Vector3<T>(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
    }
}
#endif
