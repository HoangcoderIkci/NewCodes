from math import log2
G_n = 4
G_size = 1 << G_n
def createVecCoefficients(a):
    lst_vec = [0] * G_size
    t = 0
    while a:
        lst_vec[1 << t] = a&0b1
        t+=1
        a >>=1
    return lst_vec
def fastFindCoefficientsZhegalkin(lst_coefficients : list):
    length = len(lst_coefficients)
    k = int(log2(length))
    res = [x for x in lst_coefficients]
    for idx1 in range(k):
        half_len = 1 << idx1
        full_len = half_len << 1
        num_turns = length // full_len
        for idx2 in range(num_turns):
            for idx3 in range(half_len):
                res[idx2 * full_len+half_len+idx3] ^= res[idx2 * full_len+idx3] 
        #print(res)
    # in ra kết quả
    #printCoefficientsZhegalkin(res,length=length,k=k)
    return res
def calcDistance(F,G):
    dis = 0
    for idx in range(G_size):
        dis+=G[idx] ^ F[idx]
    return dis
def printCoefficientsZhegalkin(res,length,k):
    if res[0]:
        print("1 + ",end="")
    for idx1 in range(1,length):
        temp = res[idx1]
        if temp:        
            bina = idx1
            count = k
            #print(f"{temp}*",end="")
            while(bina):
                if bina&0b1:
                    print(f"x{count}",end="")
                bina >>=1
                count-=1
            print("",end=" + ")
    print()
def process(F,case):
    distance = G_size
    for a in range(G_size):
        lst_vec = createVecCoefficients(a)
        #print(lst_vec)
        lst_vec[0] = case
        #print(lst_vec)
        zhegal = fastFindCoefficientsZhegalkin(lst_vec)
        #print(zhegal)
        z_temp = fastFindCoefficientsZhegalkin(zhegal)
        #print(z_temp == lst_vec)
        dis = calcDistance(F,zhegal)
        if dis == 4:
            printCoefficientsZhegalkin(lst_vec,G_size,G_n)
            #print(zhegal)
        if distance>dis:
            distance = dis
    print(f"distance = {distance} in case a_0 = {case}")

str_temp = "1001100100111010"
F = [int(x) for x in str_temp]
process(F,case=1)