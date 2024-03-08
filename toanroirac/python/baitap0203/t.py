# import math
# res = 0
# ls = [7, 9, 11, 13, 15, 0, 2, 4, 6, 8, 10, 12, 14, 1, 3, 5]
# s = 8
# for b in range(s+1):
#    # print()
#     temp  = math.comb(s,b)
#     #res += math.comb(5,b) * ls[b] * (-1)**(5-b)
#     print( temp,end=" , ")






ls = []
for x in range(16):
    #ls.append((12*x + 11*x**2 + 4*x**3 + 14*x**4 + 8*x**5) % 16)
    ls.append((x ** 3) % 16)
print(ls)


#0, 12, 11, 4, 14, 8