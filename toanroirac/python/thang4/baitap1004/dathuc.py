from sympy import symbols, Poly,collect,integrate, Abs
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
size = 100
lst_x = np.arange(-size, size+1)
lst_x = [lst_x[i]/(size*2) for i in range(len(lst_x))]



def combination(n, k):
    return factorial(n) // (factorial(k) * factorial(n - k))
# Số lượng biến từ 1 đến 10


def createFTemplate():
    f = Poly(0,variables)
    for i in range(n+1):
        f+=Poly(variables[i],variables) * ((1/2+variables[-1])**i) * ((1/2-variables[-1])**(n-i))
    return f

def createF(lst_a):
    f = Poly(0,d)
    for i in range(n+1):
        f+=Poly(lst_a[i],d) * ((1/2+d)**i) * ((1/2-d)**(n-i))
    return f
def createFBasedOnProbability(lst_a):
    f = Poly(0,variables)
    for i in range(n+1):
        f+=Poly(lst_a[i],d) * (d**i) * ((1-d)**(n-i))
    return f
# Tạo danh sách các biến x từ x1 đến xn

def findKlevelingfunction():
    ranges = [range(combination(n,i)+1) for i in range(n+1)]
    for lst_a in product(*ranges):
        f = createF(lst_a)
        # Get the coefficients for degree 0, 1, and 2
        f_expr = f.as_expr()
        # Get the coefficients for degree 0, 1, and 2
        #coeff_0 = f_expr.coeff(d, 0)
        coeff_1 = f_expr.coeff(d, 1)
        if coeff_1 == 0:
            print(f)
            print(lst_a)    
        # coeff_2 = f_expr.coeff(d, 2)
        # print(coeff_0, coeff_1, coeff_2)
            # tính giá trị denta
            f_value = f.subs(variables[-1], d_value)
            poly = Poly(f_value)
                    # Get the coefficients
            coeffs = poly.coeffs()
            new_del = abs(coeffs[0]-0.5)
            print(f"new_del= {new_del}")
        
def findMindelta():
    min_delta = d_value
    dict_a_min = {}
    ranges = [range(combination(n,i)+1) for i in range(n+1)]
    for lst_a in product(*ranges):
        f = createF(lst_a)
        # Get the coefficients for degree 0, 1, and 2
        
        f_value = f.subs(variables[-1], d_value)
        poly = Poly(f_value)
                    # Get the coefficients
        coeffs = poly.coeffs()
        new_del = abs(coeffs[0]-0.5)
        if new_del <= min_delta:
            min_delta = new_del
            if min_delta in dict_a_min:
                dict_a_min[min_delta].append(lst_a)
            else:
                dict_a_min[min_delta] = [lst_a]
            #lst_a_min.append(lst_a)
    print(dict_a_min[min_delta])
    print(f"min_delta= {min_delta}")   
    return dict_a_min[min_delta]
    
    #print(lst_a_min)
def groupByVariabled():
    f_template = createFTemplate()
    #print(f_template)
    expr = f_template.as_expr()
    # Group the expression by d
    grouped_expr = collect(expr, d)
    print("gr",grouped_expr)
    return grouped_expr
def calcValFunc(f):
    y = [f.subs(d, a) for a in lst_x]
    value_func = []
    for f_value in y:
        poly = Poly(f_value)
        coeffs = poly.coeffs()
        value_func.append(coeffs[0])
    return value_func
def drawGraphicMultipleFunctions():
    i = 1
    ranges = [range(combination(n,i)+1) for i in range(n+1)]
    for lst_a in product(*ranges):
        f = createF(lst_a)
        value_func = calcValFunc(f)
        #
        plt.plot(lst_x, value_func)
        # plt.plot(lst_x, value_func, label=f'f{i}')
        i+=1
    plt.xlabel('i')
    plt.ylabel('f(i)')
    plt.title('Graph of Multiple Functions')
    plt.legend()
    #plt.show()
    #Lưu đồ thị vào file PDF
    with PdfPages('GraphMultipleFunctions2.pdf') as pdf:
        pdf.savefig()
        plt.close()

    print("success!!!")
def drawGraphicOneFunction(f,title):
    value_func = calcValFunc(f)
    plt.plot(lst_x, value_func, label=f'{f}')
    plt.xlabel('i')
    plt.ylabel('f(i)')
    plt.title(f'{title}')
    plt.legend()
    #plt.show()
    #Lưu đồ thị vào file PDF
    with PdfPages(f'{title.replace(" ","")}.pdf') as pdf:
        pdf.savefig()
        plt.close()

    print("success!!!")
def findMinIntegrate():
    min_integrate = 100
    ranges = [range(combination(n,i)+1) for i in range(n+1)]
    for lst_a in product(*ranges):
        f = createF(lst_a)
    # Chuyển đổi Poly sang biểu thức sympy thông thường để tính toán
        f_expr = f.as_expr() - 1/2
        #print(f)
        #print(f_expr)
        # Tính tích phân trị tuyệt đối của hàm số trên một khoảng xác định, ví dụ từ -1 đến 1
        integral_result = integrate(Abs(f_expr), (d, -0.0001, 0.0001))
        if integral_result < min_integrate:
            min_integrate = integral_result
            f_min = f
            a_min = lst_a
    print(f"amin = {a_min}")     
    print(f"min = {min_integrate}")
    return f_min
def createProbabilitieFunctionForAffineFunction():
    start_N = 3
    end_N = 10
    for n_curr in range(start_N,end_N):
        f = Poly(0,variables)
        probability_f = f+Poly(1/2+((-2)**(n_curr-1))*(d**n_curr))
        print(probability_f)
        value_func = calcValFunc(probability_f)
        #
        #plt.plot(lst_x, value_func)
        plt.plot(lst_x, value_func, label=f'f{n_curr}')
    plt.xlabel('i')
    plt.ylabel('f(i)')
    plt.title('Graph of Multiple Probability Functions For AffineFunctions')
    plt.legend()
    #plt.show()
    #Lưu đồ thị vào file PDF
    with PdfPages('GraphMultipleFunctionsaffine.pdf') as pdf:
        pdf.savefig()
        plt.close()
    #print("res 1/2 is:", integral_result)
    
    
# ============================================ Main function ============================================
#findKlevelingfunction()
#groupByVariabled()
# findMindelta()
# f_min = findMinIntegrate()
# # f= createF([1,0,3,0])
# drawGraphicOneFunction(f,title="graphic affine function 2")
# drawGraphicMultipleFunctions()

createProbabilitieFunctionForAffineFunction()