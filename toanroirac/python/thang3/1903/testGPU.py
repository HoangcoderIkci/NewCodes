from math import log2
import pyopencl as cl
import numpy as np
import time

glo_n = 30
glo_length = 1 << glo_n

# Khởi tạo môi trường và queue
ctx = cl.create_some_context()
queue = cl.CommandQueue(ctx)


# Mã kernel
kernel_code = r"""
// Hàm kernel mới để cộng hai ma trận
__kernel void matrix_add(const int N, __global const int* A, __global const int* B, __global int* C) {
    int row = get_global_id(0);
    int col = get_global_id(1);
    C[row * N + col] = A[row * N + col] + B[row * N + col];
}
__kernel void matrix_add_1xN(const int N, __global const int* A, __global const int* B, __global int* C) {
    int col = get_global_id(0);
   
        C[col] = A[col] + B[col];
}
__kernel void step2(const int full_len,const int half_len, __global int* res) {
    int idx2 = get_global_id(0);
    int idx3 = get_global_id(1);
    //printf("step2 %d %d",res[idx2 * full_len+idx3],res[idx2 * full_len+half_len+idx3]);
    res[idx2 * full_len+half_len+idx3] ^= res[idx2 * full_len+idx3]; 
}
"""

# Tạo chương trình và build kernel
program = cl.Program(ctx, kernel_code).build()

# Kích thước của ma trận vuông
N = glo_length

# Tạo dữ liệu mẫu cho ma trận A và B
# A = np.random.randint(30, size=(N)).astype(np.int32)  # Ma trận 1xN
# B = np.random.randint(30, size=(N)).astype(np.int32)  # Ma trận 1xN
str_temp = "0101001101101001"
table = [int(x) for x in str_temp]
table = [x&0b1 for x in range(glo_length)]
# Chuyển đổi danh sách thành mảng NumPy với kiểu int32
A = np.array(table, dtype=np.int32)
print(A)
# Tạo buffer cho ma trận A, B và C
A_buf = cl.Buffer(ctx, cl.mem_flags.READ_WRITE | cl.mem_flags.COPY_HOST_PTR, hostbuf=A)
# B_buf = cl.Buffer(ctx, cl.mem_flags.READ_ONLY | cl.mem_flags.COPY_HOST_PTR, hostbuf=B)
C_buf = cl.Buffer(ctx, cl.mem_flags.WRITE_ONLY, A.nbytes)  # Kích thước tương tự như A hoặc 



# Đọc kết quả từ buffer C
# C = np.empty_like(A)
# cl.enqueue_copy(queue, C, C_buf)
# queue.finish()

# Hiển thị thời gian thực thi và một phần của kết quả
# print("Thời gian thực thi trên GPU:", end_time_gpu - start_time_gpu)
# print("Một phần của kết quả:", C)  # Hiển thị 10 phần tử đầu tiên của kết quả
# result = [A[j]+B[j] for j in range(glo_length)]
# print(result)



def supportsFunction(idx1):
    if idx1 == glo_n:
        return
    half_len = 1 << idx1
    full_len = half_len << 1
    num_turns = glo_length // full_len
    # for idx2 in range(num_turns):
    #     for idx3 in range(half_len):
    #         lst_coefficients[idx2 * full_len+half_len+idx3] ^= lst_coefficients[idx2 * full_len+idx3] 
    #start_time_gpu = time.time()
    program.step2(queue, (num_turns,half_len), None, np.int32(full_len),np.int32(half_len), A_buf)
    queue.finish()
    supportsFunction(idx1+1)

def fastFindCoefficientsZhegalkin2():
    #res = [x for x in lst_coefficients]
    supportsFunction(0)

start_time_gpu = time.time()   
fastFindCoefficientsZhegalkin2()
end_time_gpu = time.time()
print("Thời gian thực thi trên GPU:", end_time_gpu - start_time_gpu)
C = np.empty_like(A)
cl.enqueue_copy(queue, C, A_buf)
    #end_time_gpu = time.time()
print(C)