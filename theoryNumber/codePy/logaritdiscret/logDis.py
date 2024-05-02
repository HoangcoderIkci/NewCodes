def UCLN_u_v(A, B):
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
    return (g * y) , G , H 
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
def createTable(gr_order : int,g,y,mod,dict_primers : dict):
    len_dict = len(dict_primers)
    table = []
    for key,val in dict_primers.items():
        row_tab = [1]
        #temp_mod = (key**val) 
        temp1 = g**(gr_order//key)% mod
        temp2 = temp1
        for idx1 in range(1,key):
            row_tab.append(temp1)
            temp1 = (temp1 * temp2) %mod
        table.append(row_tab)
    return table
# buoc 2 :
def stepFindAForEachPart(table,gr_order,g,y,mod,dict_primers : dict):
    lst_A = []
    turn = 0
    _,g_inv,_ = UCLN_u_v(g,mod)
    g_inv %= mod
    for key,val in dict_primers.items():
        a = 0
        temp1 = gr_order//key
        turn2 = 0
        for idx1 in range(val):
            temp2 = (((g_inv **a) * y) **temp1)%mod
            idx2 = -1
            for elem in range(len(table[turn])):
                if table[turn][elem] == temp2:
                    idx2 = elem
                    break
            if idx2 != -1:
                a+=idx2 * (key**turn2)
            turn2+=1
            temp1//=key
        turn+=1
        lst_A.append(a)
    #print(lst_A)
    return lst_A
def stepFindA(lst_A,lst_primes):
    a = remainderChinese(lst_A,lst_primes)
    return a
def fullStep(gr_order : int,g,y,mod,dict_primers : dict):
    tab = createTable(gr_order,g,y,mod,dict_primers)
    lst_a = stepFindAForEachPart(tab,gr_order,g,y,mod,dict_primers)
    lst_M = []
    for key,item in dictionary.items():
        lst_M.append(key**item)
    a = stepFindA(lst_a,lst_M)
    print(f"value a = {a}")
    
    
    
# Main functions
dictionary = {2 : 2,5:2}
ord_gr = 100
g = 4
module = 5**3
for t in range(3,4,1):
    print("y : ",t)
    y = (g**t) % module
    fullStep(ord_gr,g,y,module,dictionary)

