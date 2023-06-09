#ifndef CAMERACLASS_HPP
#define CAMERACLASS_HPP

#include <cmath>
#include <vector>
#include "vectorclass.hpp"
#include "matrixclass.hpp"

template<typename T>
class Camera {
public:
    //constructor
    Camera (const Vector3<T>& pos, const Matrix3<T>& matrix, const uint32_t& screenWidth, const uint32_t& screenHight) :
        position(pos), rotationMatrix(matrix),
        vectorArray(screenHight, std::vector<Vector3<T>>(screenWidth)) {}
    //Camera movement
    void truck(const Vector3<T>& moveDirection) {
        position = position + (moveDirection * rotationMatrix);
    }

    void pan(const T& degrees){
        T rads = degrees * (M_PI / 180.0);
        rotationMatrix = rotationMatrix * Matrix3<T> (
                    {{{cos(rads) , 0.0 , sin(rads) },
                      {0.0		 , 1.0 , 0.0	    },
                      {-sin(rads) , 0.0 , cos(rads)  }}});
    }

    void tilt(const T& degrees){
        T rads = degrees * (M_PI / 180.0);
        rotationMatrix = rotationMatrix * Matrix3<T> (
                    {{{1.0 , 0.0 	   , 0.0 		},
                      {0.0 , cos(rads) , -sin(rads)	},
                      {0.0 , sin(rads) , cos(rads)  }}});
    }

    void roll(const T& degrees){
        T rads = degrees * (M_PI / 180.0);
        rotationMatrix = rotationMatrix * Matrix3<T> (
                    {{{cos(rads) , -sin(rads) , 0.0 },
                      {sin(rads) , cos(rads)  , 0.0 },
                      {0.0  	 , 0.0    	  , 1.0 }}});
    }
    //getters
    Matrix3<T> getRotationMatrix() const {  return rotationMatrix;  }
    Vector3<T> getPosition() const {  return position;  }
private:
    //camera position
    Vector3<T> position;
    //rotation matrix
    Matrix3<T> rotationMatrix;
    //vector matrix
    std::vector<std::vector<Vector3<T>>> vectorArray;
};

using Cameraf = Camera<float>;
#endif // CAMERACLASS_HPP
