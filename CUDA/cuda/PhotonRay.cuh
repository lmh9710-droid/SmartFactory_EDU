#include "Vector3.cuh"
#include "BlackHole.cuh"

class PhotonRay {
    public:
      __device__ PhotonRay(Vector3 startPos, Vector3 startDir);
      __device__ Vector3 getPosition() const;
      __device__ Vector3 getVelocity() const;

      __device__ void stepRK4(const BlackHole& bh, float dt);

    private:
     Vector3 position;
     Vector3 velocity;
     float c;
};

struct Camera {
  Vector3 position;
  int width;
  int height;
  float aspect;

  __host__ __device__ Camera(Vector3 pos, int w, int h)
                            : position(pos),
                              width(w),
                              height(h),
                              aspect((float)w/(float)h)
                              {}
  __device__ Vector3 generateRayDirection(int x, int y) const
  {
     float u = ((2.0f * x / width) - 1.0f) * aspect;
     float v = (2.0f * y / height) - 1.0f;
     return Vector3(u, v, 1.0f); // 전방(Z축 정방향)을 향함

  }

};