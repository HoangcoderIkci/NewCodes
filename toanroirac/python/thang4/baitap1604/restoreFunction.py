
"""_summary_
    chỉnh sửa biến gloN,gloLength,sửa giá trị ban đầu tại dictIn mỗi cặp a,b trong tuple tương ứng với số cột và giá trị
    bài toán chỉ quan tâm đến tính chẵn lẻ.
"""
gloN = 3
gloLength = 1 << gloN
#NameRow = ["0","1","2","3","12","13","23","123"]
NameRow = ["0"]
def recurse(start,k,count,name):
    if count < k:
        for i in range(start,gloN+1):
            name2=name+str(i)
            if count+1==k:
                NameRow.append(name2)
            else:
                recurse(i+1,k,count+1,name2)
    
def createNameRow():
    for k in range(1,gloN+1):
        count = 0
        name=""
        recurse(1,k,count,name)
    print(NameRow)
    
def neighbor(x,id):
    return x^(1 << (gloN-int(id)))
def initTable(typleInit):
    vals = [[-1]*gloLength for x in range(gloLength)]
    for id in range(gloLength):
        vals[0][id] = typleInit[0][1]
    for id,pair in enumerate(typleInit):
        vals[id][pair[0]] = pair[1]
    return dict(zip(NameRow,vals))
def timColDongDang(indexCol,currKey):
    similarKeys = []
    for num in range(gloLength):
        flag = 1
        for s in currKey:
            if (indexCol^num) & (1 << (gloN-int(s))):
                flag = 0
                break
        if flag:
            similarKeys.append(num)
    return similarKeys
def findIndexRowSum(currentKey,idx):
    new_string = ''
    for char in currentKey:
        if char != str(idx):
            new_string += char
    if new_string == '':
        return '0'
    return new_string

def Main():
    #8,4,4,4,4,2,2,2,2,2,2,1,1,1,1,0
    A1 = [1] * gloLength
    #A2 = [8,4,4,4,4,2,2,2,2,2,2,1,1,1,1,0]
    A2 = [4,1,1,1,0,0,0,0]
    dictIn = []
    for id in range(gloLength):
        dictIn.append((0,A2[id]&0b1))
    print("data input: ")
    print(dictIn)
    dictIn = tuple(dictIn)
    #dictIn = ((0,0),(1,1),(0,1),(2,1),(0,0),(1,1),(0,0),(3,1))  # sửa giá trị ban đầu tại đây
    table = initTable(dictIn) 
    flag2 = 0
    #b1 duyệt từng dòng:
    for idx1 in range(1,gloLength):
        used = [0]*gloLength
        # lấy key hiện tại
        currentKey = NameRow[idx1]
        #b1.1 tìm ô chưa được dùng và đã có giá trị khác 1:
        indexCol = 0
        flag2 = 0
        flag = 1
        while flag:
            flag = 0
            if flag2==0:
                for idx2 in range(gloLength):
                        if used[idx2]==0 and table[currentKey][idx2]!=-1:
                            indexCol = idx2
                            used[idx2] = 1
                            flag = 1
                            break
            else:
                flag2 = 0
                flag = 1
            # nếu khác -1 là còn ngược lại là đã dùng hết
            if flag:
                #flag = 0
                valCurrentCol = table[currentKey][indexCol]
                similarKeys = timColDongDang(indexCol,currentKey)
                for key in similarKeys:
                    used[key] = 1
                    table[currentKey][key] = valCurrentCol
            #b1.2 tìm lần lượt từng neighbor của nó
                NextindexCol = indexCol
                for idx3 in currentKey:
                    #b1.2.1 tìm neighbor
                    neighborCol = neighbor(indexCol,idx3)
                    if used[neighborCol] == 0:
                        if flag2 !=1:
                            flag2 = 1
                            NextindexCol = neighborCol
                    #b1.2.2 tìm hàng ở trên bằng tổng của ô hiện tại và neighbor của nó
                        indexRowSum = findIndexRowSum(currentKey,idx3)
                        table[currentKey][neighborCol] = table[indexRowSum][indexCol]^valCurrentCol
                indexCol = NextindexCol
    return table
# Main function

# for row in table:
#     print(row,table[row])
createNameRow()
tab = Main()
print("result table: ")
for key in tab:
    print(key,tab[key])
# print(tab)
# print(tab[NameRow[-1]])

#1, 0, 0, 1, 0, 1, 1, 0,
#0, 1, 1, 0, 1, 0, 0, 1