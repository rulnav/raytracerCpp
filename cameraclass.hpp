#ifndef CAMERACLASS_HPP
#define CAMERACLASS_HPP

#include <cmath>
#include "vectorclass.hpp"
#include "matrixclass.hpp"

template<typename T>
class Camera {
public:
    Camera (const Vector3<T>& pos, const Matrix3<T>& matrix) : position(pos), rotationMatrix(matrix) {}
    void truck(const Vector3<T>& moveDirection) {
        position += moveDirection * rotationMatrix;
    }

    void pan(const T& degrees){
        T rads = degrees * (M_PI / 180.0);
        rotationMatrix = rotationMatrix * Matrix3<T> (
                    {{{cos(rads) , 0.0 , -sin(rads)},
                      {0.0		 , 1.0 , 0.0	   },
                      {sin(rads) , 0.0 , cos(rads) }}});
    }
    //getters
    Matrix3<T> getRotationMatrix(){  return rotationMatrix;  }
    Vector3<T> getPosition(){  return position;  }
private:
    //camera position
    Vector3<T> position;
    //rotation matrix
    Matrix3<T> rotationMatrix;
};

using Cameraf = Camera<float>;
#endif // CAMERACLASS_HPP
