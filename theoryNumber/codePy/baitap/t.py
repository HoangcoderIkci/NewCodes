import math
import sympy as sp
from random import randint
from sympy.polys.domains import GF

def Phi(expression_F, expression_G, p):
    # Định nghĩa biến

    
    # Tạo hàm số từ các hệ số trong trường GF(p)
    #poly1 = sum(c * x**i for i, c in enumerate(coeffs1))
    #poly2 = sum(c * x**i for i, c in enumerate(coeffs2))
    
    # Chuyển đổi poly1 và poly2 thành Poly với miền là GF(p)
    poly1_GF = sp.Poly(expression_F, x, domain=GF(p))
    poly2_GF = sp.Poly(expression_G, x, domain=GF(p))
    
    # Nhân hai hàm số trong trường GF(p)
    product_GF = poly1_GF * poly2_GF
    temp = sp.Poly([2],x,domain = GF(p))
    temp = temp - product_GF
    res = poly1_GF * temp
    # Trả về kết quả dưới dạng Poly trong GF(p) hoặc một list hệ số
    return res
def MultiplyTwoPoly(expression_F, expression_G, p):
    # Định nghĩa biến

    
    # Tạo hàm số từ các hệ số trong trường GF(p)
    #poly1 = sum(c * x**i for i, c in enumerate(coeffs1))
    #poly2 = sum(c * x**i for i, c in enumerate(coeffs2))
    
    # Chuyển đổi poly1 và poly2 thành Poly với miền là GF(p)
    poly1_GF = sp.Poly(expression_F, x, domain=GF(p))
    poly2_GF = sp.Poly(expression_G, x, domain=GF(p))
    
    # Nhân hai hàm số trong trường GF(p)
    product_GF = poly1_GF * poly2_GF
    # Trả về kết quả dưới dạng Poly trong GF(p) hoặc một list hệ số
    return product_GF
def printfPoly(coeffs1,p):
    x = sp.symbols('x')
    poly1 = sum(c * x**i for i, c in enumerate(coeffs1))
    poly1_GF = sp.Poly(poly1, x, domain=GF(p))
    print(poly1_GF)
    
x = sp.symbols('x')    
mod = 3
# P = [1, 0, 2, 0, 0, 1, 0, 2, 0, 1]

# G = [2, 2, 0, 2, 1]

F_inv = -x**9 - x**7 + x**6 + x**4 + x**3 + x**2 + 1
#P = - x**3 + 1
#G_inv = -x**4 + x**3 + 1
H = x**7 + x**6 + x**4 - x**3 + 1
# Q_inv = - x**5 + x**4 + x**3 + x + 1
#Q = x**5 + x**4 + x**2 + x - 1
#G = -x**4 + x**3 + 1
#F = -x**9 - x**7 + x**6 + x**4 + x**3 + x**2 + 1
P = MultiplyTwoPoly(F_inv,H,mod)
print(P)
# temp = sp.poly(F_inv,x,domain = GF(mod)) - P
# print(temp)


# R = sp.poly(F,x,domain = GF(mod)) - P
# print(R)


# dividend = sp.Poly(F, x,domain = GF(mod))
# divisor = sp.Poly(G, x,domain = GF(mod))
# # # Thực hiện phép chia đa thức
# quotient, remainder = dividend.div(divisor)

# #In kết quả
# print("Kết quả phép chia:")
# print("Thương:", quotient)
# print("Dư:", remainder)