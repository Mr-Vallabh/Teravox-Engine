#pragma once
#include <cmath>

//Creating new namespace 

namespace Teravox{

    //Defining 3D Vector structure 

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

            //If magnitude is 0 then return original vector 

            if(fabs(mag) < 1e-6f)return Vec3(x,y,z);

            return Vec3(x/mag,y/mag,z/mag);
        }
    };

    //Defining 2D Vector structure

    struct Vec2{

        float x,y;

        //1.Constructor for 2D Vector

        Vec2(float X = 0.0f, float Y = 0.0f)
        : x(X), y(Y) {}

        //2.2D Vector addition : overloading '+' operator
        Vec2 operator+(const Vec2& v)const{
            return Vec2(x + v.x,y + v.y);
        }

        //3.2D Vector subtraction : overloading '-' operator
        Vec2 operator-(const Vec2& v)const{
            return Vec2(x - v.x,y - v.y);
        }

        //4.Vector 2D Scalar multiply : overloading '*' operator
        Vec2 operator*(const float factor)const{
            return Vec2(x * factor,y * factor);
        }

        //5.Vector 2D Scalar divide : overloading '/' operator
        Vec2 operator/(const float factor)const{

            // checking division by zero 

            if(fabs(factor) < 1e-6f)return Vec2(x,y);

            return Vec2(x/factor,y/factor);
        }

        //6.Vector 2d dot product 
        float dot(const Vec2& v)const{
            return x * v.x + y * v.y;
        }

        //7.Vector 2d magnitude 
        float magnitude()const{
            return sqrt((x * x) + (y * y));
        }

        //8.Vector 2d normalize original vector
        void normalize(){
            float mag = magnitude();

            if(fabs(mag) < 1e-6f)return ;

            x /= mag;
            y /= mag;

            return ;
        }

        //9.Vector 2d normalized 
        Vec2 normalized()const{

            float mag = magnitude();

            // If magnitude is 0 then return original vector //

            if(fabs(mag) < 1e-6f)return Vec2(x,y);

            return Vec2(x/mag,y/mag);
        }
    };

    //Defining Vector 4 structure

    struct Vec4{

        float x,y,z,w;

        //1.Constructor 

        Vec4(float X = 0.0f,float Y = 0.0f,float Z = 0.0f,float W = 0.0f)
        : x(X), y(Y), z(Z), w(W) {}

        //2.Vector 4 Addtion : overloading '+' operator
        Vec4 operator+(const Vec4& v)const{
            return Vec4(x + v.x,y + v.y,z + v.z,w + v.w);
        }

        //3.Vector 4 Subtraction : overloading '-' operator
        Vec4 operator-(const Vec4& v)const{
            return Vec4(x - v.x,y - v.y,z - v.z,w - v.w);
        }

        //4.Vector 4 Scalar multiply : overloading '*' operator
        Vec4 operator*(const float factor)const{
            return Vec4(x * factor,y * factor,z * factor,w * factor);
        }

        //5.Vector 4 Scalar divide : overloading '/' operator
        Vec4 operator/(const float factor)const{

            // checking division by zero 

            if(fabs(factor) < 1e-6f)return Vec4(x,y,z,w);

            return Vec4(x/factor,y/factor,z/factor,w/factor);
        }

        //6.Vector 4 dot product
        float dot(const Vec4& v)const{
            return x * v.x + y * v.y + z * v.z + w * v.w;
        }
    };
}