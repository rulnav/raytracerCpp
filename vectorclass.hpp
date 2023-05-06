#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstdint>
#include <math.h>

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
    T calculateLength() const{
        return sqrt(x*x + y*y + z*z);
    }

    Vector3<T>& normalize() {
        T len = calculateLength();
        if(len > 0){
            x = x/len;
            y = y/len;
            z = z/len;
        }
        return *this;
    }

    //overloads
    const Vector3<T>& operator+=(const Vector3<T>& vec2){
        x += vec2.x,  y += vec2.y,  z += vec2.z;
        return this;
    }

    const Vector3<T>& operator-=(const Vector3<T>& vec2){
        x -= vec2.x,  y -= vec2.y,  z -= vec2.z;
        return *this;
    }

    Vector3<T> operator-() const{
        return Vector3<T>(-x, -y, -z);
    }

    const Vector3<T>& operator*= (const Vector3<T>& vec2){
        x *= vec2.x,  y *= vec2.y,  z *= vec2.z;
        return *this;
    }

private:
};

using Vector3f = Vector3<float>;

//more arithmetics, as free functions
template<typename T>
Vector3<T> crossProduct(const Vector3<T>& vec1, const Vector3<T>& vec2) {
    //cross product is a vector, perpendicular to the two input vectors, and with length equal to the parallelogram they lock between eachother
    return Vector3<T>(vec1.y*vec2.z - vec1.z*vec2.y, vec1.z*vec2.x - vec1.x*vec2.z, vec1.x*vec2.y - vec1.y*vec2.x);
}

template<typename T>
Vector3<T> getNormalCopy(Vector3<T> vec) {
    T len = vec.calculateLength();
    vec.x = vec.x/len;
    vec.y = vec.y/len;
    vec.z = vec.z/len;
    return vec;
}

template<typename T>
T dotProduct(const Vector3<T>& vec1, const Vector3<T>& vec2) {
    return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
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

template<typename T>
Vector3<T> operator*(const Vector3<T>& vec1, const Vector3<T>& vec2){
    return Vector3<T>(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z);
}
#endif
