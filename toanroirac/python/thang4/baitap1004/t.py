from sympy import Matrix
import sympy as np
from numpy import linalg as LA
A = Matrix([
  [4,3],[3,4]
])


# Tính dạng Jordan
C, J = A.jordan_form()
P_inv = C.inv()
D = C @ J @ P_inv
print(J)
# print(P_inv)