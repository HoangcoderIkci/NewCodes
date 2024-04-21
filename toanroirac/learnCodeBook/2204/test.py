def pop(x) :
    print(hex(x))
    n = (x >> 1) & 0x77777777; #// Подсчет битов 
    print(hex(n))
    x = x - n; # в 4-битовых 
    print(hex(x))
    n = (n >> 1) & 0x77777777; #// полях
    print(hex(n))
    x = x - n; 
    print(hex(x))
    n = (n >> 1) & 0x77777777; 
    print(hex(n))
    x = x - n; 
    print(hex(x))
    x = (x + (x >> 4)) & 0x0F0F0F0F; #// Вычисление сумм
    print(hex(x))
    x = x * 0x01010101; #// Сложение байтов
    print(hex(x))
    return (x >> 24)&0xff; 
def pop2(x):
    count = 0
    while x:
        x&=(x-1)
        count+=1
    return count
T = pop2(0x87654321)
print(hex(T))

