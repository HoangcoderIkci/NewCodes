# from itertools import product
# from sympy import symbols, Poly,sympify,collect
# from math import factorial
# n = 3
# def combination(n, k):
#     return factorial(n) // (factorial(k) * factorial(n - k))
# # Calculate the ranges for a0, a1, a2, and a3
# ranges = [list(range(combination(n, i) + 1)) for i in range(4)]
# print(list(ranges))
# # Generate all combinations of a0, a1, a2, and a3
# for lst_a in product(*ranges):
#     print(lst_a)


# from sympy import symbols, Poly, sympify

# # Định nghĩa biến
# a0, a1, a2, a3, d = symbols('a0 a1 a2 a3 d')

# # Tạo đa thức
# poly = Poly(-1.0*a0*d**3 + 1.5*a0*d**2 - 0.75*a0*d + 0.125*a0 + 
#             1.0*a1*d**3 - 0.5*a1*d**2 - 0.25*a1*d + 0.125*a1 - 
#             1.0*a2*d**3 - 0.5*a2*d**2 + 0.25*a2*d + 0.125*a2 + 
#             1.0*a3*d**3 + 1.5*a3*d**2 + 0.75*a3*d + 0.125*a3, 
#             a0, a1, a2, a3, d, domain='RR')

# # Chuyển đa thức về dạng biểu thức
# expr = sympify(poly.as_expr())

# # Nhóm các phần tử theo biến d
# grouped_expr = expr.collect(d)

# # Lấy hệ số ứng với từng bậc của d
# coefficients_dict = grouped_expr.as_coefficients_dict()

# # In ra các hệ số
# for power, coeff in coefficients_dict.items():
#     print(f"Hs {power}: {coeff}")


from sympy import symbols, Poly,collect
from math import factorial
from itertools import product
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.backends.backend_pdf import PdfPages


n = 3
d_value = 0.25
variables = symbols(f'a0:{n+1}')
variables += symbols('d'),  # Add a comma to make it a tuple
# print(variables)
d = variables[-1]
# Định nghĩa hàm số


def createF(lst_a):
    f = Poly(0,variables)
    for i in range(n+1):
        f+=Poly(lst_a[i],d) * ((1/2+d)**i) * ((1/2-d)**(n-i))
    return f
def calcValFunc(f):
    y = [f.subs(d, a) for a in lst_x]
    value_func = []
    for f_value in y:
        poly = Poly(f_value)
        coeffs = poly.coeffs()
        value_func.append(coeffs[0])
    return value_func
lst_a =[0,0,3,1]
# Tạo dữ liệu cho đồ thị
size = 1000
lst_x = np.arange(-size, size+1)
lst_x = [lst_x[i]/(size*2) for i in range(len(lst_x))]

f = createF(lst_a)
value_func_1 = calcValFunc(f)

lst_a = [0,2,0,1]
f = createF(lst_a)
value_func_2 = calcValFunc(f)
# print(value_func)
# Vẽ đồ thị
# plt.plot(x, value_func1)
# plt.xlabel('i')
# plt.ylabel('f(i)')
# plt.title('График вероятной функии f')
# plt.show()



# Vẽ đồ thị cho f_1
plt.plot(lst_x, value_func_1, label='f1')

# Vẽ đồ thị cho f_2
plt.plot(lst_x, value_func_2, label='f2')

plt.xlabel('i')
plt.ylabel('f(i)')
plt.title('Graph of Multiple Functions')
plt.legend()
plt.show()
# Lưu đồ thị vào file PDF
# with PdfPages('output_graph.pdf') as pdf:
#     pdf.savefig()
#     plt.close()

# print("success!!!")


