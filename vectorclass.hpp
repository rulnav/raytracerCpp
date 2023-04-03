#ifndef VECTOR_HPP
#define VECTOR_HPP

template<typename T>
class Vector3D
{
public:
    // 3 most basic ways of initializing a vector
    Vector3D() : x(T(0)), y(T(0)), z(T(0)) {}
    Vector3D(const T &xx) : x(xx), y(xx), z(xx) {}
    Vector3D(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}

    // get functions for x, y, and z coordinates
    T getX() const { return x; }
    T getY() const { return y; }
    T getZ() const { return z; }

    // set functions for x, y, and z coordinates
    void setX(T xx) { x = xx; }
    void setY(T yy) { y = yy; }
    void setZ(T zz) { z = zz; }


private:
    T x, y, z;
};

using Vector3D_F = Vector3D<float>;

//vector arithmetics
template<typename T>
Vector3D<T> operator+(const Vector3D<T>& vec1, const Vector3D<T>& vec2){
    return Vector3D<T>(vec1.getX() + vec2.getX(), vec1.getY() + vec2.getY(), vec1.getZ() + vec2.getZ());
}

#endif
