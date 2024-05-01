def checkNumber(a,b,callback):
    callback(a+b)
    
def checkParity(a):
    if a&0b1:
        print("Odd")
    else:
        print("Even")
        
def positiveCheck(num):
    if num >0:
        print("Positive")
    else:
        print("Negative")
        
checkNumber(2,5,positiveCheck) 