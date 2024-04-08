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

#define loop(i, a, b) for (I64 i = a; i < b; i++)
#define glo_n 34
#define MAX_NUM_THREADS 1024
// const U32 glo_length = 1 << glo_n;
#define glo_length 17179869184ULL // 12 4096ULL // 16 65536ULL// 20 - 1048576 //24 16777216ULL // 30 1073741824ULL  //32 4294967296ULL //34 17179869184ULL // 36 68719476736ULL

// ------------------------ Begin kerner Functions -----------------------------
__global__ void addKernel(int *c, const int *a, const int *b, int size)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < size)
    {
        c[i] = a[i] + b[i];
    }
}
__global__ void supportF2(I8 *F, const I64 trust_length_block)
{
    U64 i = blockIdx.x * blockDim.x + threadIdx.x;
    F[i + trust_length_block] = F[i] ^ 1;
    // printf("i = %u dim = %u ||",i, blockDim.x);
}
/*
__global__ void supportZhegalkinGPU(U8* BLOCK,const U64 half_length_block, U8* used)
{

    U64 i = blockIdx.x * blockDim.x + threadIdx.x;
    //printf("%u %u %u\n", blockIdx.x, blockDim.x, threadIdx.x);
    U64 idx3 = threadIdx.x;
    used[i] ^= 1;
    if (idx3 < half_length_block) {
        BLOCK[i+ half_length_block] ^= BLOCK[i];
    }
}*/
// zhegalkin
__global__ void supportZhegalkinGPU2(U8 *BLOCK, const U64 half_length_block)
{
    U64 i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i % (half_length_block << 1) < half_length_block)
        BLOCK[i + half_length_block] ^= BLOCK[i];
}
// real
__global__ void supportRealGPU(I8 *BLOCK, const U64 half_length_block)
{
    U64 i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i % (half_length_block << 1) < half_length_block)
        BLOCK[i + half_length_block] -= BLOCK[i];
}
__global__ void supportFourierGPU(I8 *BLOCK, const U64 half_length_block)
{
    U64 i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i % (half_length_block << 1) < half_length_block)
    {
        BLOCK[i] += BLOCK[i + half_length_block];
        BLOCK[i + half_length_block] = BLOCK[i] - 2 * BLOCK[i + half_length_block];
    }
}
// ------------------------ End kerner Functions -----------------------------

// ======================== Begin discret function ===========================
void fastFindCoefficientsZhegalkinGPU(U8 *lst_coefficients)
{
    U64 half_len;
    U64 full_len;
    U64 num_block;
    U8 flag;
    flag = glo_length <= MAX_NUM_THREADS;
    if (flag)
    {
        loop(idx1, 0, glo_n)
        {
            // cudaMemset(global_table_GPU, 1, glo_length * sizeof(U8));
            half_len = 1ULL << idx1;
            full_len = half_len << 1;
            num_block = glo_length / full_len;
            supportZhegalkinGPU2<<<num_block, full_len>>>(lst_coefficients, half_len);
            // Wait for GPU to finish before accessing on host
            cudaDeviceSynchronize();
        }
    }
    else
    {
        loop(idx1, 0, 10)
        {
            // cudaMemset(global_table_GPU, 1, glo_length * sizeof(U8));
            half_len = 1ULL << idx1;
            full_len = half_len << 1;
            num_block = glo_length / full_len;
            supportZhegalkinGPU2<<<num_block, full_len>>>(lst_coefficients, half_len);
            // Wait for GPU to finish before accessing on host
            cudaDeviceSynchronize();
        }
        loop(idx1, 10, glo_n)
        {
            // cudaMemset(global_table_GPU, 1, glo_length * sizeof(U8));
            half_len = 1ULL << idx1;
            // full_len = MAX_NUM_THREADS;
            num_block = glo_length / MAX_NUM_THREADS;
            supportZhegalkinGPU2<<<num_block, MAX_NUM_THREADS>>>(lst_coefficients, half_len);
            // Wait for GPU to finish before accessing on host
            cudaDeviceSynchronize();
        }
    }
}

// Real
void fastFindCoefficientsRealGPU(I8 *lst_coefficients)
{
    U64 half_len;
    U64 full_len;
    U64 num_block;
    U8 flag;
    flag = glo_length <= MAX_NUM_THREADS;
    if (flag)
    {
        loop(idx1, 0, glo_n)
        {
            // cudaMemset(global_table_GPU, 1, glo_length * sizeof(U8));
            half_len = 1ULL << idx1;
            full_len = half_len << 1;
            num_block = glo_length / full_len;
            supportRealGPU<<<num_block, full_len>>>(lst_coefficients, half_len);
            // Wait for GPU to finish before accessing on host
            cudaDeviceSynchronize();
        }
    }
    else
    {
        loop(idx1, 0, 10)
        {
            // cudaMemset(global_table_GPU, 1, glo_length * sizeof(U8));
            half_len = 1ULL << idx1;
            full_len = half_len << 1;
            num_block = glo_length / full_len;
            supportRealGPU<<<num_block, full_len>>>(lst_coefficients, half_len);
            // Wait for GPU to finish before accessing on host
            cudaDeviceSynchronize();
        }
        loop(idx1, 10, glo_n)
        {
            // cudaMemset(global_table_GPU, 1, glo_length * sizeof(U8));
            half_len = 1ULL << idx1;
            // full_len = MAX_NUM_THREADS;
            num_block = glo_length / MAX_NUM_THREADS;
            supportRealGPU<<<num_block, MAX_NUM_THREADS>>>(lst_coefficients, half_len);
            // Wait for GPU to finish before accessing on host
            cudaDeviceSynchronize();
        }
    }
}
void fastFindCoefficientsFourierGPU(I8 *lst_coefficients)
{
    U64 half_len;
    U64 full_len;
    U64 num_block;
    U8 flag;
    flag = glo_length <= MAX_NUM_THREADS;
    if (flag)
    {
        loop(idx1, 0, glo_n)
        {
            // cudaMemset(global_table_GPU, 1, glo_length * sizeof(U8));
            half_len = 1ULL << idx1;
            full_len = half_len << 1;
            num_block = glo_length / full_len;
            supportFourierGPU<<<num_block, full_len>>>(lst_coefficients, half_len);
            // Wait for GPU to finish before accessing on host
            cudaDeviceSynchronize();
        }
    }
    else
    {
        loop(idx1, 0, 10)
        {
            // cudaMemset(global_table_GPU, 1, glo_length * sizeof(U8));
            half_len = 1ULL << idx1;
            full_len = half_len << 1;
            num_block = glo_length / full_len;
            supportFourierGPU<<<num_block, full_len>>>(lst_coefficients, half_len);
            // Wait for GPU to finish before accessing on host
            cudaDeviceSynchronize();
        }
        loop(idx1, 10, glo_n)
        {
            // cudaMemset(global_table_GPU, 1, glo_length * sizeof(U8));
            half_len = 1ULL << idx1;
            // full_len = MAX_NUM_THREADS;
            num_block = glo_length / MAX_NUM_THREADS;
            supportFourierGPU<<<num_block, MAX_NUM_THREADS>>>(lst_coefficients, half_len);
            // Wait for GPU to finish before accessing on host
            cudaDeviceSynchronize();
        }
    }
}
// ======================== End discret function ===========================

// ======================== Begin functions to create F1,F2 ===========================
// phan tao ham F
I64 f = 0;
// U8 *global_table_GPU = (U8 *)calloc(glo_length, sizeof(U8));
// Gán giá trị 1 cho tất cả các phần tử trong mảng bằng hàm memset
I8 *global_table_GPU;
// U8* global_table_CPU;
bool create_dynamic_array_cuda()
{
    cudaError_t cudaStatus;
    cudaStatus = cudaMallocManaged(&global_table_GPU, glo_length * sizeof(I8));

    if (cudaStatus == cudaSuccess)
    {
        printf("Cấp phát động thành công cho global_table.\n");
    }
    else
    {
        printf("Cấp phát động không thành công cho global_table: %s\n", cudaGetErrorString(cudaStatus));
        return 0;
    }
    cudaMemset(global_table_GPU, 1, glo_length * sizeof(I8));
    return 1;
}

bool create_dynamic_array_cuda_for_F2()
{
    cudaError_t cudaStatus;
    cudaStatus = cudaMallocManaged(&global_table_GPU, glo_length * sizeof(I8));
    if (cudaStatus == cudaSuccess)
    {
        printf("Cấp phát động thành công cho global_table.\n");
    }
    else
    {
        printf("Cấp phát động không thành công cho global_table: %s\n", cudaGetErrorString(cudaStatus));
        return 0;
    }
    cudaMemset(global_table_GPU, 0, glo_length * sizeof(I8));
    return 1;
}
void recursive(I64 t1, I16 num_loop)
{
    if (num_loop)
    {
        I64 t2 = 1 << num_loop;
        while (t2 < t1)
        {
            f ^= t2;
            recursive(t2, num_loop - 1);
            f ^= t2;
            t2 <<= 1;
        }
    }
    else
    {
        I64 t2 = 1;
        while (t2 < t1)
        {
            f ^= t2;
            // printf("%u,", f);
            global_table_GPU[f] = 0;
            f ^= t2;
            t2 <<= 1;
            //++c;
        }
    }
}
void calcF1SpAuto()
{
    global_table_GPU[0] = 0;
    f = 0;
    loop(t, 0, (glo_n >> 1) - 1)
    {
        // c = 0;
        recursive(glo_length, t);
        // printf("t = %u ; c = %u\n", t, c);
    }
}
// tao F2
bool calcF2CPU()
{
    global_table_GPU[0] = 1;
    global_table_GPU[1] = 0;
    U64 current_leng = 2;
    while (current_leng < glo_length)
    {
        for (I64 i = 0; i < current_leng; i++)
        {
            global_table_GPU[i + current_leng] = global_table_GPU[i] ^ 1;
            // printf("i = %i,", i);
        }
        current_leng <<= 1;
    }
    return true;
    // return global_table_GPU;
}
bool calcF2GPU()
{
    global_table_GPU[0] = 1;
    global_table_GPU[1] = 0;
    U64 current_leng = 2;
    U16 default_length_block = 1 << 8;
    U32 num_block;
    while (current_leng < glo_length)
    {
        // for (I64 i = 0; i < current_leng; i++)
        //{
        //     global_table_GPU[i + current_leng] = global_table_GPU[i] ^ 1;
        // printf("i = %i,", i);
        //}
        num_block = current_leng / default_length_block + 1;
        supportF2<<<num_block, default_length_block>>>(global_table_GPU, current_leng);
        cudaDeviceSynchronize();
        current_leng <<= 1;
    }
    return true;
    // return global_table_GPU;
}
// ======================== End functions to create F1,F2 ===========================

// ======================== Begin functions CODE CPU ===========================
// CODE CPU
void fastFindCoefficientsZhegalkinCPU(U8 *lst_coefficients)
{
    U64 half_len;
    U64 full_len;
    U64 num_turns;
    loop(idx1, 0, glo_n)
    {
        half_len = 1ULL << idx1;
        full_len = half_len << 1;
        num_turns = glo_length / full_len;
        loop(idx2, 0, num_turns)
        {
            loop(idx3, 0, half_len)
                lst_coefficients[idx2 * full_len + half_len + idx3] ^= lst_coefficients[idx2 * full_len + idx3];
        }
    }
}
void fastFindCoefficientsRealCPU(I8 *lst_coefficients)
{
    U64 half_len;
    U64 full_len;
    U64 num_turns;
    loop(idx1, 0, glo_n)
    {
        half_len = 1ULL << idx1;
        full_len = half_len << 1;
        num_turns = glo_length / full_len;
        loop(idx2, 0, num_turns)
        {
            loop(idx3, 0, half_len)
                lst_coefficients[idx2 * full_len + half_len + idx3] -= lst_coefficients[idx2 * full_len + idx3];
        }
    }
}
void fastFindCoefficientsFourierCPU(int8_t *lst_coefficients)
{
    U64 half_len;
    U64 full_len;
    U64 num_turns;
    loop(idx1, 0, glo_n)
    {
        half_len = 1ULL << idx1;
        full_len = half_len << 1;
        num_turns = glo_length / full_len;
        loop(idx2, 0, num_turns)
        {
            loop(idx3, 0, half_len)
            {
                lst_coefficients[idx2 * full_len + idx3] += lst_coefficients[idx2 * full_len + idx3 + half_len];
                lst_coefficients[idx2 * full_len + half_len + idx3] = lst_coefficients[idx2 * full_len + idx3] - 2 * lst_coefficients[idx2 * full_len + half_len + idx3];
            }
        }
    }
}
U8 *global_table_CPU;
void create_dynamic_arrayCPU()
{
    global_table_CPU = (U8 *)malloc(glo_length * sizeof(U8)); // Cấp phát bộ nhớ cho mảng
    // memset(global_table_GPU, 1, glo_length * sizeof(I8));
}

// ======================== End functions CODE CPU ===========================

int main()
{

    // int size = 1000;
    // U8* a;
    clock_t start, end;
    double cpu_time_used;

    // U8 b[] = { 0,1,0,1,0,0,1,1,0,1,1,0,1,0,0,1 };
    //  Allocate Unified Memory – accessible from CPU or GPU
    // cudaMallocManaged(&a, glo_length * sizeof(U8));
    // cudaMemset(a, 1, glo_length * sizeof(U8));

    // GPU
    // giai doan 1
    U8 flag = create_dynamic_array_cuda_for_F2();
    if (flag == 0)
        return -17;
    printf("start\n");

    start = clock();
    calcF2GPU();
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Thời gian thực thi giai đoạn 1(GPU): %f giây\n", cpu_time_used);

    // cudaMallocManaged(&global_table_CPU, glo_length * sizeof(U8));
    /*create_dynamic_arrayCPU();
    loop(i, 0, glo_length)
        global_table_CPU[i] = global_table_GPU[i];


   start = clock();
   fastFindCoefficientsZhegalkinCPU(global_table_CPU);
   end = clock();
   cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
   printf("Thời gian thực thi giai đoạn 2(CPU): %f giây\n", cpu_time_used);
   printf("\n");
   */
    //  giai doan 2

    start = clock();
    fastFindCoefficientsFourierGPU(global_table_GPU);
    // printf("finish GPU\n");
    // fastFindCoefficientsZhegalkinCPU(global_table_CPU);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Thời gian thực thi giai đoạn 2(GPU): %f giây\n", cpu_time_used);
    printf("\n");
    /*loop(i, 0, glo_length)
        if (global_table_GPU[i] != global_table_CPU[i])
            printf("Khac nhau tai i = %d", i);

    printf("");*/
    // CPU

    // Wait for GPU to finish before accessing on host
    // cudaDeviceSynchronize();
    /*for (int i = 0; i < glo_length; i++) {
        printf("%u,", a[i]);
    }*/
    // Free memory
    cudaFree(global_table_GPU);
    // cudaFree(global_table_CPU);
    // free(F2);
    return 0;
}