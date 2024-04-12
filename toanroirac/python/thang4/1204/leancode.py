x=0b10111100011000110111111011111111
print(x)
def count1(x):
    x = (x&0x55555555) + ((x>>1)&0x55555555)
    x = (x&0x33333333) + ((x>>2)&0x33333333)
    x = (x&0x0f0f0f0f) + ((x>>4)&0x0f0f0f0f)
    x = (x&0x00ff00ff) + ((x>>8)&0x00ff00ff)
    x = (x&0x0000ffff) + ((x>>16)&0x0000ffff)
    print("count =",x)
def fastCountBit(x):
    c = 0
    while x :
        x&=(x-1)
        c+=1
    print("count =",c)
def countNull(x):
    c = 0
    while x!=0x1f :
        x|=(x+1)
        c+=1
    print("count =",5-c)
def pop():
    res = x
    for i in range(1,32):
        res -= x//(1 << i)
    print(res)
countNull(x=5)