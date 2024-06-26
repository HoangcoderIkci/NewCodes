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
def remainderChinese(lstU,lstM):
    u = 0
    c = d = 0
    M = 1
    for elem in lstM:
        M *= elem
    if len(lstU) != len(lstM): 
        return False
    for i in range(len(lstU)):
        c =  M // lstM[i]
        _,d,_ = UCLN_u_v_in_MOD(c,lstM[i],M)
        u += c*d*lstU[i]
        # %= M
    return u % M   
    
u = remainderChinese([1,16],[2,27])
print(u)