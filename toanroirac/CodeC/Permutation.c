#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_SIZE 21000 // Giới hạn kích thước của mảng kết quả
#define U64 uint_fast64_t
#define U32 uint_fast32_t
#define U16 uint_fast16_t
#define U8 uint_fast8_t
#define loop(i, a, n) for (U32 i = a; i < n; i++)
#define loopBack(i, n, a) for (int i = n; i >= a; i--)
#define getBitIndex(x, idx) (((x) >> (idx)) & 1)     // get bit tại index
#define setBitIndex(x, idx) ((x) |= (1 << (idx)))    // set bit tại index = 1
#define clearBitIndex(x, idx) ((x) &= ~(1 << (idx))) // clear bit tại index = 0
#define SIZE 3
U32 count_per = 0;

U32 *arr_permutation_global;

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

void swap(U32 *a, U32 *b)
{
    U32 temp = *a;
    *a = *b;
    *b = temp;
}

void reverse(U32 arr[], U32 start, U32 end)
{
    while (start < end)
    {
        swap(&arr[start], &arr[end]);
        start++;
        end--;
    }
}

U32 nextPermutation(U32 arr[], U32 n)
{
    int i = n - 2;
    while (i >= 0 && arr[i] >= arr[i + 1])
    {
        i--;
    }

    if (i < 0)
    {
        return 0;
    }

    int j = n - 1;
    while (arr[j] <= arr[i])
    {
        j--;
    }

    swap(&arr[i], &arr[j]);
    reverse(arr, i + 1, n - 1);
    return 1;
}

// tìm và insearch vào vị trí của mảng đã sáp xếp tăng dần.
void binarySearchInsert(U32 arr[], U32 *length, U32 target)
{
    int left = 0;
    int right = *length - 1;
    int mid;

    while (left <= right)
    {
        mid = left + (right - left) / 2;

        if (arr[mid] == target)
        {
            return; // Tìm thấy target tại vị trí mid
        }
        else if (arr[mid] < target)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    // Chèn target vào vị trí thích hợp
    for (int i = *length; i > left; i--)
    {
        arr[i] = arr[i - 1];
    }
    arr[left] = target;
    (*length)++;
    // if (*length >= 3999)
    // {
    //     printf("length %d\n", *length);
    // }
    // return left; // Trả về vị trí chèn mới
}
// Chỉ tìm xem target có trong mảng không ? -1 là chưa có , mid là vị trí thấy
int binarySearch(U32 arr[], U32 len_arr, U32 target)
{
    int left = 0;
    int right = len_arr - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
        {
            return mid; // Tìm thấy target tại vị trí mid
        }
        else if (arr[mid] < target)
        {
            left = mid + 1; // Chuyển sang nửa bên phải của mảng
        }
        else
        {
            right = mid - 1; // Chuyển sang nửa bên trái của mảng
        }
    }

    return -1; // Không tìm thấy target trong mảng
}

void createArrayPermutation()
{
    U32 permutation[SIZE]; // Mảng hoán vị ban đầu
    loop(i, 0, SIZE)
        permutation[i] = i;
    U32 new_per, new_val, sz = (1 << SIZE);

    // Khởi tạo bảng permutation tương ứng với permution trên
    do
    {
        new_per = 0;
        loop(val, 0, sz)
        {
            new_val = 0;
            loop(idx, 0, SIZE)
            {
                new_val <<= 1;
                new_val |= getBitIndex(val, SIZE - 1 - permutation[idx]);
            }
            new_per |= new_val << (SIZE * val);
        }

        arr_permutation_global[count_per++] = new_per;
        // printf("new permutation = %d\n", new_per);
    } while (nextPermutation(permutation, SIZE));
}

void process()
{
    U32 **arrRes;
    arrRes = (U32 **)malloc(500 * sizeof(U32 *));
    for (int i = 0; i < 500; i++)
    {
        arrRes[i] = (U32 *)malloc(4000 * sizeof(U32));
    }
    U32 *arrLength = (U32 *)malloc(200 * sizeof(U32));

    U32 num_func = (1 << (1 << SIZE));
    U32 current_per, sz = (1 << SIZE), alpha, new_trustable;
    U8 flag;
    U32 count_class = 0;
    U32 length = 0;
    U32 c = 0;
    loop(func, 0, num_func)
    {
        flag = 1;
        // check function tồn tại chưa
        loop(idx, 0, count_class)
        {
            if (binarySearch(arrRes[idx], arrLength[idx], func) != -1)
            {
                flag = 0;
                break;
            }
        }
        if (flag)
        {
            length = 1;
            arrRes[count_class][0] = func;
            loop(idx, 0, count_per)
            {
                current_per = arr_permutation_global[idx];
                new_trustable = 0;
                loop(idx2, 0, sz)
                {
                    alpha = current_per & ((1 << SIZE) - 1);
                    if (getBitIndex(func, alpha))
                    {
                        setBitIndex(new_trustable, idx2);
                    }
                    current_per >>= SIZE;
                }
                if (new_trustable != func)
                {
                    printf("new trustable = %d \n", new_trustable);
                    binarySearchInsert(arrRes[count_class], &length, new_trustable);
                }
            }
            arrLength[count_class] = length; // lưu số lượng phần tử trong class
            c += length;
            count_class++;
            if (c >= num_func)
            {
                printf("\n");
            }
            printf("c = %d\n", c);
        }
    }

    printf("%d\n", c);
    // in ket qua tung nhom
    loop(id, 0, count_class)
    {
        printf("================================================================\n");
        printf("class %d : length %d\n", id, arrLength[id]);
        loop(j, 0, arrLength[id])
        {
            printTypeBit(arrRes[id][j], sz);
        }
        printf("================================================================\n\n\n");
    }

    for (int i = 0; i < 500; i++)
    {
        free(arrRes[i]); // Giải phóng từng hàng
    }
    free(arrRes); // Giải phóng mảng chính
    free(arrLength);
}
int main()
{
    int sz = SIZE;
    arr_permutation_global = (U32 *)malloc(sz * sizeof(U32));
    createArrayPermutation();
    process();
    free(arr_permutation_global);
    return 0;
}
