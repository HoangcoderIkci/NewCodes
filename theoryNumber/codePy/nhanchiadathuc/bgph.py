import math
import sympy as sp
from random import randint
from sympy.polys.domains import GF
def Nhan_trong_module(A, B, Module):
    A = int(A)
    B = int(B)
    Module = int(Module)
    n = math.ceil(math.log(Module, 2))
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
def powInModule(a,x,mod):
    x = int(x)
    res = 1
    while x :
        if x&0b1:
            res = Nhan_trong_module(res,a,mod)
        a = Nhan_trong_module(a,a,mod)
        x >>=1
    return res
            

def UCLN_u_v_in_MOD(A, B, MOD):
    A = int(abs(A))
    B = int(abs(B))
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
    return (g * y)% MOD, G% MOD , H % MOD

def process1(A, so_mu, l, r, w, t, n, d, res, MOD):
    m = r - l + 1
    #print(l, r)
    temp = int(m / 2)
    A_cp = A.copy()
    #c1 = (w**so_mu) % MOD
    c1 = powInModule(w,so_mu,MOD)
    #c2 = (w ** (so_mu + n / 2)) % MOD
    c2 = powInModule(w,so_mu + (n >> 1),MOD)
    for i in range(l, l + temp):
        #A_cp[i] = (A[i] + c1 * A[i + temp]) % MOD
        A_cp[i] =( A[i] + Nhan_trong_module(c1,A[i + temp],MOD)) % MOD
        #A_cp[i + temp] = (A[i] + c2 * A[i + temp]) % MOD
        A_cp[i + temp] = (A[i] + Nhan_trong_module( c2 , A[i + temp],MOD)) % MOD
    #print(A_cp)
    if t < d:
        A_cp, res = process1(A_cp, so_mu / 2, l, l + temp - 1, w, t + 1, n, d, res, MOD)
        A_cp, res = process1(
            A_cp, (so_mu + n / 2) / 2, l + temp, r, w, t + 1, n, d, res, MOD
        )
    else:
        res[int(so_mu)] = A_cp[l]
        res[int((so_mu + n / 2))] = A_cp[r]
    return A_cp, res


def find_bgph(A, n, w, *, d, res, MOD):
    r = len(A) - 1
    A_res, res = process1(A, 0, 0, r, w, 1, n, d, res, MOD)
    # qua trinh 2 tim n^-1
    d, u, v = UCLN_u_v_in_MOD(n, MOD, MOD=MOD)
    # print(u, v)
    res_cp = res.copy()
    for i in range(len(res)):
        res[i] = Nhan_trong_module(u, res[i], Module=MOD)
    l_temp = res.copy()[1:]
    l_temp.reverse()
    hs_polymian = [res[0]] + l_temp
    return A_res, res_cp, hs_polymian

def chuan_hoa_he_so(coefficients):
    # tim 
    leng = len(coefficients)
    id_last = 0
    for i in range(leng, 0, -1):
        if coefficients[i-1]:
            id_last = i
            break
    coefficients = coefficients[:id_last]
    if not isinstance(coefficients,list):
        return [coefficients]
    return coefficients
def multipleTwoPolynomialverSupper(F_input,G_input,w,module):
    if(len(F_input)==len(G_input)==1):
        return [F_input[0]*G_input[0]]
    F = []
    G = []
    #w = 2**3
    #sao chép để không thay đổi F,G
    for elem in F_input:
        F.append(elem)
    for elem in G_input:
        G.append(elem)
    # tìm phần khác 0 cuối cùng
    F = chuan_hoa_he_so(F)
    G = chuan_hoa_he_so(G)
    if(len(F)==len(G)==1):
        return [F_input[0]*G_input[0]]       
    deg_sum = len(G) + len(F) - 2
    d = int(math.ceil(math.log(deg_sum+1, 2)))
    n = 2**d
    t = 32//n
    if t == 0:
        t=1
    w = 2**t
    M = w**(n >> 1) + 1
    #M = module
    F.extend([0] * (n - len(F)))
    G.extend([0] * (n - len(G)))
    # buoc 2 tinh gia tri cua F
    res1 = [0] * n
    _, res1, hs_pl = find_bgph(F, n, w, d=d, res=res1, MOD=M)
    # buoc 3 tinh gia tri cua G
    res2 = [0] * n
    _, res2, hs_p2 = find_bgph(G, n, w, d=d, res=res2, MOD=M)
    # buoc 4 nhan toa do 2 gia tri cua F va G
    pl1 = res1
    pl2 = res2
    tich_toa_do = []
    if len(pl1) <= len(pl2):
        tich_toa_do = pl2.copy()
        for i in range(len(pl1)):
            tich_toa_do[i] = Nhan_trong_module(pl1[i], tich_toa_do[i], Module=M)
    else:
        tich_toa_do = pl1.copy()
        for i in range(len(pl2)):
            tich_toa_do[i] = Nhan_trong_module(pl2[i], tich_toa_do[i], Module=M)
            
    #print(tich_toa_do)
    res3 = [0] * n
    _, _, hspl3 = find_bgph(tich_toa_do, n, w, d=d, res=res3, MOD=M)
    #print(hspl3)
    for id in range(len(hspl3)):
        hspl3[id]%=module

    # for p in range(len(hspl3)-1):
    #     if hspl3[p] != 0:
    #         print(f"{hspl3[p]}*x^{p}+",end="")
    # print(f"{hspl3[-1]}*x^{len(hspl3)-1}")    
    return chuan_hoa_he_so(hspl3)


################## BEGIN function chia da thuc ##################
def InverseCoefficients(F_x,taget_degree):
    NewF_x = [0] * (taget_degree+1)
    for id in range(min(len(F_x),taget_degree+1)):
        NewF_x[-1-id] = F_x[id]
    return NewF_x
        
    
def PhiSupport(A_x,G_x,w,module,bac_mod_x):
    # a(x) (2-a*g)
    #b1 tinh a*g:
    #mult_a_g = multipleTwoPolynomial(A_x,G_x,w,N,d,module)
    mult_a_g = multipleTwoPolynomialverSupper(A_x,G_x,w,module)
    if not isinstance(mult_a_g,list): mult_a_g = [mult_a_g]
    min_len = min(len(mult_a_g),bac_mod_x)
    mult_a_g = mult_a_g[:min_len]
    # 2 - a*g:
    mult_a_g[0] = mult_a_g[0] - 2
    for idx in range(len(mult_a_g)):
        mult_a_g[idx] = (-mult_a_g[idx])%module
    #b3 tinh a(x) (2-a*g)
    res = multipleTwoPolynomialverSupper(A_x,mult_a_g,w,module)
    #print(res)
    return res[:bac_mod_x]

def getRemainderDivider(F_x,G_x,w,MOD):
    F_x = [x %MOD for x in F_x]
    G_x = [x %MOD for x in G_x]
    deg_F = len(F_x)-1
    m = len(G_x) - 1
    d = int(math.ceil(math.log(deg_F, 2)))
    N = 2**d
    #F_x.extend([0] * (N-len(F_x)))
    #deg_F = N-1
    #b0 tinh k : 2^(k-1) <= n-m < 2^k
    k = int(math.log2(deg_F-m)) + 1
    #module = w**(N >> 1) + 1
    module = MOD
    #b1 : dao nguoc tat ca he so cua F va G
    F_x_inv = InverseCoefficients(F_x,deg_F)
    #printfPoly(F_x_inv,module)
    G_x_inv = InverseCoefficients(G_x,m)
    #printfPoly(G_x_inv,module)
    #b2 tim G[-1]^-1
    _,P_x,_ = UCLN_u_v_in_MOD(G_x[-1],module,module)
    P_x = [P_x]
    #b3 tinh P_k 
    for i in range(1,k+1):
        bac_hien_tai = (1 << i)
        P_x = PhiSupport(P_x[:bac_hien_tai],G_x_inv[:bac_hien_tai],w,module,bac_hien_tai)
        #(P_x)
        P_x = P_x[:(1 << i)]
        P_x = chuan_hoa_he_so(P_x)

    
    Q_x = multipleTwoPolynomialverSupper(F_x_inv[:deg_F-m+1],P_x[:deg_F-m+1],w,module)
    #b5 tinh Q_x mod (x ^ (deg_F-m+1))
    Q_x = Q_x[:deg_F-m+1]
    #b6 revers Q_x 
    Q_x = InverseCoefficients(Q_x,deg_F-m)
    #b7 tinh R_x = F_x_ - Q_x * G_x
    Q_x_G_x = multipleTwoPolynomialverSupper(Q_x,G_x,w,module)
    R_x = []
    min_len = min(m, len(F_x), len(Q_x_G_x))
    for id in range(min_len):
        R_x.append((F_x[id]-Q_x_G_x[id])%module)
    return Q_x,R_x
################## END function chia da thuc ##################
################## BEGIn function chia da thuc ##################
################## END function chia da thuc ##################


def multiply_polynomials_check(coeffs1, coeffs2, p):
    # Định nghĩa biến
    x = sp.symbols('x')
    
    # Tạo hàm số từ các hệ số trong trường GF(p)
    poly1 = sum(c * x**i for i, c in enumerate(coeffs1))
    poly2 = sum(c * x**i for i, c in enumerate(coeffs2))
    
    # Chuyển đổi poly1 và poly2 thành Poly với miền là GF(p)
    poly1_GF = sp.Poly(poly1, x, domain=GF(p))
    poly2_GF = sp.Poly(poly2, x, domain=GF(p))
    
    # Nhân hai hàm số trong trường GF(p)
    product_GF = poly1_GF * poly2_GF
    
    # Trả về kết quả dưới dạng Poly trong GF(p) hoặc một list hệ số
    return product_GF
def printfPoly(coeffs1,p):
    x = sp.symbols('x')
    # Xoay ngược lại list bằng cách sử dụng slicing
    reversed_list = coeffs1[::-1]
    #poly1 = sum(c * x**i for i, c in enumerate(coeffs1))
    poly1_GF = sp.Poly(reversed_list, x, domain=GF(p))
    print(poly1_GF)
# Ví dụ sử dụng:

def checkEqualityInModule(coefficients1,coefficients2,mod):
    for id in range(len(coefficients1)):
        if (coefficients1[id] - coefficients2[id]) % mod:
            return False
    return True


if __name__ == '__main__':
    """_summary_ nhớ viết hàm số theo formmat sau : ví dụ F(x) = 1 + 2x + 3x**2 + 4x**3
    thì F=[1,2,3,4]
    nhớ chỉnh biến mod
    """
    x = sp.symbols('x')
    F = []
    G = []
    # divisor = []
    # dividend = []
    for id in range(40):
        F.append(randint(0,2))
    for id in range(20):
        G.append(randint(0,2))
    # F = [2,0,2,1,0,1,1,1,0,1] 
    # G = [2,1,0,0,1]
    F.append(1)
    G.append(1)
  
    mod = 17
    divisor = []
    for elem in F:
        divisor.append(elem)
    print("divisor = ")
    printfPoly(divisor,mod)
    dividend = []
    for elem in G:
        dividend.append(elem)
    print("dividend = ")
    printfPoly(dividend,mod)
    t = 5
    w = -1
    quotient,remainder = getRemainderDivider(divisor,dividend,w,mod)
    printfPoly(quotient,mod)
    printfPoly(remainder,mod)
    poly_f = sp.Poly(F[::-1],x,domain=GF(mod))
    #print("poly_f = ",poly_f)
    poly_G = sp.Poly(G[::-1],x,domain=GF(mod))
    #print("poly_G = ",poly_G)
    q,r = poly_f.div(poly_G)
    
    print(checkEqualityInModule(q.all_coeffs()[::-1],quotient,mod))
    print(checkEqualityInModule(r.all_coeffs()[::-1],remainder,mod))