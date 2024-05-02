from sympy import symbols, gcd,Poly, FF,diff,div
from math import log,ceil,e,sqrt
from random import randint
import numpy as np
def FindGcdPolynomial(F,G):
    x = symbols('x')
    f_x = Poly(F,x)
    g_x = Poly(G,x)
    ucln = gcd(f_x, g_x)
    coefficients = ucln.all_coeffs()
    print(coefficients[0])
#A probable algorithm for finding the divisor of a polynomial
def probableFindingDivisorPolynomial(polyD : list,primerModule):
    x = symbols('x')
    lst_solutions = []
    domain = FF(primerModule)
    D_x = Poly(polyD, x,domain = domain)
    while D_x.degree()>1:
        denta = randint(1, primerModule-1)
        a = 5
        P_x = Poly((x - denta)**((primerModule - 1)//2) - 1,domain = domain)
        #print(P_x)
        H_x = gcd(D_x, P_x)
        if(H_x.degree()==1):
            print("Found!!! H_x = ",H_x)
            lst_solutions.append(-H_x.all_coeffs()[-1])
            D_x,_ = div(D_x,H_x)
    lst_solutions.append(-D_x.all_coeffs()[-1])
    for id in range(len(lst_solutions)):
        lst_solutions[id]%=primerModule
    return lst_solutions  
def CalcValueOfFunction(coefficients,x):
    # truyền theo thứ tự sau : từ coefficients của bậc cao đến thấp
    res = coefficients[0]
    for elem in coefficients[1:]:
        res=res*x+elem        
    return res
    #res+= coefficients[-1]
def UCLN_u_v(A, B):
    A = abs(A)
    B = abs(B)
    g = 1
    _A = A
    _B = B
    while _A % 2 == 0 and _B % 2 == 0:
        _A >>= 1
        _B >>= 1
        g <<= 1
    x, y, E, F, G, H = _A, _B, 1, 0, 0, 1
    while x != 0:
        while x % 2 == 0:
            x >>= 1
            if E % 2 == 0 and F % 2 == 0:
                F >>= 1
                E >>= 1
            else:
                E = (E + _B) >> 1
                F = (F - _A) >> 1
        while y % 2 == 0:
            y >>= 1
            if G % 2 == 0 and H % 2 == 0:
                G >>= 1
                H >>= 1
            else:
                G = (G + _B) >> 1
                H = (H - _A) >> 1
        if x >= y:
            x -= y
            E -= G
            F -= H
        else:
            y -= x
            G -= E
            H -= F

    # print(f"d = {g*y}")
    # print(f"u = {G}")
    # print(f"v = {H}")
    return (g * y) , G , H     
def hensels_lifting(f,p,k,x0,c_limit):
    """_summary_

    Args:
        f (_type_): _description_
        p (_type_): _description_
        k (_type_): _description_
        x0 (_type_): _description_
    """
    lst_x0 = [x0]
    x = symbols('x')
    f_prime = diff(f,x)
    for i in range(1,k):
        f_val = f.subs(x,x0)
        f_prime_val = f_prime.subs(x,x0) % p
        h = -f_val // (p**i)
        h%=p
        if f_prime_val == 0 and h != 0:
            return lst_x0
        if h==0:
            solution=0
        else:
            _,u,_ = UCLN_u_v(f_prime_val,p)
            solution  = (u*h) % p
        x0+= solution * (p**i)
        if x0 >c_limit:
            break
        lst_x0.append(x0)
    return lst_x0
        # giải so sánh t1 f' = h (mod p)
def SieveOfEratosthenes(n):
    prime = [True for i in range(n+1)]
    p = 2
    res = []
    while (p * p <= n):
        if (prime[p] == True):
            for i in range(p * p, n+1, p):
                prime[i] = False
        p += 1
    for p in range(2, n+1):
        if prime[p]:
            res.append(p)
    print(res)
    return res        
def kiem_tra_binh_phuong(a, b):
    # a = 7
    # b = 5
    if a % b == 0:
        return 0
    res = 1
    temp = 0
    while a != 2 and a != 1:
        du = a % b
        if du >= b - du:
            a = b - du
            res *= (-1) ** ((b - 1) / 2)
        else:
            a = du
        while a % 2 == 0:
            a /= 2
            res *= (-1) ** ((b**2 - 1) / 8)
        if a == 1:
            return res
        if a == 0:
            return 0
        temp = a
        a = b
        b = temp
        res *= (-1) ** ((a - 1) * (b - 1) / 4)
    return res
def Nhan_trong_module(A, B, Module):
    A = int(A)
    B = int(B)
    Module = int(Module)
    n = ceil(log(Module, 2))
    binary_list = [int(i) for i in bin(A)[2:]]
    temp = n - len(binary_list)
    binary_list = [0] * temp + binary_list
    C = (2 ** (2 * n)) % Module
    R = 0
    for i in range(n):
        if binary_list[n - 1 - i] & 0b01:
            R = R + B
        if R & 0b01:
            R += Module
        R >>= 1
    if R >= Module:
        R -= Module
    A, B = R, C
    binary_list = [int(i) for i in bin(A)[2:]]
    temp = n - len(binary_list)
    binary_list = [0] * temp + binary_list
    R = 0
    for i in range(n):
        if binary_list[n - 1 - i] & 0b01:
            R += B
        if R & 0b01:
            R += Module
        R >>= 1
    if R >= Module:
        R -= Module
    return R
def powInModule(p,x,Mod): # chỉ module lẻ mới được
    res = 1
    while x:
        if x&0b1:
            res = Nhan_trong_module(res,p,Mod)
        p = Nhan_trong_module(p,p,Mod)
        x >>=1
    return res
def changeToBacThangModule(mt1):
    # print(mt1)
    rank = 0
    lst_ind_basic = []
    # Lấy kích thước số hàng và cột của ma trận
    num_rows, num_cols = mt1.shape
    for col in range(num_cols):
        for row in range(rank, num_rows):
            if mt1[row][col]:
                lst_ind_basic.append(col)
                if row != rank:
                    temp_row = mt1[row].copy()
                    # print(temp_row)
                    mt1[row] = mt1[rank]
                    # print(temp_row)
                    mt1[rank] = temp_row
                    #print(mt1, end="\n\n")
                # ap null các rows ở dưới row rank:
                for idr in range(rank + 1, num_rows):
                    if mt1[idr][col]:
                        #hs_temp = mt1[idr][col]
                        for idcl in range(col, num_cols):
                            mt1[idr][idcl] ^= mt1[rank][idcl]  
                #print(mt1, end="\n\n")
                rank += 1
    # đưa về dạng chuẩn
    temp_r = rank - 1
    lst_temp_id_bs = lst_ind_basic.copy()
    lst_temp_id_bs.reverse()
    # print("lst bs", lst_ind_basic)
    for id_bs in lst_temp_id_bs:
        for id_r in range(0, temp_r):
            if mt1[id_r][id_bs]:
                #hs_temp = mt1[id_r][id_bs]
                mt1[id_r][id_bs] = 0
                for id_cl in range(id_bs + 1, num_cols):
                    mt1[id_r][id_cl] ^= mt1[temp_r][id_cl]
        temp_r -= 1
    # tìm ind phần tử khác 0 cuối cùng
    lst_solutions = []
    for idx in range(num_cols):
        if idx not in lst_ind_basic:
            col_temp = mt1[:, idx]
            col_temp[idx] = 1
            lst_solutions.append(col_temp)
    print("solutions (list vector Z): ", lst_solutions)
    return lst_solutions
        

def GcdFast(A, B):
    g = 1
    _A = A
    _B = B
    while _A % 2 == 0 and _B % 2 == 0:
        _A >>= 1
        _B >>= 1
        g <<= 1
    x, y, E, F, G, H = _A, _B, 1, 0, 0, 1
    while x != 0:
        while x % 2 == 0:
            x >>= 1
            if E % 2 == 0 and F % 2 == 0:
                F >>= 1
                E >>= 1
            else:
                E = (E + _B) >> 1
                F = (F - _A) >> 1
        while y % 2 == 0:
            y >>= 1
            if G % 2 == 0 and H % 2 == 0:
                G >>= 1
                H >>= 1
            else:
                G = (G + _B) >> 1
                H = (H - _A) >> 1
        if x >= y:
            x -= y
            E -= G
            F -= H
        else:
            y -= x
            G -= E
            H -= F

    # print(f"d = {g*y}")
    # print(f"u = {G}")
    # print(f"v = {H}")
    return g * y, G, H
# changeToBacThangModule(mt1, 2)
def createMatrix(lst_analysis_F_x : list):
    mt = []
    for dt in lst_analysis_F_x:
        mt.append(list(dt.values()))
    for id1 in range(len(mt)):
        for id2 in range(len(mt[id1])):
            mt[id1][id2] &=0b1
    matrix = np.array(mt)
    mt_T = matrix.transpose()
    return mt_T
def MainProcess(coefficients_f,A,C,B,N):
    H = int(N**(1/2)) + 1
    J = H**2 - N
    x = symbols('x')
    poly_f = Poly(coefficients_f,x)
    #bước 1 tạo basic B
    F_B_temp = SieveOfEratosthenes(B)
    #F_B = [2,3,5]
    F_B = []
    for elem in F_B_temp:
        if kiem_tra_binh_phuong(elem,N) == 1:
            F_B.append(elem)
    print(f"F_B = {F_B}")
    len_F_B = len(F_B)
    # tạo dict :
    lst_analysis_F_x = [dict(zip(F_B,[0]*len_F_B)) for i in range(C-A+1)]
    
    #dt_primer = dict(zip(F_B,[0]*len_F_B))
    #bước 2 tính giá trị của F và tìm max
    arrValuesOfFunc = []
    for x in range(A,C+1):
        val = CalcValueOfFunction(coefficients_f,x)
        arrValuesOfFunc.append(val)
    print("bảng giá trị ban đầu(Исходная таблица значений): ",arrValuesOfFunc)
    # sử lý cho việc có nghiệm chia hết cho 2 riêng biệt
    for id in range(len(arrValuesOfFunc)):
        while arrValuesOfFunc[id]&0b1==0:
            arrValuesOfFunc[id] >>=1
            lst_analysis_F_x[id][2]+=1
   
    print("bảng giá trị sau khi chia 2(Таблица значений после деления на 2): ",arrValuesOfFunc)        
    # for id in range(1,C+1,2):
    #     arrValuesOfFunc[id] >>=1
    # tìm max
    max_val = arrValuesOfFunc[0]
    for val in arrValuesOfFunc[1:]:
        if max_val < val: max_val = val
    #bước 3 : Tính nghiệm với từng số nguyên tố
    ## tìm nghiệm riêng cho trường hợp p = 2
    ## giải cho các p còn lại
    #arrayAllSolutions = []
    for p in F_B[1:]:
        k = int(log(max_val)//log(p))
        print(f"bắt đầu với p(Начнем с p) = {p}")
        lst_solutions = probableFindingDivisorPolynomial(coefficients_f,p)
        print(f"Nghiệm tương ứng với module p(Решение, соответствующее модулю p) = {lst_solutions}")
        print("bắt đầu xử lý từng nghiệm(Начнем обработку каждого решения)")
        # hensels_lifting cho từng nghiệm
        for x0 in lst_solutions:
            lst_sol = hensels_lifting(poly_f,p,k,x0,c_limit=C)
            print(f"list nghiệm tương ứng với nghiệm x0 = {x0} (khi dùng thuật toán hensels_lifting)(Список решений, соответствующих решению x0 (при использовании алгоритма hensels_lifting) là {lst_sol}")
            turn = 1
            for solution in lst_sol:
                distance = p**turn
                print(f"bắt đầu xử lý đối với(начать обработку для) : P**t = {distance}")
                for idx1 in range(solution % distance,C+1,distance):
                    arrValuesOfFunc[idx1]//=p
                    lst_analysis_F_x[idx1][p]+=1
                print("bảng giá trị sau khi xử lý(таблица значений после обработки) p**t: ",arrValuesOfFunc)   
                turn+=1
    print("При значениях c после этого F(c) является B-гладким: ",end="")     
    lst_index_c = []
    for idx1 in range(len(arrValuesOfFunc)):
        if arrValuesOfFunc[idx1] ==1 or arrValuesOfFunc[idx1] == -1:
            print(idx1,end=',')
            lst_index_c.append(idx1)
    print()
    lst_analysis_F_x2 = []
    for id in lst_index_c:
        print(lst_analysis_F_x[id])
        lst_analysis_F_x2.append(lst_analysis_F_x[id])
    print()
    matrix_np = createMatrix(lst_analysis_F_x2)
    lst_z_solutions = changeToBacThangModule(matrix_np)
    for vector_z in lst_z_solutions:
        x = 1
        y = 1
        for z in vector_z:
            if z:
                x*=(lst_index_c[z]+H)    
                dict_primers = lst_analysis_F_x2[z]
                for key,val in dict_primers.items():
                   # y = Nhan_trong_module(y,key**(val >> 1),N)
                    y = Nhan_trong_module(y,powInModule(key,val>>1,N),N)
        #print(x,y)
        print(f"x ={x},y ={y}")
        d,_,_ = GcdFast((x-y)%N,N)
        # print(f"d = {d}")
        if d !=1 and d != N:
            print("\n\n################################ Results #################################")
            print(f"нащел делител d = {d}")
            return True

    # b1 tính giá trị của hàm số từ A đến C
    
# Main function
if __name__ == "__main__":
# Khai báo biến x là biến biểu tượng
    x = symbols('x')
    A = 0
    L = 12
    B = 7
    N = 2449
    H = int(N**(1/2)) + 1
    J = H**2 - N
    f = [1,2*H,J]
    MainProcess(f,A,L,B,N)

