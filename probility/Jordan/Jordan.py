from sympy import Matrix
import sympy as np
from numpy import linalg as LA
# Khai báo ma trận của bạn
# Ví dụ: Ma trận A
A = Matrix([
  [1,1],[1,1]
])
# Tính các giá trị riêng và vector riêng của A
eigenvalues, eigenvectors = LA.eig(np.diag((1, 2, 3)))
eigenvalues = A.eigenvals()
eigenvectors = A.eigenvects()
for id in eigenvectors:
  print("\nCác vector riêng tương ứng:")
  print(id[-1])
  
print("Các giá trị riêng của ma trận A:")
print(eigenvalues)

# Tính dạng Jordan
P, J = A.jordan_form()
P_inv = P.inv()
C = P @ J @ P_inv
print("Ma trận P:")
print(P)
print("\nDạng Jordan J của ma trận:")
print(J)

