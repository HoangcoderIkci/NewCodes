#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <iostream>
// #define MAX_SIZE 10000000 // Giới hạn kích thước của mảng kết quả
#define MAX_SIZE 22000 // Giới hạn kích thước của mảng kết quả
// #define U64 uint_fast64_t
#define MAX_COUNT_CLASS 35
#define U32 uint64_t
#define U16 uint_fast16_t
#define U8 uint_fast8_t
#define loop(i, a, n) for (U32 i = a; i < n; i++)
#define loopBack(i, n, a) for (int i = n; i >= a; i--)
#define getBitIndex(x, idx) (((x) >> (idx)) & 1)     // get bit tại index
#define setBitIndex(x, idx) ((x) |= (1 << (idx)))    // set bit tại index = 1
#define clearBitIndex(x, idx) ((x) &= ~(1 << (idx))) // clear bit tại index = 0
#define size 5
U32 MAX_COUNT_FUNC = 1llu;
U32 count_per = 0;
bool *arrStatusFunction;
using namespace std;

// hàm về hoán vị
// Hàm để đổi chỗ hai giá trị
void swap(U32 &a, U32 &b)
{
    int temp = a;
    a = b;
    b = temp;
}

// Hàm đảo ngược dãy từ chỉ số start đến hết
void reverse(U32 arr[], int start, int end)
{
    while (start < end)
    {
        swap(arr[start], arr[end]);
        start++;
        end--;
    }
}

// Hàm tìm hoán vị kế tiếp
bool nextPermutation(U32 arr[], U32 n)
{
    int i = n - 2;

    // Tìm 'pivot'
    while (i >= 0 && arr[i] >= arr[i + 1])
    {
        i--;
    }

    // Nếu không tìm thấy 'pivot', đây là hoán vị cuối cùng
    if (i < 0)
    {
        return false;
    }

    // Tìm 'successor' của 'pivot'
    int j = n - 1;
    while (arr[j] <= arr[i])
    {
        j--;
    }

    // Đổi chỗ
    swap(arr[i], arr[j]);

    // Đảo ngược dãy từ `i+1` đến cuối cùng
    reverse(arr, i + 1, n - 1);
    // loop(i, 0, n)
    //     printf("%d ", arr[i]);
    // printf("\n");
    return true;
}

// Matrix nhập dưới dạng mảng 1 chiều, mỗi phần tử sẽ tương ứng với 1 row ví dụ : Matrix[3] = {1, 2, 4}
// tương ứng với matrix [0,0,1],[0,1,0],[1,0,0]
// Lưu ý hàm SupportProcess đang viết cho trường hợp n = 3
// đưa matrix về dạng chuẩn tắc
void changeMatrix(U32 matrix[], U32 row, U32 col)
{
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
            setBitIndex(arrIndexBasic, col - 1 - j); // đưa vào trong basic
            rank++;                                  // tăng rank
        }
        // printf("rank = %d \n", rank);
        loop(i, 0, row)
        {
            loop(k, 0, col)
            {
                printf("%d ", getBitIndex(matrix[i], k));
            }
            printf("\n");
        }
    }
    // bước 2 đưa dạng đường chéo chứa 1
    U32 temp_rank = rank;
    loopBack(j, col - 1, 0)
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
        printf("rank = %d \n", temp_rank);
        loop(i, 0, row)
        {
            loop(k, 0, col)
            {
                printf("%d ", getBitIndex(matrix[i], k));
            }
            printf("\n");
        }
    }
}

int checkInverseMatrix(U32 arrForCheck[], U32 row, U32 col)
{
    U32 rank = 0, idx = 0, temp_to_swap;
    U32 *matrix;
    matrix = (U32 *)malloc(row * sizeof(U32));
    loop(i, 0, row)
    {
        matrix[i] = arrForCheck[i];
    }
    //   bước 1 đưa dạng bậc thang
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
            // setBitIndex(arrIndexBasic, col - 1 - j); // đưa vào trong basic
            rank++; // tăng rank
        }
    }

    // bước 2 đưa dạng đường chéo chứa 1
    free(matrix);
    return (rank == row);
    // return 1;
}

// in số dạng binary
void printTypeBit(U32 bit, U32 len_bit)
{
    U32 temp = 1 << len_bit - 1;
    loopBack(i, len_bit - 1, 0)
    {
        printf("%i", (temp & bit) >> i);
        temp >>= 1;
    }
    printf("\n");
}
// nhân hàng với Matrix
/*
ví dụ 0b011 * matrix[3] = {0b100, 0b010, 0b001}
    => result = tổng 2 cột cuối.
 */
U32 mulRơwWithMatrix(U32 matrix[], U32 newRow, U32 row, U32 col)
{
    U32 res = 0;
    loopBack(i, col - 1, 0)
    {
        if (newRow & 0b1)
        {
            res ^= matrix[i];
        }
        newRow >>= 1;
    }
    return res;
}

// hàm tạo chỉnh hợp k,n

void generatePermutation(U32 *count, U32 arr[], bool used[], U32 n, U32 k, U32 index, U32 trustTable, U32 *length, U32 idx_current = 1)
{
    if (index == k)
    {
        U32 alpha;
        U32 res;
        U32 flag;
        U32 temp_count = *count;
        U32 arrTemp[size];
        // chắc chắn nghịch đảo rồi
        loop(idx, 0, size)
        {
            // Arrangement_global[count][idx] = arr[idx];
            arrTemp[idx] = arr[idx];
        }
        // printf("\n");
        //  giờ cần thêm cả các hoán vị của nó vào nữa
        do
        {
            // Biến đổi trustable
            loop(i_col, 0, (1 << size))
            {
                res = 0;
                loop(t, 0, (1 << size)) // Biến đổi trustTable
                {
                    alpha = mulRơwWithMatrix(arrTemp, t, size, size);
                    alpha ^= i_col;
                    flag = getBitIndex(trustTable, alpha);
                    if (flag)
                        res ^= (((U32)1) << t);
                }
                if (arrStatusFunction[res] == true)
                {
                    (*length)++;
                    arrStatusFunction[res] = false;
                }
                temp_count++;
                // printf("count: %d\n", temp_count);
            }
        } while (nextPermutation(arrTemp, k));
        *count = temp_count;
        // count++;
    }
    else
    {
        for (U32 i = idx_current; i < n; i++)
        {
            if (!used[i])
            {
                // kiểm tra xem thêm vào có oki không
                arr[index] = i;
                if (checkInverseMatrix(arr, index + 1, size) == 0)
                {
                    arr[index] = 0;
                    continue;
                }
                // arr[index] = i;
                used[i] = true;

                generatePermutation(count, arr, used, n, k, index + 1, trustTable, length, i + 1);
                used[i] = false; // Quay lui (backtrack)
            }
        }
    }
}

// Hàm này thực thi lặp hết các function
// check xem fuction đã trong nhóm nào chưa ? Nếu chưa thì chạy hàm supportProcess để tạo nhóm cho nó.
void mainProcess(U32 trustTable)
{
    // newCode
    U32 n = 1 << size; // Số phần tử tối đa
    U32 k = size;      // Chập k của chỉnh hợp
    U32 len_bit = n;
    U32 length = 1;
    U32 arr_supp_per[k];
    bool *used;
    used = (bool *)malloc(n * sizeof(bool));
    for (U32 i = 0; i < n; i++)
    {
        used[i] = false;
    }

    U32 count_p = 0; // Đếm số chỉnh hợp

    //
    U32 count_func = 1;
    count_func <<= n;
    MAX_COUNT_FUNC = count_func;
    cout << count_func << "\n";
    arrStatusFunction = (bool *)malloc(count_func * sizeof(bool));
    for (U32 i = 0; i < count_func; i++)
    {
        arrStatusFunction[i] = true;
    }
    arrStatusFunction[trustTable] = false;
    U32 count_class = 0;
    generatePermutation(&count_p, arr_supp_per, used, n, k, 0, trustTable, &length);
    count_per = count_p;
    printf("Count_per: %d\n", count_per);
    printf("length class = %d\n", length);
    free(used);
}

int main()
{
    U32 func = 5;
    mainProcess(func);
    free(arrStatusFunction);
    return 0;
}