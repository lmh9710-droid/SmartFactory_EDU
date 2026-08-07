#include "PhotonRay.cuh"

__device__ PhotonRay::PhotonRay(Vector3 startPos, Vector3 startDir)
                      : position(startPos),
                        c(1.0f)
{
    velocity = startDir.normalize() * c;
}

__device__ Vector3 PhotonRay::getPosition() const 
{
    return position; 
}

__device__ Vector3 PhotonRay::getVelocity() const
{
    return velocity;
}

__device__ void PhotonRay::stepRK4(const BlackHole& bh, float dt) 
{
    Vector3 k1_v = bh.computeAcceleration(position, velocity) * dt;
    Vector3 k1_p = velocity * dt;

    Vector3 k2_v = bh.computeAcceleration(position + k1_p * 0.5f, velocity + k1_v * 0.5f) * dt;
    Vector3 k2_p = (velocity + k1_v * 0.5f) * dt;

    Vector3 k3_v = bh.computeAcceleration(position + k2_p * 0.5f, velocity + k2_v * 0.5f) * dt;
    Vector3 k3_p = (velocity + k2_v * 0.5f) * dt;

    Vector3 k4_v = bh.computeAcceleration(position + k3_p, velocity + k3_v) * dt;
    Vector3 k4_p = (velocity + k3_v) * dt;

    velocity = velocity + (k1_v + k2_v * 2.0f + k3_v * 2.0f + k4_v) * (1.0f / 6.0f);
    position = position + (k1_p + k2_p * 2.0f + k3_p * 2.0f + k4_p) * (1.0f / 6.0f);

    //광자의 속도가 빛의 속도(c)를 유지하도록 정규화 보정

    velocity = velocity.normalize() * c;
}