from fractions import Fraction

def euc_ext(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = euc_ext(b % a, a)
        return (g, x - (b // a) * y, y)

def phan_ra_eN(e, N):
    # Trả về dãy các nghiệm liên tục của e/N
    a = e // N
    yield a
    while e % N != 0:
        e, N = N, e % N
        a = e // N
        yield a

def tinh_phan_so_phu_hop(phan_ra):
    # Tính toán và trả về các phân số phù hợp từ dãy nghiệm liên tục
    m, n = 0, 1
    for a in reversed(list(phan_ra)):
        m, n = n, a*n + m
    return Fraction(m, n)

# Ví dụ sử dụng
e = 65537
N = 3233 # Giả sử đây là sản phẩm của hai số nguyên tố p và q

phan_ra_list = list(phan_ra_eN(e, N))
print("Dãy nghiệm liên tục:", phan_ra_list)

phan_so_phu_hop = tinh_phan_so_phu_hop(phan_ra_list)
print("Phân số phù hợp:", phan_so_phu_hop)
