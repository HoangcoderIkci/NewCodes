# In ra bảng chữ cái tiếng Nga
alphaBet = ["А","Б","В","Г","Д","Е","Ж","З","И","К","Л","М","Н","О","П","Р","С","Т","У","Ф","Х","Ц","Ч","Ш","Щ","Ь","Ы","Э","Ю","Я"]
gammas = ["Е","Т","Ь"]
# gammas = ["Ц","Ф","Р"]
text = "ДДЗЗЬЛШХНЭДДАРЬТЧГНЗААЛЭРЛЗИЭЭ"
# text ="ХЩВГДФЦЭЖЫЯШТЩЬЭЗЩХХИЦАЯВВСЖЦЫ"
#Ц Ф РИ Т Б   ЕТЬ
lenAlphaBet = len(alphaBet)
def findIdx(alphaBet,x):
    for idx in range(len(alphaBet)):
        if alphaBet[idx] == x:
            return idx
    return -1

for g in gammas:
    idx_g = findIdx(alphaBet,g)
    for t in text:
        idx_t = findIdx(alphaBet,t)
        temp = (idx_t - idx_g) % lenAlphaBet
        print(alphaBet[temp],end=" ")
    print()