import math
char = 851
NOL = (char,char)
a = 1
b = 3
# y^2 = x^3 + ax + b
F  = [b,a,0,1]

k_global = 5184

def Nhan_trong_module(A, B, Module):
    A = int(A)
    B = int(B)
    A%=Module
    B%=Module
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
def UCLN_u_v_in_MOD(A, B, MOD):
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
    return (g * y) % MOD, G % MOD, H % MOD
def calcF(x,coefficients):
    res = coefficients[-1]
    for coeff in coefficients[-2::-1]:
        res = Nhan_trong_module(res,x,char)
        res = (res + coeff)%char
    return res
def createY():
    lstPoints = []
    for x in range(char):
        valF = calcF(x,F)
        # tim y
        for y in range(char):
            if Nhan_trong_module(y,y,char) == valF:
                lstPoints.append((x,y))
                lstPoints.append((x,(char-y)%char))
                break
    return list(set(lstPoints))
def AddTwoPoints(P1,P2):
    # th1 : P1 = ~0 or P2 = ~0
    if P1 == NOL: return P2
    if P2 == NOL: return P1
    # th2 :
    if P1[0] == P2[0] and (P1[1] + P2[1] == char or P1[1] == P2[1]==0):
        return NOL
    # th4 :
    if P1 == P2:
        # tính alpha 
        numerator = Nhan_trong_module(P1[0],P1[0],char)
        numerator = (numerator * 3 + a ) % char
        denominator = (P1[1] << 1)%char
        # _,u,_ = UCLN_u_v_in_MOD(denominator,char,char)
        # alpha = Nhan_trong_module(u,numerator,char)
        # miu = (P1[1] - alpha*P1[0])%char
        # x3 = (alpha*alpha - (P1[0] << 1)) % char
        # y3 = (- (alpha*x3+miu)) % char
        # return (x3,y3)
    #th3 
    else:
        numerator = (P2[1] - P1[1]) % char
        denominator = (P2[0] - P1[0]) % char
    d_temp,_,_ = UCLN_u_v_in_MOD(P2[1],char,char)
    if d_temp!=1:
        print("ERROR: d_temp = ",d_temp)
    d,u,_ = UCLN_u_v_in_MOD(denominator,char,char)
    if d!=1:
        print("ERROR: d = ",d)
    alpha = Nhan_trong_module(u,numerator,char)
    miu = (P1[1] - alpha*P1[0])%char
    x3 = (alpha*alpha - (P1[0] + P2[0])) % char
    y3 = (- (alpha*x3+miu)) % char
    return (x3,y3)
def powerPoint(point,power):
    P = point
    res = NOL
    while power:
        if power&0b1:
            res = AddTwoPoints(res,P)
            #print("power = ",power)
        P = AddTwoPoints(P,P)
        power >>=1
    return res    
# def findRankPoint(lstPoints):
#     return len(lstPoints)    
        
def main():
    # lstPoints = createY()
    # print(lstPoints)
    # print("rank group point = ",len(lstPoints)+1)
    # P1 = lstPoints[1]
    # P3 = powerPoint(P1,2)
    # print(P3)
    P = (-1,1)
    for t in range(1,5):
        print(1<<t)
        P = powerPoint(P,2)
        print(P)    
    R = P
    print("Part two")
    for t in range(1,5):
        print(1<<t)
        R = powerPoint(R,2)
        print(R) 
    P1 = (189,169)
    P2 = (313,599)
    P3 = AddTwoPoints(P1,P2)
    print(f"P3 = {P3}")

    P4 = (191,792)
    P3 = AddTwoPoints(P3,P4)
    print(f"P3 = {P3}")
    #print(temp)
    
    P4 = (383,538)
    P3 = AddTwoPoints(P3,P4)
    print(f"P3 = {P3}")
    
    
    
    
#"""_summary_
# nhớ thay đổi a,b ở trên tương ứng với hàm y^2 = x^3 + ax + b
#"""
# Main function
main()

