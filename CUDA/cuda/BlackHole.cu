#include "BlackHole.cuh"

__host__ __device__ BlackHole::BlackHole(Vector3 pos, float m)
                    : position(pos),
                      mass(m),
                      G(1.0f),
                      c(1.0f)
{
}

__host__ __device__ float BlackHole::getEvenHorizon() const const
{ 
     return (2.0f*G*mass)/(c*c);

}

__host__ __device__ Vector3 BlackHole::getPosition() const
{
    return position;
}

__device__ Vector3 BlackHole::computeAcceleration(const Vector3& rayPos, 
                                                  const Vector3& rayVel) const
{
      //광자의 위치와 속도를 받아 중력 가속도를 계산하는 메소드
      Vector3 relativePos = rayPos - position;
      float rSq = relativePos.lengthSq();
      float r = sqrtf(rSq);

      // 상대론적 각 운동량 L = r x v 
      Vector3 L_vec = relativePos.cross(rayVel);
      float L2 = L_vec.lengthSq();

      // 아인슈타인 일반상대성 근사 보정이 적용된 중력 가속도 
      float accelMagnitude = 
      (3.0f * G * mass* L2) / (c * c * powf(r, 5.0f));
      return relativePos.normalize()* (-accelMagnitude);
}

