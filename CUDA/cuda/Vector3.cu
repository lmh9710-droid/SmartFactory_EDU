#include "Vector3.cuh"
#include <iostream>
#include <fstream>
#include <cmath>
#include <cuda_runtime.h>

__host__ __device__ Vector3::Vector3()
    : x(0),
      y(0),
      z(0)
{
}

__host__ __device__ Vector3::Vector3(float _x, float _y, float _z)
    : x(_x),
      y(_y),
      z(_z)
{
}

__host__ __device__ Vector3 Vector3::operator+(const Vector3 &v) const
{
    return Vector3(x + v.x, y + v.y, z + v.z);
}

__host__ __device__ Vector3 Vector3::operator-(const Vector3 &v) const
{
    return Vector3(x - v.x, y - v.y, z - v.z);
}

__host__ __device__ Vector3 Vector3::operator*(float s) const
{
    return Vector3(x * s, y * s, z * s);
}

__host__ __device__ float Vector3::lengthSq() const
{
    return x * x + y * y + z * z;
}

__host__ __device__ float Vector3::length() const
{
#ifdef __CUDA_ARCH__
    return norm3df(x, y, z);
#else
    return std::sqrt(x * x + y * y + z * z);
#endif
}

__host__ __device__ Vector3 Vector3::normalize() const
{
    float len = length();
    if (len > 0.0f)
    {
        return Vector3(x / len, y / len, z / len);
    }
    return Vector3(0, 0, 0);
}

__host__ __device__ Vector3 Vector3::cross(const Vector3& v) const 
{
    return Vector3(y*v.z - z*v.y, z*v.x-x*v.z, x*v.y - y*v.x);
}
