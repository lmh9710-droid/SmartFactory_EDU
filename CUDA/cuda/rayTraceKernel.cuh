#include "PhotonRay.cuh"

__global__ void rayTraceKernel(uchar3* d_output, Camera cam, BlackHole bh){
 
    int idx_x = blockIdx.x * blockDim.x + threadIdx.x;
    int idx_y = blockIdx.y * blockDim.y + threadIdx.y;

    if(idx_x >= cam.width || idx_y >= cam.height)
    {
        return; 
    }

    Vector3 rayDir = cam.generateRayDirection(idx_x, idx_y);
    PhotonRay ray(cam.position, rayDir);

    float dt = 0.05f;
    int maxSteps = 400; 
    bool absorbed = false;
    float eventHorizon = bh.getEvenHorizon();

    //추적 루프 진행
    for (int step = 0; step < maxSteps; ++step) {
        Vector3 relativePos = ray.getPosition() - bh.getPosition();
        float currentDist = relativePos.length();

        if (currentDist <= eventHorizon)
        {
            absorbed = true;
        }

        if (currentDist > 30.0f) {
            break;//탈출 성공
        }

        // 광선 스스로 블랙홀의 중력을 받아 궤적 업데이트

        ray.stepRK4(bh, dt);

    }

    int pixelIdx = idx_y * cam.width + idx_x;
    if(absorbed)
    {
        d_output[pixelIdx] = make_uchar3(0, 0, 0);    
    }
    else
    {
        Vector3 finalPos = ray.getPosition();
        int phi = (int)(atan2f(finalPos.y, finalPos.x) * 10.0f);
        int theta = (int)(acosf(finalPos.z / finalPos.length()) * 10.0f);

        if((phi + theta) % 2 == 0) {
            d_output[pixelIdx] = make_uchar3(200, 70, 40);
        } 
        else {
            d_output[pixelIdx] = make_uchar3(25, 25, 50);
        }
    }

}