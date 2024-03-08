CHAR = 2
HS_POLE = 451
sizeFiled = 8
limitField = (1 << sizeFiled)
TableMultiplyOfField = [[0]*limitField for i in range(limitField)]
TableInverseElement = [0 for i in range(limitField)]
#PiTable = [ 252,238,221,17,207,110,49,22,251,196, 250, 218, 35, 197, 4, 77, 233,119, 240, 219,147,46,153,186, 23, 54, 241. 187, 20, 205, 95, 193, 249, 24, 101,90, 226, 92, 239, 33, 129, 28, 60, 66, 139, 1, 142, 79, 5, 132, 2, 174, 227, 106, 143,160, 6, 11, 237, 152, 127, 212, 211, 31, 235, 52, 44, 81, 234, 200, 72, 171, 242, 42,104, 162, 253, 58, 206, 204, 181, 112, 14, 86, 8, 12, 118, 18, 191, 114, 19, 71, 156,183, 93, 135, 21, 161, 150, 41, 16, 123, 154, 199, 243, 145, 120, 111, 157, 158, 178177, 50, 117, 25, 61, 255, 53, 138, 126, 109, 84, 198, 128, 195, 189, 13, 87, 223245, 36, 169, 62, 168, 67, 201, 215, 121, 214, 246, 124, 34, 185, 3, 224, 15, 236222, 122, 148, 176, 188, 220, 232, 40, 80, 78, 51, 10, 74, 167, 151, 96, 115, 30, 098, 68, 26, 184, 56, 130, 100, 159, 38, 65, 173, 69, 70, 146, 39, 94, 85, 47, 140, 163165, 125, 105, 213, 149, 59, 7, 88, 179, 64, 134, 172, 29, 247, 48, 55, 107, 228, 136,217, 231, 137, 225, 27, 131, 73, 76, 63, 248, 254, 141, 83, 170, 144, 202, 216, 133,97, 32, 113, 103, 164, 45, 43, 9, 91, 203, 155, 37, 208, 190, 229, 108, 82, 89, 166,116, 210, 230, 244, 180, 192, 209, 102, 175, 194, 57, 75, 99, 182]
PiTable = [252,238,221,17,207,110,49,22,251,196, 250, 218, 35, 197, 4, 77,233,119, 240, 219,147,46,153,186,23, 54, 241,187,20, 205, 95, 193, 249, 24, 101,90, 226, 92, 239, 33, 129, 28, 60, 66, 139, 1, 142, 79, 5, 132, 2, 174, 227, 106, 143,160, 6, 11, 237, 152, 127, 212, 211, 31, 235, 52, 44, 81, 234, 200, 72, 171, 242, 42,104, 162, 253, 58, 206, 204, 181, 112, 14, 86, 8, 12, 118, 18, 191, 114, 19, 71, 156,183, 93, 135, 21, 161, 150, 41, 16, 123, 154, 199, 243, 145, 120, 111, 157, 158, 178,177, 50, 117, 25, 61, 255, 53, 138, 126, 109, 84, 198, 128, 195, 189, 13, 87, 223,245, 36, 169, 62, 168, 67, 201, 215, 121, 214, 246, 124, 34, 185, 3, 224, 15, 236,222, 122, 148, 176, 188, 220, 232, 40, 80, 78, 51, 10, 74, 167, 151, 96, 115, 30, 0,98, 68, 26, 184, 56, 130, 100, 159, 38, 65, 173, 69, 70, 146, 39, 94, 85, 47, 140, 163,165, 125, 105, 213, 149, 59, 7, 88, 179, 64, 134, 172, 29, 247, 48, 55, 107, 228, 136,217, 231, 137, 225, 27, 131, 73, 76, 63, 248, 254, 141, 83, 170, 144, 202, 216, 133,97, 32, 113, 103, 164, 45, 43, 9, 91, 203, 155, 37, 208, 190, 229, 108, 82, 89, 166,116, 210, 230, 244, 180, 192, 209, 102, 175, 194, 57, 75, 99, 182]
st = set(PiTable)
# tạo mảng nghịch đảo của Pi để tí tạo S nghịch đảo.
inversePiTable = [] 
for idx in range(256):
    for idx2 in range(256):
        if PiTable[idx2] == idx:
            inversePiTable.append(idx2)
     
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

def PiTransformation(elem):
    return PiTable[elem]
def linearTransformation(a):
    table_coefficients = [1,148,32,133,16,194,192,1,251,1,192,194,16,133,32,148]
    res = 0
    for idx in range(16):
        res^= TableMultiplyOfField[table_coefficients[idx]][getRowWithIndex8bit(a,idx)]
    return res

def X(k,a):
    return k^a
def S(a):
    res = 0
    for idx1 in range(16):
        temp = getRowWithIndex8bit(a,idx1)
        temp = PiTransformation(temp) 
        temp = temp << (idx1 * 8)
        res ^= temp
    return res

def R(a):
    a_new = linearTransformation(a)
    a >>= 8
    a ^= a_new << 15 * 8
    return a

def L(a):
    for idx1 in range(16):
        a = R(a)
    return a

def F(k,a1,a0):
    a0 = L(S(X(k,a1))) ^ a0
    return a0,a1
    
def createC(k1,k2):
    arrayKeys = [0]*11
    arrayKeys[1] = k1
    arrayKeys[2] = k2
    C = 0
    for idx1 in range(1,5):
          # tạo C
        a1,a2 = arrayKeys[2*idx1-1],arrayKeys[2*idx1]
        for idx2 in range(1,9):
            C = L(8*(idx1-1)+idx2)
            #print(hex(C))
            a1,a2 = F(C,a1,a2)
            #print(hex(a1))
            #print(hex(a2))
        arrayKeys[2*idx1+1] = a1
        arrayKeys[2*idx1+2] = a2
    return arrayKeys

def encrypt(a,arrKeys):
    for idx in range(1,10):
        a = L(S(X(arrKeys[idx],a)))
    return X(arrayKeys[-1],a)

############ decryption ###########
def reversR(a):
    a_last = getRowWithIndex8bit(a,15)
    #a_new = linearTransformation(a)
    a <<= 8
    a &= 0xffffffffffffffffffffffffffffffff 
    a ^= linearTransformation(a^a_last)
    return a
def reversL(a):
    for idx in range(16):
        a = reversR(a)
    return a
def reverS(a):
    res = 0
    for idx1 in range(16):
        temp = getRowWithIndex8bit(a,idx1)
        #temp = PiTransformation(temp) 
        temp = inversePiTable[temp]
        temp = temp << (idx1 * 8)
        res ^= temp
    return res


    
__CreateTables()

# variable = 0xd456584dd0e3e84cc3166e4b7fa2890d
# res = L(variable)
# print(hex(res))

K = 0x8899aabbccddeeff0011223344556677fedcba98765432100123456789abcdef
K1 = 0x8899aabbccddeeff0011223344556677
K2 = 0xfedcba98765432100123456789abcdef
arrP = [0x1122334455667700ffeeddccbbaa9988,0x00112233445566778899aabbcceeff0a,0x112233445566778899aabbcceeff0a00,0x2233445566778899aabbcceeff0a0011]
a = 0x1122334455667700ffeeddccbbaa9988
arrayKeys = createC(K1,K2)
for idx1 in arrP:
    result = encrypt(idx1,arrayKeys)
    print(hex(result))
    


b = 0x7f679d90bebc24305a468d42b9d4edcd
def decrypt(b,arrKeys):
    for idx in range(9):
        #print(hex(reversL(X(arrKeys[10-idx],b))))
        b = reverS(reversL(X(arrKeys[10-idx],b)))
    b = X(arrayKeys[1],b)
    return b
pltext = decrypt(b,arrayKeys)
print(hex(pltext))



################ nâng cấp tìm MAC (128) #################
K1_K2_support = []
def e_K(a):
    return encrypt(a,arrayKeys)
def createK1K2_128(r):
    if (r >> 127)&0b1:
        k1 = (r <<1) ^ 0b10000111 #(Bn = 128)
    else:
        k1 = r << 1
    if (k1 >> 127)&0b1:
        k2 = (k1 <<1) ^ 0b10000111 #(Bn = 128)
    else:
        k2 = k1 << 1
    K1_K2_support.append(k1& 0xffffffffffffffffffffffffffffffff)
    K1_K2_support.append(k2& 0xffffffffffffffffffffffffffffffff)
def findMAC(P,num_q):
    R = e_K(0)

    P_temp = 0
    createK1K2_128(R)
    for i in K1_K2_support:
        print(hex(i))
    # create C
    arrC = [0]
    for idx1 in range(1,num_q):
        P_temp = P[idx1-1]
        arrC.append(e_K(P_temp^arrC[idx1-1]))
    # find MAC
    P_temp = e_K(P[-1]^arrC[-1]^K1_K2_support[0])
    print(hex(P_temp >> 64))
    
    
findMAC(arrP,4)
    
    