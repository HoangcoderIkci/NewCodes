import numpy as np
def kronProduct(A,B):
    res = []
    for i in range(A.shape[0]):
        temp = []
        for j in range(A.shape[1]):
            temp.append(B * A[i,j])
        res.append(temp)
    return res
A = np.array([[1, 2], [3, 4]])
B = np.array([[0, 5], [6, 7]])

result = kronProduct(A, B)

print("Result of Kronecker product:")
for i in range(2):
        # for j in range(result.shape[1]):
        print(result[i])
        

