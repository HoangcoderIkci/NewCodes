import math

def giai_phuong_trinh_bac_2(a, b, c):
    delta = b**2 - 4*a*c
    if delta > 0:
        x1 = (-b + math.sqrt(delta)) / (2*a)
        x2 = (-b - math.sqrt(delta)) / (2*a)
        return x1, x2
    elif delta == 0:
        x = -b / (2*a)
        return x
    else:
        return False
def Phi(k,d,e):
    return (e*d - 1) // k
def ProperFraction2(e,N):
    N_input = N
    e_input = e
    P = [1,e // N]
    Q = [0,1]
    r = e % N
    A = [e//N]
    e = N
    N = r
    while r :
        A.append(e // N)
        r = e % N
        e = N
        N = r
        P.append(P[-1]*A[-1]+P[-2])
        Q.append(Q[-1]*A[-1]+Q[-2])
        f_n = Phi(P[-1],Q[-1],e_input)
        if f_n < N_input:
            nghiem = giai_phuong_trinh_bac_2(1,-(N_input-f_n)-1,N_input)
            if nghiem:
                if nghiem[0].is_integer() and nghiem[-1].is_integer:
                    print(nghiem)
                    return nghiem
               
        
        
ProperFraction2(1779399043,2796304957)