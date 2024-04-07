import multiprocessing
from time import time
# Hàm tính tổng của một phần của mảng
def calculate_sum(arr, start, end, result_queue):
    partial_sum = sum(arr[start:end])
    result_queue.put(partial_sum)

if __name__ == "__main__":
    # Dữ liệu mảng số nguyên
    data = list(range(1, 10000001))
    
    # Số lượng tiến trình con
    num_processes = 10
    
    # Chia mảng thành các phần cho từng tiến trình
    chunk_size = len(data) // num_processes
    start_indices = [i * chunk_size for i in range(num_processes)]
    end_indices = [(i + 1) * chunk_size if i < num_processes - 1 else len(data) for i in range(num_processes)]
    
    # Queue để lưu trữ kết quả từ các tiến trình con
    result_queue = multiprocessing.Queue()
    
    # Tạo và khởi động các tiến trình con
    processes = []
    begin = time()
   

    for i in range(num_processes):
        p = multiprocessing.Process(target=calculate_sum, args=(data, start_indices[i], end_indices[i], result_queue))
        processes.append(p)
        p.start()
    
    # Đợi cho tất cả các tiến trình con hoàn thành
    for p in processes:
        p.join()
    end = time()
    print("Total time = ", end - begin)
    # Tổng của tất cả các phần
    total_sum = 0
    while not result_queue.empty():
        total_sum += result_queue.get()
    print("Tổng của mảng là:", total_sum)
    begin = time()
    tt = 0
    for i in range(len(data)):
        tt+= data[i]
    end = time()
    print("Total time = ", end - begin)