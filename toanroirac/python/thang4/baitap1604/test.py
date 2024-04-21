from itertools import product
for elem in range(1 << 4):
    b = bin(elem)[2:]
    b = [int(x) for x in b]
    b = ([0] * (4-len(b))) + b
    print(b)
n = 3  # Số lần lặp

# Tạo các tổ hợp của giá trị từ 0 đến 1 cho các biến
combinations = product(range(2), repeat=n)
print(list(combinations))

print(hex(6277101735386680763495507056286727952657427581105975853055))