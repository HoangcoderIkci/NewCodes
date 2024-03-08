CHAR = 2
HS_POLE = 451
sizeFiled = 8
limitField = (1 << sizeFiled)
TableMultiplyOfField = [[0]*limitField for i in range(limitField)]
TableInverseElement = [0 for i in range(limitField)]
PiTable = [[12, 4, 6, 2, 10, 5, 11, 9, 14, 8, 13, 7, 0, 3, 15, 1],[6, 8, 2, 3, 9, 10, 5, 12, 1, 14, 4, 7, 11, 13, 0, 15],[11, 3, 5, 8, 2, 15, 10, 13, 14, 1, 7, 4, 12, 9, 6, 0],[12, 8, 2, 1, 13, 4, 15, 6, 7, 0, 10, 5, 3, 14, 9, 11],[7, 15, 5, 10, 8, 1, 6, 13, 0, 9, 3, 14, 11, 4, 2, 12],[5, 13, 15, 6, 9, 2, 12, 10, 11, 7, 8, 1, 4, 3, 14, 0],[8, 14, 2, 5, 6, 9, 1, 12, 15, 4, 11, 0, 13, 10, 3, 7],[1, 7, 14, 13, 0, 5, 8, 3, 4, 15, 10, 6, 9, 12, 11, 2]]


def getLastRow(x):
    return 0xF & x
def getRowWithIndex(x,idx):
    return 0xF  & (x >> (idx * 4))
def getRowWithIndex8bit(x,idx):
    return 0xFF  & (x >> (idx * 8))
def multyplyTwoElemInField(a,b):
    res = 0
    turn = 0;temp = 0
    while b:
        if b & 0b1:
            temp = a
            for idx in range(turn):
                temp <<= 1
                if temp & limitField:
                    temp ^= HS_POLE
            res ^= temp
        turn += 1
        b >>= 1
    return res
def createTableMultiply():
    for idx1 in range(limitField):
        for idx2 in range(idx1,limitField):
            temp = multyplyTwoElemInField(idx1,idx2)
            TableMultiplyOfField[idx1][idx2] = temp
            TableMultiplyOfField[idx2][idx1] = temp
            if temp == 1:
                TableInverseElement[idx1] = idx2
                TableInverseElement[idx2] = idx1
def __CreateTables():
    createTableMultiply()           



############### 64 bit ######################

def T(a):
    res = 0
    temp = 0
    for idx1 in range(8):
        temp = getRowWithIndex(a,idx1)
        temp = PiTable[idx1][temp]
        temp <<= (idx1 * 4)
        res ^= temp
    return res

def g(k,a):
    return (((T(k + a) << 11) ^ ((T(k + a) >> 21) & 0x7ff)) & 0xffffffff)

def G(k,a1,a0):
    return a0,(g(k,a0) ^ a1)

def GStar(k,a1,a0):
    return ((g(k,a0) ^ a1) << 32 ) ^ a0

def encrypt(k,a):
    a1,a0 = a >> 32,a & 0xffffffff
    #print(hex(a1))
    #print(hex(a0))
    k_temp = 0
    # create Keys
    arrKeys = []
    for idx in range(8):
        arrKeys.append(k&0xffffffff)
        k >>= 32
    for idx in range(24):
        k_temp = arrKeys[7-idx%8]
        ##print(hex(k_temp))
        #a >>=8
        a1,a0 = G(k_temp,a1,a0)
        #print(hex(a1),end=",")
        #print(hex(a0))
    for idx in range(7):
        k_temp = arrKeys[idx]
        ##print(hex(k_temp))
        #a >>=8
        a1,a0 = G(k_temp,a1,a0)
        #print(hex(a1),end=",")
        #print(hex(a0))
    return GStar(arrKeys[-1],a1,a0)
    
########### decrypt ############

def decrypt(k,a):
    a1,a0 = a >> 32,a & 0xffffffff
    #print(hex(a1))
    #print(hex(a0))
    k_temp = 0
    # create Keys
    arrKeys = []
    for idx in range(8):
        arrKeys.append(k&0xffffffff)
        k >>= 32
    for idx in range(8):
        k_temp = arrKeys[7-idx]
        a1,a0 = G(k_temp,a1,a0)
    for idx in range(23):
        k_temp = arrKeys[idx%8]
        ##print(hex(k_temp))
        #a >>=8
        a1,a0 = G(k_temp,a1,a0)
        #print(hex(a1),end=",")
        #print(hex(a0))
    return GStar(arrKeys[-1],a1,a0)
__CreateTables()

k = 0xffeeddccbbaa99887766554433221100f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff
a = 0xfedcba9876543210
tt = encrypt(k,a)
print(hex(tt))
tt = decrypt(k,tt)
print(hex(tt))