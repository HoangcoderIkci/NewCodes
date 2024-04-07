# lst = ['000100','000110','000111','001001','001011','001100','010100','010110','010111','011001','011011','011100','100100','100110','100111','101001','101011','101100','110001','110011','110100','111001','111011','111100']

# for elem in lst:
#     print("[",end="")
#     for el2 in range(len(elem)-1):
#         print(f"{elem[el2]}",end=',')
#     print(elem[-1], end='')
#     print("],",end="")
    
    
import sympy as sp

# Định nghĩa các biến
x1, x2, x3,x4,x5,x6 = sp.symbols('x1 x2 x3 x4 x5 x6')

# Định nghĩa hàm số
f = (x3 +x1*x2+x1*x2*x3) * (x4+x4*x6 +x4*x5*x6) + x3 + x1 + x1*x2 + x1*x2*x3


# Tính giá trị của hàm số tại x1=1, x2=2, x3=0
result = f.subs({x1: 0, x2: 0, x3: 0,x4:0,x5:0,x6:0})

print(result)
