#pragma once
#include <cmath>

//Creating new namespace 

namespace Teravox{

    //Defining structure

    struct Vec3{

        float x, y, z;

        //1.Constructor 

        Vec3(float X = 0.0f, float Y = 0.0f, float Z = 0.0f)
        : x(X), y(Y), z(Z) {}

        //2.Vector Addition : overloading '+' operator
        Vec3 operator+(const Vec3& v)const{
            return Vec3(x + v.x,y + v.y,z + v.z);
        }

        //3.Vector Subtraction : overloading '-' operator
        Vec3 operator-(const Vec3& v)const{
            return Vec3(x - v.x,y - v.y,z - v.z);
        }

        //4.Vector scalar multiplication : overloading '*' operator
        Vec3 operator*(const float factor)const{
            return Vec3(x * factor,y * factor,z * factor);
        }

        //5.Vector scalar division : overloading '/' operator
        Vec3 operator/(const float factor)const{

            // checking division by zero 
            if(fabs(factor) < 1e-6f)return Vec3(x,y,z);

            return Vec3(x/factor,y/factor,z/factor);

        }

        //6.Dot product of 2 vectors //

        float dot(const Vec3& v)const{
            return x * v.x + y * v.y + z * v.z;
        }

        //7.Cross product of 2 vectors 
        Vec3 cross(const Vec3& v)const{
            return Vec3(y * v.z - z * v.y,z * v.x - x * v.z,x * v.y - y * v.x);
        }

        //8.Magnitude of vector
        float magnitude()const{
            return sqrt((x * x) + (y * y) + (z * z));
        }

        //9.Normalizing vector 
        void normalize(){
            float mag = magnitude();

            if(fabs(mag) < 1e-6f)return ;

            x /= mag;
            y /= mag;
            z /= mag;
            return ;
        }

        //10.Normalized 
        Vec3 normalized()const{
            float mag = magnitude();
            if(fabs(mag) < 1e-6f)return Vec3(x,y,z);
            return Vec3(x/mag,y/mag,z/mag);
        }
    };
}