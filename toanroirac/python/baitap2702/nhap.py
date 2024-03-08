from itertools import combinations

n = 5  # Thay đổi giá trị của n tùy ý
k = 3  # Thay đổi giá trị của k tùy ý

# Tạo một danh sách từ 0 đến n - 1
nums = list(range(1,n))

# Sinh tất cả tổ hợp chập k từ các số từ 0 đến n - 1
all_combinations = list(combinations(nums, k))

# In ra tất cả các tổ hợp
# for combo in all_combinations:
#     print(combo)
for i in range(15):
    print("c",end="")