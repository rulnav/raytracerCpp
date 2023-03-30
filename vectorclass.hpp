#ifndef VECTOR_HPP
#define VECTOR_HPP
template<typename T> 
class Vector 
{ 
public: 
    // 3 most basic ways of initializing a vector
    Vector() : x(T(0)), y(T(0)), z(T(0)) {} 
    Vector(const T &xx) : x(xx), y(xx), z(xx) {} 
    Vector(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {} 
    
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
 
typedef Vector<float> VectorF; 
#endif 
