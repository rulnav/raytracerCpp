#ifndef MATRIXCLASS_HPP
#define MATRIXCLASS_HPP

#include <array>
#include <cstdint>
#include <cstdio>
#include "vectorclass.hpp"


template<typename T>
class Matrix3
{
public:
    Matrix3() {}
    Matrix3(const std::array<std::array<T,3>,3>& mm) : m(mm) {}
    // Debug
    void printMatrix(){
        for (uint8_t i = 0; i < 3; ++i) {
            for (uint8_t j = 0; j < 3; ++j) {
                printf("%f ", m[i][j]);
            }
            printf("\n");
        }
    }
    // overloads
    const std::array<T,3>& operator [] (uint8_t i) const { return m[i]; }
    std::array<T,3>& operator [] (uint8_t i) { return m[i]; }

    template<typename S>
    friend Vector3<T> operator * (const Matrix3<T>& m, const Vector3<T>& vec);
    template<typename S>
    friend Vector3<T> operator * (const Vector3<T>& vec, const Matrix3<T>& m);
    template<typename S>
    friend Matrix3<T> operator * (const Matrix3<T>& matrix1, const Matrix3<T>& matrix2);
private:
    // initialize the coefficients of the matrix with the coefficients of the identity matrix
    std::array<std::array<T,3>,3> m = {{{1,0,0},
                                        {0,1,0},
                                        {0,0,1}}};
};

using Matrix3f = Matrix3<float>;

template<typename T>
Vector3<T> operator * (const Matrix3<T>& m, const Vector3<T>& vec) {
    return Vector3<T>(
            vec.x * m[0][0] + vec.y * m[0][1] + vec.z * m[0][2],
            vec.x * m[1][0] + vec.y * m[1][1] + vec.z * m[1][2],
            vec.x * m[2][0] + vec.y * m[2][1] + vec.z * m[2][2]);
}

template<typename T>
Vector3<T> operator * (const Vector3<T>& vec, const Matrix3<T>& m) {
    return m * vec;
}

template<typename T>
Matrix3<T> operator * (const Matrix3<T>& matrix1, const Matrix3<T>& matrix2) {
    Matrix3<T> resultMatrix;
    for (uint8_t i = 0; i < 3; ++i) {
        for (uint8_t j = 0; j < 3; ++j) {
        resultMatrix[i][j] = matrix1[i][0] * matrix2[0][j] +
                             matrix1[i][1] * matrix2[1][j] +
                             matrix1[i][2] * matrix2[2][j] ;
        }
    }
    return resultMatrix;
}

template<typename T>
Vector3<T>& operator *= (Vector3<T>& vec, const Matrix3<T>& m){
    vec.x = vec.x * m[0][0] + vec.y * m[0][1] + vec.z * m[0][2];
    vec.y = vec.x * m[1][0] + vec.y * m[1][1] + vec.z * m[1][2];
    vec.z = vec.x * m[2][0] + vec.y * m[2][1] + vec.z * m[2][2];
    return vec;
}
#endif // MATRIXCLASS_HPP
