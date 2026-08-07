#include "rayTraceKernel.cuh"
#include <iostream>
#include <fstream>

int main()
{
  const int width = 1024;
  const int height = 768;

  //호스트 환경에서 개체 인스턴스 초기화

  Camera hostCamera(Vector3 (0.0f, 0.0f, -15.0f), width, height );
  BlackHole hostBlackHole(Vector3(0.0f, 0.0f, 0.0f), 1.0f);
  
  size_t imgSize = width * height * sizeof(uchar3);
  uchar3* h_output = (uchar3*)malloc(imgSize);
  uchar3* d_output;
  cudaMalloc(&d_output, imgSize);

  dim3 blockSize(16, 16);
  dim3 gridSize((width * blockSize.x -1) / blockSize.x, (height + blockSize.y -1)/ blockSize.y);
  
  std::cout << "OOP 기반 CUDA 블랙홀 레이 트레이싱 가속 시작.. " << std::endl;

  rayTraceKernel <<<gridSize, blockSize>>> (d_output, hostCamera, hostBlackHole);
  
  cudaDeviceSynchronize();
  cudaMemcpy(h_output, d_output, imgSize, cudaMemcpyDeviceToHost);

  std::ofstream imgFile("blackhole_oop_cuda.ppm");
  imgFile << "P3\n" << width << " " << height << "\n255\n";

  for (int i =0; i < width * height ; ++i)
  {
    imgFile << (int)h_output[i].x << " " << (int)h_output[i].y << " " << (int)h_output[i].z <<"\n";
  }
  imgFile.close();

  std::cout << "렌더링 완료! 'blackhole_oop_cuda.ppm' 저장됨" << std::endl;

  cudaFree(d_output);
  free(h_output);
  return 0;
} 