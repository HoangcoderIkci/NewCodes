# import math
# max_length = 100000
# sum = 0
# def calculate_mean(L):
#     sum = 0
#     for i in range(1,max_length):
#         sum += ((1 - 2 **(-L))**(i-1))*math.log2(i)
#     sum *= 2 **(-L)
#     return sum
# def calculate_variance(L):
#     #b1 mean((log2 A.(RN))^2)
#     mean_square = 0
#     for i in range(1,max_length):
#         mean_square += ((1 - 2 **(-L))**(i-1))*(math.log2(i)**2)
#     mean_square *= 2 **(-L)
    
#     return mean_square - calculate_mean(L) **2
# if __name__ == "__main__":
#     for L in range(1,17):
#         temp = calculate_mean(L)
#         print(f"L = {L},temp = {temp}")
#        # print(temp)
       
       
       
# from sympy import symbols, Eq, factorial, simplify,binomial

# # Khai báo các biến
# n, k = symbols('n k')

# # Biểu thức ban đầu
# expr1 = binomial(n, k) * binomial(n, n - k) / binomial(2*n, n)

# # Biểu thức đã rút gọn
# expr2 = binomial(n, k) * binomial(n, n - k)  * 2 *k/n*(1-k/n) / binomial(2*n, n) + binomial(n, k-1) * binomial(n, n - k+1)* ((1-(k-1)/n) **2) / binomial(2*n, n) + binomial(n, k+1) * binomial(n, n - k-1) * ((k+1)/n)**2 / binomial(2*n, n)
# # expr1 = factorial(2*n) *2/(2* (factorial(n) * factorial(n)))
# # Kiểm tra xem hai biểu thức có bằng nhau hay không
# equation = Eq(expr1, expr2)
# is_equal = simplify(equation)
# print(simplify(expr1))
# if is_equal == True:
#     print("Hai biểu thức bằng nhau.")
# else:
#     print("Hai biểu thức không bằng nhau.")



from sympy import Matrix,sqrt
# Khai báo ma trận của bạn
# Ví dụ: Ma trận A
A = Matrix([
  [1/sqrt(2),1/sqrt(2)],[1/sqrt(2),-1/sqrt(2)]
])

# Tính dạng Jordan
P, J = A.jordan_form()
P_inv = P.inv()
# C = P @ J @ P_inv
print("C1:")
print(P)
print("\nC^-1:")
print(P_inv)
print("J:")
print(J)
# for row in P:
#     print(row)