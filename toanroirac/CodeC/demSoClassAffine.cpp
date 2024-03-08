#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <iostream>
#define U32 uint64_t
#define U16 uint_fast16_t
#define U8 uint_fast8_t
#define loop(i, a, n) for (U32 i = a; i < n; i++)
#define loopBack(i, n, a) for (int i = n; i >= a; i--)
#define getBitIndex(x, idx) (((x) >> (idx)) & 1)     // get bit tại index
#define setBitIndex(x, idx) ((x) |= (1 << (idx)))    // set bit tại index = 1
#define clearBitIndex(x, idx) ((x) &= ~(1 << (idx))) // clear bit tại index = 0
#define size 5
U32 gioihan = 0b11111;
#define registerBit(x) ((x << 1 | x >> (size - 1)) & gioihan)

using namespace std;
void process()
{
    U32 so_luong_bien = (1llu) << size;
    U32 static_variables = 0;
    // loop(i, 0, so_luong_bien)
    // {
    //     static_variables[i] = true;
    // }
    U32 res = 0;
    loop(i, 0, size)
    {
        res = 0;
        loop(t, 0, so_luong_bien)
        {
            if (getBitIndex(static_variables, t) == 0)
            {
                // static_variables[t] = false;
                setBitIndex(static_variables, t);
                U32 elem = t;
                do
                {
                    loop(k, 0, i)
                        elem = registerBit(elem);
                    setBitIndex(static_variables, elem);
                    // static_variables[elem] = false;
                } while (elem != t);
                res++;
            }
        }
        static_variables = 0;
        // loop(j, 0, so_luong_bien)
        // {
        //     static_variables[j] = true;
        // }
        // phục hồi lại bảng trên
        printf("tại i = %d ; số orbit tại dịch i bit = %d\n", i, res);
    }
    // printf("res = %d\n", res);
}
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
long double res_count_class = 0;
void generatePermutation(U32 *count, U32 arr[], bool used[], U32 n, U32 k, U32 index, U32 idx_current = 1)
{
    if (index == k)
    {
        // U32 temp_count = *count;
        U32 num_ori = 0;
        U32 arrTemp[size];
        U32 so_luong_bien = (1llu) << size;
        U32 static_variables = 0;
        // chắc chắn nghịch đảo rồi
        loop(idx, 0, size)
        {
            // Arrangement_global[count][idx] = arr[idx];
            arrTemp[idx] = arr[idx];
        }
        // printf("\n");
        //  giờ cần thêm cả các hoán vị của nó vào nữa
        U32 elem;
        do
        {
            // Biến đổi trustable
            loop(i_col, 0, so_luong_bien)
            {
                // elem = 0;
                static_variables = 0;
                num_ori = 0;
                loop(t, 0, so_luong_bien) // Biến đổi trustTable
                {
                    if (getBitIndex(static_variables, t) == 0)
                    {
                        num_ori++;
                        setBitIndex(static_variables, t);
                        elem = t;
                        do
                        {
                            elem = mulRơwWithMatrix(arrTemp, elem, size, size);
                            elem ^= i_col;
                            // elem = registerBit(elem);
                            setBitIndex(static_variables, elem);
                            // static_variables[elem] = false;
                        } while (elem != t);
                    }
                }
                // temp_count += (1llu) << num_ori;
                res_count_class += (((1llu) << num_ori) * 1.f) / 319979520;
            }
        } while (nextPermutation(arrTemp, k));
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

                generatePermutation(count, arr, used, n, k, index + 1, i + 1);
                used[i] = false; // Quay lui (backtrack)
            }
        }
    }
}

int main()
{
    U32 n = 1 << size; // Số phần tử tối đa
    U32 k = size;      // Chập k của chỉnh hợp
    U32 arr_supp_per[k];
    bool *used;
    used = (bool *)malloc(n * sizeof(bool));
    for (U32 i = 0; i < n; i++)
    {
        used[i] = false;
    }
    U32 count_p = 0; // Đếm số chỉnh hợp
    generatePermutation(&count_p, arr_supp_per, used, n, k, 0);
    // printf("count: %d\n", count_p);
    // printf("num class = ");
    // U32 count_per = 319979520;
    // cout << count_p / count_per << endl;
    free(used);
    return 0;
}