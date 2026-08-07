#pragma once 
#include"Vector3.cuh"

class BlackHole {

public: 
  __host__ __device__ BlackHole(Vector3 pos, float m);
  __host__ __device__ float getEvenHorizon() const;
  __host__ __device__ Vector3 getPosition() const;
  __device__ Vector3 computeAcceleration(const Vector3& rayPos, 
                                         const Vector3& rayVel) const;



private: 
  Vector3 position;
  float mass; 
  float G;
  float c;



};