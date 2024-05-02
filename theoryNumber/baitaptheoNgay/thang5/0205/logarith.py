import math
h = 6
B = 17
r = int(B**(0.5))+1
charSet = 17
g = 3
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
def createArrayPower():
    arrayPowValueOfEleG = {}
    temp = g
    arrayPowValueOfEleG[0] = 1
    arrayPowValueOfEleG[1] = g
    for a in range(2,r):
        temp = (temp*g) % charSet
        arrayPowValueOfEleG[a] = temp
    #arrayPowValueOfEleG = sorted(arrayPowValueOfEleG.items(), key=lambda x: x[1])
    return arrayPowValueOfEleG


# main function

def main():
    arrayPowValueOfEleG = createArrayPower()
    #b2 tim g1
    _,u,_= UCLN_u_v_in_MOD(g,charSet,charSet)
    g1 = powInModule(u,r,charSet)
    #B3
    #arrRes = []
    for b in range(r):
        arrX = []
        temp = powInModule(g1,b,charSet)
        temp = Nhan_trong_module(temp,h,charSet)
        for key, value in arrayPowValueOfEleG.items():
            if value == temp:
                arrX.append(key)
        if arrX:
            mulRB = (r*b) % charSet
            if type(arrX) == int:
                print((mulRB + arrX) % charSet)
                return (mulRB + arrX) % charSet
            else:
                min = (mulRB + arrX[0]) % charSet
                for x in arrX:
                    temp2 = (mulRB + x) % charSet
                    if temp2 < min: min = temp2
                print(min)
                return min
                
                
        
    
main()

