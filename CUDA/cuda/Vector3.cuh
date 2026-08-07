#pragma once 

class Vector3 {
    public:
      float x, y, z;
    
    __host__ __device__ Vector3();
    __host__ __device__ Vector3(float _x, float _y, float _z);

    __host__ __device__ Vector3 operator+(const Vector3& v) const;
    __host__ __device__ Vector3 operator-(const Vector3& v) const;
    __host__ __device__ Vector3 operator*(float s) const;

    __host__ __device__ float lengthSq() const;
    __host__ __device__ float length() const;

    __host__ __device__ Vector3 normalize() const;
    __host__ __device__ Vector3 cross(const Vector3& v) const;
};