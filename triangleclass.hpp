#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "vectorclass.hpp"

template<typename T>
class Triangle3 : public Vector3<T>
{
public:
    //constructors
    Triangle3() : vertex1(), vertex2(), vertex3(), edge1(), edge2(), edge3() {};
    Triangle3(const Vector3<T> &p1, const Vector3<T> &p2, const Vector3<T> &p3) : vertex1(p1), vertex2(p2), vertex3(p3) {
        calculateEdges();
        calculateNormalOfPlane();
    }
    //properties
    T area() const{
        return calculateNormalOfPlane().calculateLength() / 2;
    }

    bool rayIntersectsTriangle(const Vector3<T>& rayOrigin, const Vector3<T>& rayDirection, Vector3<T>& intersectingRay ) const{
        //check if ray is parallel to triangle
        T projectionOfRayDirectionOntoNormalOfPlane = dotProduct(normalOfPlane, rayDirection);
        if(projectionOfRayDirectionOntoNormalOfPlane == 0)  {
            return false;
        }
        //check if ray hits the triangle's plane from the front
        T distanceFromOriginToPlane = calculateDistanceFromVertexOriginToPlane(rayOrigin);
        if(distanceFromOriginToPlane >= 0)	{
            return false;
        }
        int dirRayLen = 1;  //rayDirection.calculateLength(); //should be one, if we assume rayDirection is normalized
        intersectingRay =  rayOrigin + Vector3<T>( rayDirection * Vector3<T>(dirRayLen * distanceFromOriginToPlane / projectionOfRayDirectionOntoNormalOfPlane ));
        Vector3<T> v1ToIntersectionPoint = intersectingRay - vertex1;
        if(dotProduct(normalOfPlane, crossProduct(edge1, v1ToIntersectionPoint)) <= 0){
            return false;
        }
        Vector3<T> v2ToIntersectionPoint = intersectingRay - vertex2;
        if(dotProduct(normalOfPlane, crossProduct(edge2, v2ToIntersectionPoint)) <= 0){
            return false;
        }
        Vector3<T> v3ToIntersectionPoint = intersectingRay - vertex3;
        if(dotProduct(normalOfPlane, crossProduct(edge3, v3ToIntersectionPoint)) <= 0){
            return false;
        }
        return true;
    }

    T calculateDistanceFromVertexOriginToPlane(const Vector3<T>& rayOrigin) const{
        return dotProduct(normalOfPlane, vertex1 - rayOrigin);
    }

private:
    //triangle edges
    Vector3<T> edge1;
    Vector3<T> edge2;
    Vector3<T> edge3;

    //plane's normal
    Vector3<T> normalOfPlane;

    //triangle vertexs
    Vector3<T> vertex1;
    Vector3<T> vertex2;
    Vector3<T> vertex3;

    void calculateEdges(){
        edge1 = vertex2 - vertex1;
        edge2 = vertex3 - vertex2;
        edge3 = vertex1 - vertex3;
    }

    Vector3<T> calculateNormalOfPlane() {
        normalOfPlane = crossProduct(edge1, Vector3<T>(0) - edge3).normalize();
        return normalOfPlane;
    }

};

using Triangle3f = Triangle3<float>;
#endif // TRIANGLE_HPP
