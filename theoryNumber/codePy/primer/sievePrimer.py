# Python program to print all
# primes smaller than or equal to
# n using Sieve of Eratosthenes
def SieveOfEratosthenes(n):
    prime = [True for i in range(n+1)]
    p = 2
    res = []
    while (p * p <= n):
        if (prime[p] == True):
            for i in range(p * p, n+1, p):
                prime[i] = False
        p += 1
    for p in range(2, n+1):
        if prime[p]:
            res.append(p)
    print(res)
    return res
def F(coefficients:list,x):
    res = 0
    for c in range(len(coefficients)):
        res+= (x**c) * coefficients[c]
    return res

# giải phương trình F(x) = 0 mod(p)

# Driver code
B = 6
F_B = SieveOfEratosthenes(B)
coefficients = [-31,0,1]
