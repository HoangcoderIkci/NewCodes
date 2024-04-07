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
#define size 4
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
// ================================================================= Begin Code Supper =================================================================
// Begin hỗ trợ cho Supper
U32 getRow(U32 matrix, U32 num_r, U32 len_row)
{
    matrix >>= num_r * len_row;
    U32 res = 0;
    loop(i, 0, len_row)
    {
        if (matrix & 0b1)
            setBitIndex(res, i);
        matrix >>= 1;
    }
    return res;
}
U32 setRow(U32 matrix, U32 num_r, U32 len_row, U32 value)
{
    loop(i, 0, len_row)
    {
        if (value & 0b1)
        {
            setBitIndex(matrix, num_r * len_row + i);
        }
        else
            clearBitIndex(matrix, num_r * len_row + i);
        value >>= 1;
    }
    return matrix;
}

U32 getBitsRow(U32 matrix, U32 num_r, U32 len_row)
{
    U32 res = 0;
    U32 val = 1 << (num_r * len_row);
    loop(i, 0, len_row)
    {
        res |= (val & matrix);
        val <<= 1;
    }
    return res;
}
void printfMatrix(U32 matrix, U32 row, U32 col)
{
    loop(i, 0, row)
    {
        loop(k, 0, col)
        {
            printf("%d ", getBitIndex(matrix, i * col + k));
        }
        printf("\n");
    }
}
// end hàm hỗ trợ cho Supper

int checkInverseMatrixSupper(U32 matrix, U32 row, U32 col)
{
    if (row != col)
        return 0;
    // printfMatrix(matrix, row, col);
    U32 rank = 0, idx = 0, temp_to_swap;
    U32 arrIndexBasic = 0;
    // bước 1 đưa dạng bậc thang
    loop(j, 0, col)
    {
        // begin tìm vị trí đầu tiên khác 0
        idx = 100;
        loop(i, rank, row)
        {
            if (getBitIndex(matrix, i * col + j))
            {
                idx = i;
                break;
            }
        }
        // end tìm vị trí đầu tiên khác 0
        if (idx != 100) // trường hợp tìm được vị trí có phần tử khác 0
        {
            // đảo chỗ 2 hàng
            temp_to_swap = getRow(matrix, rank, col);                     // matrix[rank];
            matrix = setRow(matrix, rank, col, getRow(matrix, idx, col)); // matrix[rank] = matrix[idx];
            matrix = setRow(matrix, idx, col, temp_to_swap);              // matrix[idx] = temp_to_swap;
            // printfMatrix(matrix, row, col);
            //   biến các hàng bên dưới về 0
            loop(i, rank + 1, row)
            {
                if (getBitIndex(matrix, i * col + j))
                {
                    // matrix[i] ^= matrix[rank];
                    matrix ^= getBitsRow(matrix, rank, col) << ((i - rank) * col);
                }
            }
            setBitIndex(arrIndexBasic, col - 1 - j); // đưa vào trong basic
            rank++;                                  // tăng rank
        }
        else
        {
            return 0;
        }
        // printf("rank = %d \n", rank);
        //  printfMatrix(matrix, row, col);
    }
    // bước 2 đưa dạng đường chéo chứa 1
    return 1;
}

U32 mulRơwWithMatrixSupper(U32 matrix, U32 newRow, U32 row, U32 col)
{
    U32 res = 0;
    loopBack(i, row - 1, 0)
    {
        if (newRow & 0b1)
        {
            res ^= getRow(matrix, i, col);
        }
        newRow >>= 1;
    }
    return res;
}
// ================================================================= End Code Supper =================================================================

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

// U32 Arrangement_global[MAX_SIZE][size];
U32 *Arrangement_global_supper; // mảng lưu trữ tất cả Ma trận nghịch đảo // Mỗi ma trận ứng với 1 biến ví dụ : 0b 100010001 sẽ là ma trận E
U32 **Arrangement_global;
// hàm tạo chỉnh hợp k,n

void generatePermutation(U32 *count, U32 arr[], bool used[], U32 n, U32 k, U32 index, U32 idx_current = 1)
{
    if (index == k)
    {
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
            // chắc chắn nghịch đảo rồi

            loop(idx, 0, size)
            {
                // printf("%d  ", arr[idx]);
                Arrangement_global[temp_count][idx] = arrTemp[idx];
            }
            // printf("\n");
            // printf("count: %d\n", temp_count);
            temp_count++;
            // printf("count: %d\n", temp_count);
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

                generatePermutation(count, arr, used, n, k, index + 1, i + 1);
                used[i] = false; // Quay lui (backtrack)
            }
        }
    }
}

// hàm này giúp tạo từng nhóm với phần tử đại diện là trustTable
// Arr_res  :  lưu trữ các phần tử trong class
// length  :  lưu trữ số lượng phần tử trong class
// trustTable  :  Phần tử đại diện của class
void SupportProcess(U32 Arr_res[], U32 trustTable, U32 *length)
{
    // tạo mảng
    U32 alpha;
    U32 res;
    U32 flag, count = 0;
    U32 matrix[3];
    U32 c = 0;
    // Arr_res[0] = trustTable;
    loop(i, 0, 8)
    {
        loop(j, 0, 8)
        {
            if (i == j)
                continue;
            loop(k, 0, 8)
            {
                if (k == i || k == j)
                    continue;
                res = 0;
                matrix[0] = i;
                matrix[1] = j;
                matrix[2] = k;
                if (checkInverseMatrix(matrix, 3, 3))
                {
                    c++;
                    matrix[0] = i; // gán lại vì khi cho vào hàm check bị biến đổi mất tiêu rồi -_-
                    matrix[1] = j;
                    matrix[2] = k;
                    // loop(ii, 0, 3)
                    //     printTypeBit(matrix[ii], 3);
                    loop(t, 0, 8)
                    {
                        alpha = mulRơwWithMatrix(matrix, t, 3, 3);
                        // printf("t = %d  ", t);
                        // printTypeBit(alpha, 3);
                        flag = getBitIndex(trustTable, alpha);
                        if (flag)
                            res ^= (1 << t);
                    }
                    if (res != trustTable)
                    {
                        ++count;
                        // Arr_res[num_class++] = res;
                        binarySearchInsert(Arr_res, length, res);
                    }
                }
            }
        }
    }
    // printf("%d %d \n", count, c);
    // printf("length %d \n", *length);
}

void SupportProcess2(U32 trustTable, U32 *length)
{
    // tạo mảng
    U32 alpha;
    U32 res;
    U32 flag, count = 0;
    // U32 matrix[size];
    U32 c = 0;
    // Arr_res[0] = trustTable;
    // lặp tất cả các ma trận nghịch đảo
    loop(i_col, 0, (1 << size))
    {
        loop(i, 0, count_per)
        {
            // lấy matrix

            res = 0;
            loop(t, 0, (1 << size)) // Biến đổi trustTable
            {
                alpha = mulRơwWithMatrix(Arrangement_global[i], t, size, size);
                alpha ^= i_col;
                flag = getBitIndex(trustTable, alpha);
                if (flag)
                    res ^= (((U32)1) << t);
            }
            if (res >= MAX_COUNT_FUNC)
            {
                printf("Error \n");
            }
            if (arrStatusFunction[res] == true)
            {
                (*length)++;
                arrStatusFunction[res] = false;
            }
        }
    }
    // printf("%d %d \n", count, c);
    // printf("length %d \n", *length);
}

// newfunction
void SupportProcessNew(U32 trustTable, U32 *length)
{
    // tạo mảng
    U32 alpha;
    U32 res;
    U32 flag, count = 0;
    // U32 matrix[size];
    U32 c = 0;
    // Arr_res[0] = trustTable;
    // lặp tất cả các ma trận nghịch đảo
    U32 minDistance = 1000000;
    loop(i_col, 0, (1 << size))
    {
        loop(i, 0, count_per)
        {
            // lấy matrix

            res = 0;
            loop(t, 0, (1 << size)) // Biến đổi trustTable
            {
                alpha = mulRơwWithMatrix(Arrangement_global[i], t, size, size);
                alpha ^= i_col;
                res += alpha & 1;
            }
            if (res >= MAX_COUNT_FUNC)
            {
                printf("Error \n");
            }
            if (arrStatusFunction[res] == true)
            {
                (*length)++;
                arrStatusFunction[res] = false;
            }
        }
    }
    // printf("%d %d \n", count, c);
    // printf("length %d \n", *length);
}
// end newfunction

// Hàm này thực thi lặp hết các function
// check xem fuction đã trong nhóm nào chưa ? Nếu chưa thì chạy hàm supportProcess để tạo nhóm cho nó.
void mainProcess()
{
    // newCode
    U32 n = 1 << size; // Số phần tử tối đa
    U32 k = size;      // Chập k của chỉnh hợp
    U32 len_bit = n;
    U32 arr_supp_per[k];
    bool *used;
    used = (bool *)malloc(n * sizeof(bool));
    for (U32 i = 0; i < n; i++)
    {
        used[i] = false;
    }

    U32 count_p = 0; // Đếm số chỉnh hợp
    generatePermutation(&count_p, arr_supp_per, used, n, k, 0);
    count_per = count_p;
    printf("Count_per: %d\n", count_per);
    //
    U32 count_func = 1;
    count_func <<= n;
    MAX_COUNT_FUNC = count_func;
    cout << count_func << "\n";
    U32 c = 0;
    arrStatusFunction = (bool *)malloc(count_func * sizeof(bool));
    for (U32 i = 0; i < count_func; i++)
    {
        arrStatusFunction[i] = true;
    }
    U32 flag;
    U32 *arrRes;
    // arrRes = (U32 *)malloc(MAX_COUNT_CLASS * sizeof(U32));

    // U32 *arrLength = new U32[MAX_COUNT_CLASS];
    // U32 *count_class = new U32;
    U32 count_class = 0;
    U32 length = 0;
    U32 func;
    // loop hết các function

    loop(temp, 0, count_func)
    {
        func = temp;
        flag = 1; // đặt cờ chưa tồn tại
        flag = arrStatusFunction[func];
        // printf("function = %d\n", func);
        if (flag) // chưa tồn tại
        {
            arrStatusFunction[func] = false; // đã tồn tại
            length = 1;
            //++(*count_class);
            count_class++;
            // arrRes[count_class] = func;     // gán phần tử đại diện của class
            SupportProcess2(func, &length); // tạo nhóm cho phần tử đại diện của class
            printf("coutclass = %d\n", count_class);
            printTypeBit(func, len_bit);
            printf("length = %d\n", length);
            // if (count_class == 45)
            //     printf("%d\n", arrLength[count_class]);
            // printf("length %d  \n", length);
            // loop(tt, 0, length)
            //     printf("%d  ", arrRes[count_class][tt]);
            // printf("\n");
            c += length; // biến c == số lượng tổng fuction thì là program đã đúng (count_func)
            if (c >= count_func)
            {
                printf("\n");
            }
            printf("c = %d\n", c);
        }
        // printf("temp = %d  ", temp);
    }

    printf("%d\n", c);
    free(used);
}

void tim_class_func(U32 trustTable)
{
    U32 length = 1;
    // tạo mảng các function
    // newCode
    U32 n = 1 << size; // Số phần tử tối đa
    U32 k = size;      // Chập k của chỉnh hợp
    U32 len_bit = n;
    U32 arr_supp_per[k];
    bool *used;
    used = (bool *)malloc(n * sizeof(bool));
    for (U32 i = 0; i < n; i++)
    {
        used[i] = false;
    }

    U32 count_p = 0; // Đếm số chỉnh hợp
    generatePermutation(&count_p, arr_supp_per, used, n, k, 0);
    count_per = count_p;
    printf("Count_per: %d\n", count_per);
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

    //
    // tạo mảng các hoán vị
    SupportProcess2(trustTable, &length);

    printf("số lượng function của class là = %d\n", length);
    free(used);
}

int main()
{
    // Arrangement_global_supper = (U32 *)malloc(MAX_SIZE * sizeof(U32));
    Arrangement_global = (U32 **)malloc(MAX_SIZE * sizeof(U32 *));
    for (int i = 0; i < MAX_SIZE; i++)
    {
        Arrangement_global[i] = (U32 *)malloc(size * sizeof(U32));
    }
    mainProcess();
    U32 func = 100;
    tim_class_func(func);
    // free(Arrangement_global_supper); // Giải phóng mảng chính
    free(arrStatusFunction);
    for (int i = 0; i < MAX_SIZE; i++)
    {
        free(Arrangement_global[i]);
    }
    free(Arrangement_global);
    return 0;
}