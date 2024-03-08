size = 4
#define getBitIndex(x, idx) (((x) >> (idx)) & 1)     // get bit tại index
def setBitIndex(x, idx): 
    x |= (1 << (idx))
    return x
def getBitIndex(x, idx):
    return (((x) >> (idx)) & 0b1)
def getHighBit(x):
    return ((x >> (size - 1)) & 0b1)
def getFirstBit(x):
    return x & 0b1
def process1(F):
    len_bit=0
    temp_bit=0
    num_turn=0
    t=0
    len_func = (1 << size)
    t = F
    vec = 0
    
    for idx1 in range(0, len_func):
        if t & 0b1:
            #print("1 ",end="")
            vec+=1
        # else:
        #     print("0 ",end="")
        t >>= 1
    #print()
    for idx1 in range(0, size):
        len_bit = (1 << idx1)
        num_turn = len_func // len_bit
        num_turn >>= 1
        for idx2 in range(0, num_turn):
            for idx3 in range(0, len_bit):
                temp_bit = getBitIndex(F, (idx2 * len_bit * 2 + idx3))
                if temp_bit:
                    F ^= (1 << (idx2 * len_bit * 2 + len_bit + idx3))
    degree = 0
    
    turn = 0; temp=0; temp_degree=0
    for idx1 in range(0, len_func):
        if F & 0b1:
            #print("1 ",end="")
            temp = turn
            temp_degree = 0
            while temp:
                if (temp & 0b1):
                    temp_degree+=1
                temp >>= 1
            if (temp_degree > degree):
                degree = temp_degree

        #else:
            #print("0 ",end="")
        F >>= 1
        turn+=1

    # print()
    # print(f"degree of polynomial = {degree}")
    if (degree==size):
        #for idx in range(10000000):
        print(f"degree = {size}")
    if (vec != (1 << (size - 1))):
        print(f"vec = {vec} khac thuong")
    #// buoc 2 tim bac da thuc
    return degree
def createTable():
    module = 1 << size
    res=0
    flag = 1
    F=0
    tempt = 1
    arrResult = [0] * (size+1)
    for c in range(0,module):
        F = 0
        for set in range(0,module):
            res = (set * c) % module
            flag = getHighBit(res)
            flag <<= set
            F |= flag
        tempt = process1(F)
        if tempt == size - 1 :
            print(f"F = {tempt} , c = {c}")
        arrResult[tempt]+=1
        #print("################################============================################################\n")
    for idx in range(size):
        print(f"degree{idx} : {arrResult[idx]}")


# =================== MAIN =================== #
size = 4




module = 1 << size
for i in range(0,module):
    t = getHighBit(i*3 % module)
    print(t)
createTable()

