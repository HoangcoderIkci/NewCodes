#include <stdint.h>
#include <stdio.h>
#include <cstdlib>
#define U8 uint8_t
#define U16 uint16_t
#define U32 uint32_t
#define loop(i, a, n) for (U32 i = a; i < n; i++)
#define loopBack(i, n, a) for (int i = n; i >= a; i--)
#define getBitIndex(x, idx) (((x) >> (idx)) & 1)     // get bit tại index
#define setBitIndex(x, idx) ((x) |= (1 << (idx)))    // set bit tại index = 1
#define clearBitIndex(x, idx) ((x) &= ~(1 << (idx))) // clear bit tại index = 0

U32 matrixMulcol(U32 a, U32 *matrix, int size)
{
    U32 res = 0;
    U32 temp = 0;
    U32 x = 0;
    // U8 t = 0;
    for (int i = 0; i < size; i++)
    {
        temp ^= matrix[i];
    }
    for (int t = 0; t < size; t++)
    {
        if (a & 0b1)
        {
            res |= temp & (1 << t);
        }
        a >>= 1;
    }
    return res;
}
U32 matrixMultiplication(U32 a, U32 *matrix, int size)
{
    U32 res = 0;
    for (int i = size - 1; i >= 0; i--)
    {
        if (a & 0b1)
            res ^= matrix[i];
        a >>= 1;
    }
    return res;
}
U32 scalarProduc(U32 a, U32 b)
{
    U32 res = 0;
    a = a ^ b;
    while (a)
    {
        res ^= (a & 0b1);
        a >>= 1;
    }
    return res;
}
// đưa matrix về dạng chuẩn tắc
U32 *changeMatrix(U32 arr[], U32 row, U32 col)
{
    U32 *matrix = (U32 *)malloc(row * sizeof(U32));
    U32 temp1 = 0, t2;
    loop(i, 0, row)
    {
        temp1 = 0;
        t2 = arr[i];
        loop(j, 0, col)
        {
            temp1 = (temp1 << 1) ^ (t2 & 0b1);
            t2 >>= 1;
        }
        matrix[i] = temp1;
    }
    // loop(i, 0, row)
    // {
    //     loop(k, 0, col)
    //     {
    //         printf("%d ", getBitIndex(matrix[i], k));
    //     }
    //     printf("\n");
    // }
    // printf("\n");
    U32 rank = 0, idx = 0, temp_to_swap;
    U32 arrIndexBasic = 0;
    // bước 1 đưa dạng bậc thang
    loop(j, 0, col)
    {
        // begin tìm vị trí đầu tiên khác 0
        idx = 100;
        loop(i, rank, row)
        {
            if (getBitIndex(matrix[i], j))
            {
                idx = i;
                break;
            }
        }
        // end tìm vị trí đầu tiên khác 0
        if (idx != 100) // trường hợp tìm được vị trí có phần tử khác 0
        {
            // đảo chỗ 2 hàng
            temp_to_swap = matrix[rank];
            matrix[rank] = matrix[idx];
            matrix[idx] = temp_to_swap;
            // biến các hàng bên dưới về 0
            loop(i, rank + 1, row)
            {
                if (getBitIndex(matrix[i], j))
                {
                    matrix[i] ^= matrix[rank];
                }
            }
            setBitIndex(arrIndexBasic, j); // đưa vào trong basic
            rank++;                        // tăng rank
        }
        // printf("rank = %d \n", rank);
        // loop(i, 0, row)
        // {
        //     loop(k, 0, col)
        //     {
        //         printf("%d ", getBitIndex(matrix[i], k));
        //     }
        //     printf("\n");
        // }
        // printf("\n");
    }
    // bước 2 đưa dạng đường chéo chứa 1
    U32 temp_rank = rank;
    loopBack(j, col - 1, 1) // dòng cuối k cần làm gì cả
    {
        if (getBitIndex(arrIndexBasic, j))
        { // cột trong basic
            --temp_rank;
            loop(i, 0, temp_rank)
            {
                // printf("%d %d\n", matrix[i], getBitIndex(matrix[i], j));
                if (getBitIndex(matrix[i], j))
                {
                    matrix[i] ^= matrix[temp_rank];
                }
            }
        }
        // printf("rank = %d \n", temp_rank);
        // loop(i, 0, row)
        // {
        //     loop(k, 0, col)
        //     {
        //         printf("%d ", getBitIndex(matrix[i], k));
        //     }
        //     printf("\n");
        // }
    }
    loop(i, 0, row)
    {
        temp1 = 0;
        t2 = matrix[i];
        loop(j, 0, col)
        {
            temp1 = (temp1 << 1) ^ (t2 & 0b1);
            t2 >>= 1;
        }
        matrix[i] = temp1;
    }
    return matrix;
}
void printMatrixBinary(U32 *matrix, U32 row, U32 col)
{
    loop(i, 0, row)
    {
        loopBack(k, col - 1, 0)
        {
            printf("%d ", getBitIndex(matrix[i], k));
        }
        printf("\n");
    }
}
void printMatrixHex(U32 *matrix, U32 row)
{
    loop(i, 0, row)
    {
        printf("%x ", matrix[i]);
    }
    printf("\n");
}
U32 *findInvMatrix(U32 *matrix, U32 size)
{
    U32 *matrix_temp = (U32 *)malloc(size * sizeof(U32));
    loop(i, 0, size)
    {
        matrix_temp[i] = (matrix[i] << size) ^ (1 << (size - 1 - i));
    }
    U32 *newMatrix = changeMatrix(matrix_temp, size, size << 1);
    free(matrix_temp);
    // lấy phần nghịch đảo
    U32 limit = (1 << size) - 1;
    loop(i, 0, size)
        newMatrix[i] &= limit;
    printMatrixHex(newMatrix, size);
    return newMatrix;
}
U32 *affineTransformWalshaAdamara(U32 *A, U32 a, int *trustable, U32 n)
{
    U32 size = (1 << n);
    U32 *newTrustTable = (U32 *)malloc(size * sizeof(U32));
    int coeff = 0;
    U32 c;
    U8 flag;
    U32 *A_inv = findInvMatrix(A, n);
    loop(b, 0, size)
    {
        c = matrixMulcol(b, A_inv, n);
        flag = scalarProduc(a, c);
        if (flag)
        {
            newTrustTable[b] = -trustable[c];
        }
        else
        {
            newTrustTable[b] = trustable[c];
        }
    }
    return newTrustTable;
}
void binaryInsertionSort(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int left = 0;
        int right = i - 1;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (arr[mid] > key)
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }

        for (int j = i - 1; j >= left; j--)
        {
            arr[j + 1] = arr[j];
        }
        arr[left] = key;
    }
}
void sortCoefficientsWalshaAdamara(int *trustable, U32 n)
{
    int size = (1 << n);
    loop(i, 0, size)
    {
        if (trustable[i] < 0)
            trustable[i] *= -1;
    }
    binaryInsertionSort(trustable, size);
}
int main()
{
    U32 a = 0b1011;
    U32 arrtemp[4] = {0x2, 0x5, 0x6, 0x7};
    U32 *arr = (U32 *)malloc(4 * sizeof(U32));
    for (int i = 0; i < 4; i++)
    {
        arr[i] = arrtemp[i];
    }

    printMatrixHex(arr, 4);
    // printf("%u\n", matrixMultiplication(a, arr, 4));
    U32 matrix = matrixMulcol(a, arr, 4);
    // printMatrixHex(matrix, 4);
    printf("matrix = %u\n", matrix);
    free(arr);
    return 0;
}