
from itertools import product
for elem in range(1 << 4):
    b = bin(elem)[2:]
    b = [int(x) for x in b]
    b = ([0] * (4-len(b))) + b
    print(b)
n = 4  # Số lần lặp

# Tạo các tổ hợp của giá trị từ 0 đến 1 cho các biến
combinations = product(range(2), repeat=4)
for elem in combinations:
    print((elem[0]&elem[1])^elem[2]^elem[3],end=",")


