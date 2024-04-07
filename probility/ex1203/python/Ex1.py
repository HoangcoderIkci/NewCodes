from sympy import Matrix
import sympy as np

def createP(n : int):
    P = [[0]*(n+1) for i in range(n+1)]
    #print(P)
    P[0][1] = 1
    for i in range(1,n):
        P[i][i] = 2 * i * (1 - i/n) / n
        P[i][i+1] = (1 - i/n) **2
        P[i][i-1] = (i/n) **2
    P[n][n-1] = 1
    return P

P = createP(3)

A = Matrix(P)
# Tính các giá trị riêng và vector riêng của A
#eigenvalues, eigenvectors = LA.eig(np.diag((1, 2, 3)))
eigenvalues = A.eigenvals()
print("Các giá trị riêng của ma trận A:")
print(eigenvalues)