mod = 3
divisor = x**9 - x**7 + x**5 - x**2 + 1
dividend = x**4 - x**3 - x - 1
n = 9
m = 4
n-m = 5
d = 4, vì n = 9
k = 3
f^-1 = x**9 - x**7 + x**4 - x**2 + 1
g^-1 = -x**4 - x**3 - x + 1

P = P(2 - Pg)
i = 0
P_0 = 1

i = 1
P_1 =x**3 + x + 1 = x + 1 (x^2)

i = 2
P_2 =x**6 - x**3 + x**2 + x + 1 = - x**3 + x**2 + x + 1 (x^4) 

i = 3 
P_3 = x**10 - x**9 + x**4 - x**3 + x**2 + x + 1 =  x**4 - x**3 + x**2 + x + 1 (x^8)  H(x)

Q_inv = F_iv * H = - x**5 + x**4 + x**3 + x + 1 (mod x^6)
Q_inv = x**13 - x**12 - x**10 + x**7 - x**5 + x**4 + x**3 + x + 1 = - x**5 + x**4 + x**3 + x + 1 (mod x^6)

R = -x**2 







Kết quả phép chia:
Thương: Poly(x**5 + x**4 + x**2 + x - 1, x, modulus=3)
Dư: Poly(x**2, x, modulus=3)