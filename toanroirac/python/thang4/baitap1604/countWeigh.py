from sympy import symbols
from sympy import Add
from itertools import product
# Khai báo các biến
# Số lượng biến
n = 4

# Tạo n biến dạng trên
X = symbols('x0:%d' % (n+1))

# Tạo hàm từ dạng đa thức Zhegalkin
f = X[1]*X[2]+X[1]*X[3]+X[2]*X[3]
f = X[1]+X[2]+X[3]
# f_temp = f.subs({X[1]:0})
def countBit(trusTable):
    return trusTable.count(1)
# Tạo bảng giá trị của hàm
def createTable(f,A):
    numLoop = len(A)
    trusTable = []
    combinations = product(range(2), repeat=numLoop)
    for loop in combinations:
        values = {X[A[i]]: loop[i] for i in range(numLoop)}
        #print(values)
        trusTable.append(f.subs(values)&0b1)
    return trusTable
def mainProcess(f,A):
    res = [countBit(createTable(f,list(range(1,n))))]
    arrTemp = [[1],[2],[3],[1,2],[1,3],[2,3],[1,2,3]]
    for row in arrTemp:
        #g= # Sao chép hàm số f để tạo hàm g
        g = Add(*f.args)
        for elem in row:
            g=g.subs({X[elem]:A[elem]})
        A_temp = [x for x in [1,2,3] if x not in row]
        trTable = createTable(g,A_temp)
       # print("trustTable:",trTable)
        numBit = countBit(trTable)
        res.append(numBit)
    print(res)
    return res
    
# print(type(f))
# # In bảng giá trị
# trusTable = createTable(f_temp)
# print(trusTable)
# numBit = countBit(trusTable)
# print(numBit)

res = []
for col in range(8):
    b = bin(col)[2:]
    A = [int(x) for x in b]
    A = ([0]*(4-len(A))) + A
    
    #print(A)
    #A = [-1,0,0,1]         
                            
    t = mainProcess(f,A)
    res.append(t)
# #    
for i in range(len(res)):
    for j in range(len(res[0])):
        print(res[j][i],end=",")
    print()
