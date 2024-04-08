import threading
from queue import Queue
from time import time

# Hàm tính tổng của một phần của mảng
def calculate_sum(arr, start, end, result_queue):
    partial_sum = sum(arr[start:end])
    result_queue.put(partial_sum)

if __name__ == "__main__":
    # Dữ liệu mảng số nguyên
    data = list(range(1, 100000001))
    
    # Số lượng threads
    num_threads = 10
    
    # Chia mảng thành các phần cho từng thread
    chunk_size = len(data) // num_threads
    start_indices = [i * chunk_size for i in range(num_threads)]
    end_indices = [(i + 1) * chunk_size if i < num_threads - 1 else len(data) for i in range(num_threads)]
    
    # Queue để lưu trữ kết quả từ các thread
    result_queue = Queue()
    
    # Tạo và khởi động các thread
    threads = []
    begin = time()
    
    for i in range(num_threads):
        t = threading.Thread(target=calculate_sum, args=(data, start_indices[i], end_indices[i], result_queue))
        threads.append(t)
        t.start()
    
    # Đợi cho tất cả các thread hoàn thành
    for t in threads:
        t.join()
    
    end = time()
    print("Total time with threading: ", end - begin)
    
    # Tổng của tất cả các phần
    total_sum = 0
    while not result_queue.empty():
        total_sum += result_queue.get()
        
    print("Tổng của mảng là:", total_sum)
    
    # Đo thời gian xử lý tuần tự để so sánh
    begin = time()
    total_sum_sequential = sum(data)
    end = time()
    
    print("Tổng của mảng (xử lý tuần tự):", total_sum_sequential)
    print("Total time with sequential processing: ", end - begin)
