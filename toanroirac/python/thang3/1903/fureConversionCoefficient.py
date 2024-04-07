from math import log2
import pyopencl as cl
import numpy as np
import time

glo_n = 4
glo_length = 1 << glo_n

def table1():
    """
    bảng (-1)^(ab)
    """ 
    size_temp = 1 << glo_n 
    tableSupport = [[0] * size_temp for i in range(size_temp)]
    for a in range(size_temp):
        for b in range(a,size_temp):
            c = 0
            a_ = a
            b_ = b
            while a_:
                c^= (a_&0b1)&b_
                a_ >>= 1
                b_ >>= 1
            if c &0b1:   
                tableSupport[a][b] = tableSupport[b][a] = -1
            else:
                tableSupport[a][b] = tableSupport[b][a] = 1
    return tableSupport
def supportsFunction(lst_coefficients : list,idx1):
    if idx1 == glo_n:
        return
    half_len = 1 << idx1
    full_len = half_len << 1
    num_turns = glo_length // full_len
    for idx2 in range(num_turns):
        for idx3 in range(half_len):
            lst_coefficients[idx2 * full_len+half_len+idx3] ^= lst_coefficients[idx2 * full_len+idx3] 
    #print(lst_coefficients)
    supportsFunction(lst_coefficients,idx1+1)
def fastFindCoefficientsZhegalkin2(lst_coefficients : list):
    res = [x for x in lst_coefficients]
    supportsFunction(res,0)
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
        print(res)
    # in ra kết quả
    printCoefficientsZhegalkin(res,length=length,k=k)
    return res
def printCoefficientsReal(res,length,k):
    for idx1 in range(0,length):
        temp = res[idx1]
        if temp:        
            bina = idx1
            count = k
            print(f"{temp}*",end="")
            while(bina):
                if bina&0b1:
                    print(f"x{count}",end="")
                bina >>=1
                count-=1
            print("",end=" + ")
    print()
def fastFindCoefficientsReal(lst_coefficients : list):
    length = len(lst_coefficients)
    k = int(log2(length))
    res = [x for x in lst_coefficients]
    for idx1 in range(k):
        half_len = 1 << idx1
        full_len = half_len << 1
        num_turns = length // full_len
        for idx2 in range(num_turns):
            for idx3 in range(half_len): 
                res[idx2 * full_len+half_len+idx3] -= res[idx2 * full_len+idx3]   # y - x
                #res[idx2 * full_len+half_len+idx3] = res[idx2 * full_len+idx3] - res[idx2 * full_len+half_len+idx3]
        print(res)
    # in ra kết quả
    printCoefficientsReal(res,length=length,k=k)
    return res
def calcCoefficentsFourier(trustable,supTable):
    coefficients = []
    arrNotNullIndex = []
    for id1 in range(len(trustable)):
        if trustable[id1]:
            arrNotNullIndex.append(id1)
    for id1 in range(len(trustable)):
        c = 0
        for col in arrNotNullIndex:
            c+= supTable[id1][col]
        coefficients.append(c)
    return coefficients
def convertToBinary(number,length):
    binary = bin(number)[2:]
    bi = [int(x) for x in binary]
    binary = ([0] * (length - len(bi))) + bi
    return binary
def printCoefficientsFourier(res,length,n):
    for idx1 in range(0,length):
            temp = res[idx1]
            if temp:        
                bina = idx1
                count = n
                print(f"{temp}*(-1)^(",end="")
                while(bina):
                    if bina&0b1:
                        if bina !=1:
                            print(f"x{count}",end=" + ")
                        else:
                            print(f"x{count}",end="")
                    bina >>=1
                    count-=1
                print(")",end="+")
            print()
        
def fastFourierTransform(trustable):
    """tim he so cua bien doi fourier"""
    length = len(trustable)
    n = int(log2(length))
    length = len(trustable)
    k = int(log2(length))
    res = [x for x in trustable]
    pow_temp = 1
    for idx1 in range(k):
        half_len = 1 << idx1
        full_len = half_len << 1
        num_turns = length // full_len
        for idx2 in range(num_turns):
            for idx3 in range(half_len):
                t1 = (res[idx2 * full_len+idx3] + res[idx2 * full_len+half_len+idx3]) / 2
                t2 = (res[idx2 * full_len+idx3] - res[idx2 * full_len+half_len+idx3]) / 2
                res[idx2 * full_len+idx3] = t1
                res[idx2 * full_len+half_len+idx3] = t2
        res_temp = [x * (1 << pow_temp) for x in res]
        pow_temp+=1
        print(res_temp)
    # in ra kết quả
    printCoefficientsFourier(res,length,n)
    return res

def printCoefficientsFourier(coeffWalshAdamard,length,n):
    for idx1 in range(0,length):
        temp = coeffWalshAdamard[idx1]
        if temp:        
            bina = idx1
            count = n
            print(f"{temp}*(-1)^(",end="")
            while(bina):
                if bina&0b1:
                    if bina !=1:
                        print(f"x{count}",end="+")
                    else:
                        print(f"x{count}",end="")
                bina >>=1
                count-=1
            print(")",end="+")
    print()
def fastFindWalshAdamard(trustable):
    length = len(trustable)
    n = int(log2(length))
    trustable2 = []
    for elem in trustable:
        if elem:
            trustable2.append(-1)
        else:
            trustable2.append(1)
    print(trustable2)
    coeffWalshAdamard = fastFourierTransform(trustable2)
    #coeffWalshAdamard = [1-2*coeffFourier[0]]
    # in ra kết quả
    printCoefficientsFourier(coeffWalshAdamard,length,n)
    return coeffWalshAdamard   
def selectFunction(number,trustable):
    lst = [fastFindCoefficientsZhegalkin,fastFindCoefficientsReal,fastFourierTransform,fastFindWalshAdamard]
    return lst[number](trustable)

str_temp = "0101001101101001"
table = [int(x) for x in str_temp]

#table = [x&0b1 for x in range(glo_length)]
print(table)

# arr1 = [1,1,0,1,1,1,1,0] 
#tableSupport = table1()
c = selectFunction(0,table)
print(c)

# start_time_gpu = time.time()   
# fastFindCoefficientsZhegalkin(table)
# end_time_gpu = time.time()
# print("Thời gian thực thi trên GPU:", end_time_gpu - start_time_gpu)
