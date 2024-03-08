#include <stdio.h>
#include <stdint.h>
#define U64 uint_fast64_t
#define U32 uint_fast32_t
#define U16 uint_fast16_t
#define U8 uint_fast8_t
#define loop(i, a, n) for (U32 i = a; i < n; i++)
#define loopBack(i, n, a) for (int i = n; i >= a; i--)
#define getBitIndex(x, idx) (((x) >> (idx)) & 1)     // get bit tại index
#define setBitIndex(x, idx) ((x) |= (1 << (idx)))    // set bit tại index = 1
#define clearBitIndex(x, idx) ((x) &= ~(1 << (idx))) // clear bit tại index = 0

#define size 2
// đưa matrix về dạng chuẩn tắc
void changeMatrix(U32 matrix[], U8 row, U8 col)
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
    U8 temp_rank = rank;
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

int checkInverseMatrix(U32 matrix[], U8 row, U8 col)
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
        else
        {
            return 0;
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
    }
    // bước 2 đưa dạng đường chéo chứa 1
    return 1;
}
// ================================================================= Begin Code Supper =================================================================
// Begin hỗ trợ cho Supper
U32 getRow(U32 matrix, U8 num_r, U8 len_row)
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
U32 setRow(U32 matrix, U8 num_r, U8 len_row, U32 value)
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

U32 getBitsRow(U32 matrix, U8 num_r, U8 len_row)
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
void printfMatrix(U32 matrix, U8 row, U8 col)
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

int checkInverseMatrixSupper(U32 matrix, U8 row, U8 col)
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

U32 mulRơwWithMatrixSupper(U32 matrix, U32 newRow, U8 row, U8 col)
{
    U32 res = 0;
    loop(i, 0, col)
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
void printTypeBit(U32 bit, U8 len_bit)
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
U32 mulRơwWithMatrix(U32 matrix[], U32 newRow, U8 row, U8 col)
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
void binarySearchInsert(U32 arr[], U8 *length, U32 target)
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
    // return left; // Trả về vị trí chèn mới
}
// Chỉ tìm xem target có trong mảng không ? -1 là chưa có , mid là vị trí thấy
int binarySearch(U32 arr[], U8 len_arr, U32 target)
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

// hàm này giúp tạo từng nhóm với phần tử đại diện là trustTable
// Arr_res  :  lưu trữ các phần tử trong class
// length  :  lưu trữ số lượng phần tử trong class
// trustTable  :  Phần tử đại diện của class
void SupportProcess(U32 Arr_res[], U32 trustTable, U8 *length)
{
    // tạo mảng
    U32 alpha;
    U32 res;
    U8 flag, count = 0;
    U32 matrix[3];
    U8 c = 0;
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

// Hàm này thực thi lặp hết các function
// check xem fuction đã trong nhóm nào chưa ? Nếu chưa thì chạy hàm supportProcess để tạo nhóm cho nó.
void mainProcess()
{
    int count_func = (1 << (1 << 3));
    U32 c = 0;
    U8 flag;
    U32 arrRes[50][50];
    U32 arrLength[500];
    U8 *count_class = new U8;
    *count_class = 0;
    U8 *length = new U8;
    *length = 0;
    U32 func;
    // loop hết các function
    loop(temp, 0, count_func)
    {
        func = temp;
        flag = 1; // đặt cờ chưa tồn tại
        loop(idx, 1, *count_class + 1)
        {
            if (binarySearch(arrRes[idx], arrLength[idx], func) != -1) // ton tai và thoát loop
            {
                flag = 0;
                break;
            }
        }
        if (flag) // chưa tồn tại
        {
            *length = 1;
            ++(*count_class);
            arrRes[*count_class][0] = func;                     // gán phần tử đại diện của class
            SupportProcess(arrRes[*count_class], func, length); // tạo nhóm cho phần tử đại diện của class
            arrLength[*count_class] = *length;                  // lưu số lượng phần tử trong class
            // loop(tt, 0, *length)
            //     printf("%d  ", arrRes[*count_class][tt]);
            // printf("\n");
            // printf("length %d  ", *length);
            c += *length; // biến c == số lượng tổng fuction thì là program đã đúng (count_func)
        }
        // printf("temp = %d  ", temp);
    }
    printf("%d\n", c);
    // in ket qua tung nhom
    loop(id, 1, *count_class + 1)
    {
        printf("================================================================\n");
        printf("class %d : length %d\n", id, arrLength[id]);
        loop(j, 0, arrLength[id])
        {
            printTypeBit(arrRes[id][j], 8);
        }
        printf("================================================================\n\n\n");
    }
    delete count_class;
}
int main()
{
    // U32 matrix[] = {0b010, 0b110, 0b111};
    // U32 matrix = 0b011100101;
    // U32 newRow = 0b100;
    // printfMatrix(matrix, 3, 3);
    // loop(elem, 0, 8)
    // {
    //     printf("%i : %d       ", elem, mulRơwWithMatrix(matrix, elem, 3, 3));
    // }
    // printf("\n");
    // int res = checkInverseMatrixSupper(matrix, 3, 3);
    // printf("res = %d\n", res);
    // U32 trustable = 0b11100101;
    // U32 arrRes[120];
    // U8 length = 1;
    mainProcess();
    return 0;
}