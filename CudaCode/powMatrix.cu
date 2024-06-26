#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
// #include <omp.h> // Để sử dụng OpenMP Khoong dung duoc trong CUDA
#define U64 uint64_t
#define U32 uint32_t
#define U16 uint16_t
#define U8 uint8_t
#define I64 int64_t
#define I32 int32_t
#define I16 int16_t
#define I8 int8_t
#define F16 float
#define loop(i, a, b) for (I64 i = a; i < b; i++)
#define glo_n 26
#define MAX_NUM_THREADS 1024
// const U32 glo_length = 1 << glo_n;
#define glo_length 676 // 12 4096ULL // 16 65536ULL// 20 - 1048576 //24 16777216ULL // 30 1073741824ULL  //32 4294967296ULL //34 17179869184ULL // 36 68719476736ULL

// ------------------------ Begin kerner Functions -----------------------------
__global__ void squareMatrix(float *matrix)
{
    // int i = blockIdx.x * blockDim.x + threadIdx.x;
    int row = blockIdx.x;
    int col = threadIdx.x;
    int length = blockDim.x;
    float newVal = 0;
    loop(i, 0, length)
    {
        newVal += matrix[row * length + i] * matrix[i * length + col];
    }
    matrix[row * length + col] = newVal;
}
F16 *global_table_GPU;
bool create_dynamic_array_cuda_for_F2()
{
    cudaError_t cudaStatus;
    cudaStatus = cudaMallocManaged(&global_table_GPU, glo_length * sizeof(F16));
    if (cudaStatus == cudaSuccess)
    {
        printf("Cấp phát động thành công cho global_table.\n");
    }
    else
    {
        printf("Cấp phát động không thành công cho global_table: %s\n", cudaGetErrorString(cudaStatus));
        return 0;
    }
    // cudaMemset(global_table_GPU, 0, glo_length * sizeof(I8));
    return 1;
}

int main()
{
    printf("start\n");
    float test[glo_n][glo_n] = {
        {0.005, 0.025, 0.035, 0.065, 0.003, 0.014, 0.035, 0.005, 0.040, 0.005, 0.008, 0.078, 0.003, 0.210, 0.003, 0.018, 0.000, 0.104, 0.095, 0.160, 0.001, 0.031, 0.010, 0.001, 0.011, 0.001},
        {0.081, 0.000, 0.000, 0.000, 0.344, 0.000, 0.000, 0.000, 0.050, 0.013, 0.000, 0.138, 0.000, 0.000, 0.069, 0.000, 0.000, 0.094, 0.025, 0.013, 0.081, 0.000, 0.000, 0.000, 0.094, 0.000},
        {0.113, 0.000, 0.025, 0.004, 0.243, 0.000, 0.000, 0.116, 0.060, 0.000, 0.035, 0.032, 0.004, 0.000, 0.176, 0.011, 0.000, 0.035, 0.000, 0.099, 0.039, 0.000, 0.000, 0.000, 0.011, 0.000},
        {0.100, 0.040, 0.022, 0.012, 0.162, 0.045, 0.007, 0.022, 0.140, 0.000, 0.002, 0.010, 0.037, 0.015, 0.040, 0.010, 0.000, 0.052, 0.045, 0.132, 0.047, 0.012, 0.037, 0.000, 0.007, 0.000},
        {0.065, 0.016, 0.043, 0.097, 0.040, 0.031, 0.015, 0.012, 0.039, 0.001, 0.003, 0.043, 0.042, 0.114, 0.027, 0.029, 0.005, 0.149, 0.116, 0.051, 0.007, 0.020, 0.024, 0.009, 0.004, 0.000},
        {0.073, 0.011, 0.019, 0.004, 0.073, 0.080, 0.004, 0.011, 0.115, 0.008, 0.000, 0.042, 0.004, 0.000, 0.195, 0.000, 0.000, 0.099, 0.031, 0.179, 0.023, 0.011, 0.011, 0.000, 0.008, 0.000},
        {0.101, 0.020, 0.015, 0.010, 0.176, 0.005, 0.015, 0.075, 0.090, 0.000, 0.000, 0.025, 0.005, 0.020, 0.106, 0.005, 0.005, 0.101, 0.045, 0.106, 0.045, 0.000, 0.025, 0.000, 0.005, 0.000},
        {0.187, 0.002, 0.006, 0.000, 0.501, 0.009, 0.002, 0.011, 0.106, 0.000, 0.000, 0.000, 0.006, 0.004, 0.082, 0.002, 0.000, 0.006, 0.019, 0.033, 0.011, 0.000, 0.009, 0.000, 0.006, 0.000},
        {0.051, 0.009, 0.066, 0.030, 0.032, 0.012, 0.014, 0.004, 0.000, 0.000, 0.003, 0.049, 0.032, 0.260, 0.072, 0.015, 0.001, 0.059, 0.102, 0.151, 0.001, 0.028, 0.000, 0.005, 0.000, 0.004},
        {0.188, 0.000, 0.000, 0.000, 0.312, 0.000, 0.000, 0.000, 0.062, 0.000, 0.000, 0.000, 0.000, 0.000, 0.250, 0.000, 0.000, 0.000, 0.000, 0.000, 0.188, 0.000, 0.000, 0.000, 0.000, 0.000},
        {0.024, 0.000, 0.000, 0.000, 0.268, 0.000, 0.000, 0.000, 0.317, 0.000, 0.000, 0.000, 0.000, 0.049, 0.049, 0.000, 0.000, 0.000, 0.146, 0.049, 0.024, 0.000, 0.049, 0.000, 0.024, 0.000},
        {0.125, 0.006, 0.014, 0.034, 0.177, 0.020, 0.014, 0.006, 0.120, 0.003, 0.003, 0.151, 0.006, 0.006, 0.071, 0.003, 0.003, 0.006, 0.046, 0.066, 0.026, 0.000, 0.003, 0.000, 0.094, 0.000},
        {0.214, 0.058, 0.004, 0.000, 0.263, 0.000, 0.000, 0.012, 0.152, 0.000, 0.000, 0.000, 0.029, 0.004, 0.070, 0.074, 0.004, 0.008, 0.049, 0.012, 0.033, 0.000, 0.004, 0.000, 0.008, 0.000},
        {0.056, 0.013, 0.063, 0.162, 0.084, 0.025, 0.141, 0.016, 0.040, 0.001, 0.008, 0.008, 0.012, 0.009, 0.072, 0.009, 0.001, 0.009, 0.059, 0.165, 0.008, 0.001, 0.020, 0.000, 0.016, 0.000},
        {0.011, 0.018, 0.021, 0.026, 0.008, 0.144, 0.005, 0.008, 0.021, 0.000, 0.000, 0.029, 0.062, 0.202, 0.020, 0.035, 0.000, 0.137, 0.035, 0.063, 0.083, 0.024, 0.042, 0.000, 0.006, 0.002},
        {0.105, 0.006, 0.000, 0.000, 0.204, 0.000, 0.000, 0.022, 0.044, 0.000, 0.000, 0.083, 0.006, 0.000, 0.149, 0.050, 0.000, 0.182, 0.077, 0.039, 0.033, 0.000, 0.000, 0.000, 0.000, 0.000},
        {0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 1.000, 0.000, 0.000, 0.000, 0.000, 0.000},
        {0.122, 0.012, 0.023, 0.034, 0.247, 0.006, 0.012, 0.012, 0.113, 0.001, 0.015, 0.007, 0.038, 0.023, 0.088, 0.006, 0.000, 0.035, 0.054, 0.081, 0.009, 0.016, 0.006, 0.000, 0.041, 0.000},
        {0.098, 0.014, 0.026, 0.014, 0.110, 0.020, 0.002, 0.071, 0.113, 0.005, 0.000, 0.011, 0.017, 0.018, 0.085, 0.026, 0.009, 0.014, 0.073, 0.175, 0.053, 0.002, 0.042, 0.000, 0.006, 0.000},
        {0.059, 0.023, 0.007, 0.001, 0.078, 0.005, 0.002, 0.340, 0.130, 0.001, 0.000, 0.014, 0.010, 0.006, 0.081, 0.007, 0.000, 0.050, 0.051, 0.058, 0.022, 0.002, 0.028, 0.000, 0.025, 0.000},
        {0.044, 0.020, 0.036, 0.024, 0.036, 0.004, 0.024, 0.000, 0.036, 0.000, 0.004, 0.077, 0.020, 0.125, 0.004, 0.060, 0.000, 0.190, 0.157, 0.125, 0.000, 0.012, 0.000, 0.000, 0.000, 0.000},
        {0.061, 0.000, 0.000, 0.000, 0.626, 0.000, 0.000, 0.000, 0.243, 0.000, 0.000, 0.000, 0.000, 0.000, 0.043, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.026, 0.000},
        {0.200, 0.006, 0.006, 0.000, 0.211, 0.000, 0.000, 0.183, 0.200, 0.000, 0.000, 0.022, 0.006, 0.044, 0.083, 0.000, 0.000, 0.000, 0.022, 0.011, 0.000, 0.000, 0.006, 0.000, 0.000, 0.000},
        {0.059, 0.000, 0.118, 0.000, 0.000, 0.059, 0.000, 0.000, 0.176, 0.000, 0.000, 0.000, 0.000, 0.000, 0.059, 0.294, 0.000, 0.000, 0.000, 0.176, 0.000, 0.000, 0.059, 0.000, 0.000, 0.000},
        {0.092, 0.033, 0.026, 0.013, 0.046, 0.079, 0.013, 0.039, 0.066, 0.000, 0.000, 0.020, 0.046, 0.033, 0.112, 0.020, 0.000, 0.026, 0.105, 0.197, 0.000, 0.000, 0.033, 0.000, 0.000, 0.000},
        {0.200, 0.000, 0.000, 0.000, 0.800, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000}};
    create_dynamic_array_cuda_for_F2();
    loop(i, 0, glo_n)
        loop(j, 0, glo_n)
            global_table_GPU[i * glo_n + j] = test[i][j];
    int num_pow = 2;
    printf("start\n");
    loop(i, 0, num_pow)
    {
        squareMatrix<<<glo_n, glo_n>>>(global_table_GPU);
        cudaDeviceSynchronize();
    }
    loop(i, 0, glo_n)
    {
        loop(j, 0, glo_n)
            printf("%f,", global_table_GPU[i * glo_n + j]);
        printf("\n");
    }
    cudaFree(global_table_GPU);
    return 0;
}