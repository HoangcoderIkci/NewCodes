#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#define MAX_SIZE 100 // Giới hạn kích thước của mảng kết quả
#define U32 uint_fast32_t
U32 Arrangement_global[MAX_SIZE][MAX_SIZE];

void generatePermutation(U32 *count, U32 arr[], bool used[], U32 n, U32 k, U32 index)
{
    if (index == k)
    {
        for (U32 i = 0; i < k; i++)
        {
            Arrangement_global[*count][i] = arr[i];
        }
        (*count)++;
        return;
    }

    for (U32 i = 0; i < n; i++)
    {
        if (!used[i])
        {
            arr[index] = i;
            used[i] = true;
            generatePermutation(count, arr, used, n, k, index + 1);
            used[i] = false; // Quay lui (backtrack)
        }
    }
}

int main()
{
    U32 n = 4; // Số phần tử tối đa
    U32 k = 3; // Chập k của chỉnh hợp

    U32 arr[k];
    bool used[n]; // Mảng theo dõi các phần tử đã sử dụng
    for (U32 i = 0; i < n; i++)
    {
        used[i] = false;
    }

    U32 count = 0; // Đếm số chỉnh hợp

    generatePermutation(&count, arr, used, n, k, 0);
    printf("Count = %d\n", count);
    // In tất cả các chỉnh hợp
    for (U32 i = 0; i < count; i++)
    {
        for (U32 j = 0; j < k; j++)
        {
            printf("%d ", Arrangement_global[i][j]);
        }
        printf("\n");
    }

    return 0;
}
