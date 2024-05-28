import numpy as np



def createArrayMultModule(module):
    temp = 0
    arrMultiple2 = [[0] * module for i in range(module)]
    arrInverseSubtraction2 = [0] * module
    for i in range(module):
        for j in range(i, module):
            temp = (i * j) % module
            arrMultiple2[i][j] = temp
            arrMultiple2[j][i] = temp
            if temp == 1:
                arrInverseSubtraction2[i] = j
                arrInverseSubtraction2[j] = i
    return arrMultiple2, arrInverseSubtraction2


# module = 5
# mt1 = np.array([[0, 1, 0, 1], [1, 0, 1, 0], [0, 1, 0, 1], [1, 0, 1, 0]])


def changeToBacThang(mt1):
    rank = 0
    lst_ind_basic = []
    # Lấy kích thước số hàng và cột của ma trận
    num_rows, num_cols = mt1.shape
    for col in range(num_cols):
        for row in range(rank, num_rows):
            if mt1[row][col]:
                lst_ind_basic.append(col)
                if row != rank:
                    mt1[row], mt1[rank] = mt1[rank], mt1[row]
                hs_nghich_dao = arrInverseSubtraction[mt1[rank][col]]
                # đưa hệ số về 1
                for id in range(col, num_cols):
                    mt1[rank][id] = arrMultiple[mt1[rank][id]][hs_nghich_dao]
                # ap null các rows ở dưới row rank:
                for idr in range(rank + 1, num_rows):
                    if mt1[idr][col]:
                        hs_temp = mt1[idr][col]
                        for idcl in range(col, num_cols):
                            mt1[idr][idcl] = (
                                mt1[idr][idcl] ^ arrMultiple[mt1[rank][idcl]][hs_temp]
                            )
                rank += 1
    print(mt1)
    # đưa về dạng chuẩn
    temp_r = rank - 1
    lst_temp_id_bs = lst_ind_basic
    lst_temp_id_bs.reverse()
    for id_bs in lst_temp_id_bs:
        for id_r in range(0, temp_r):
            if mt1[id_r][id_bs]:
                hs_temp = mt1[id_r][id_bs]
                mt1[id_r][id_bs] = 0
                for id_cl in range(id_bs + 1, num_cols):
                    mt1[id_r][id_cl] = (
                        mt1[id_r][id_cl] ^ arrMultiple[mt1[temp_r][id_cl]][hs_temp]
                    )
                print(mt1)
        temp_r -= 1
    print(mt1)

    print("\n################################################################\n")
    # tìm ind phần tử khác 0 cuối cùng
    col_last = mt1[:, -1]
    # for id in range(len(col_last)):
    #     if col_last[num_rows - 1 - id] != 0:
    #         id_last_non_zero = num_rows - id
    #         break
    # print(id_last_non_zero)
    if num_cols - 1 in lst_ind_basic:
        print("system not nghiem\n")
    else:
        if rank == min(num_rows, num_cols - 1):
            print("system with ! nghiem : ")
            print(mt1[:, -1])
        else:
            print("system with > 1 nghiem : ")
            print("basic nghiem : \n")
            set_all = set(range(num_cols - 1))
            # Loại bỏ các số có trong ls1 khỏi tập hợp
            setIndexNotBasic = set_all - set(lst_ind_basic)
            # res_bs = np.array()
            for id in setIndexNotBasic:
                elem = mt1[:, id]
                for j in range(id):
                    elem[j] = elem[j] ^ col_last[j]

                # elem = (col_last - elem) % module
                elem[id] = 1
                print(elem)


def changeToBacThangModule(mt1, arrMultiple2, arrInverseSubtraction2, module):
    # print(mt1)
    rank = 0
    lst_ind_basic = []
    # Lấy kích thước số hàng và cột của ma trận
    num_rows, num_cols = mt1.shape
    for col in range(num_cols):
        for row in range(rank, num_rows):
            if mt1[row][col]:
                lst_ind_basic.append(col)
                if row != rank:
                    temp_row = mt1[row].copy()
                    # print(temp_row)
                    mt1[row] = mt1[rank]
                    # print(temp_row)
                    mt1[rank] = temp_row
                    print(mt1, end="\n\n")
                    # mt1[row], mt1[rank] = mt1[rank], mt1[row]
                    # print(mt1)
                hs_nghich_dao = arrInverseSubtraction2[mt1[rank][col]]
                # đưa hệ số về 1
                for id in range(col, num_cols):
                    mt1[rank][id] = arrMultiple2[mt1[rank][id]][hs_nghich_dao]
                # ap null các rows ở dưới row rank:
                for idr in range(rank + 1, num_rows):
                    if mt1[idr][col]:
                        hs_temp = mt1[idr][col]
                        for idcl in range(col, num_cols):
                            mt1[idr][idcl] = (
                                mt1[idr][idcl] - arrMultiple2[mt1[rank][idcl]][hs_temp]
                            ) % module
                print(mt1, end="\n\n")
                rank += 1
    # mt1 = mt1[0:rank, 0 : rank + 1]

    # print(mt1, end="\n\n")
    # num_cols = rank + 1
    # rum_rows = rank
    # print()
    # đưa về dạng chuẩn
    temp_r = rank - 1
    lst_temp_id_bs = lst_ind_basic.copy()
    lst_temp_id_bs.reverse()
    # print("lst bs", lst_ind_basic)
    for id_bs in lst_temp_id_bs:
        for id_r in range(0, temp_r):
            if mt1[id_r][id_bs]:
                hs_temp = mt1[id_r][id_bs]
                mt1[id_r][id_bs] = 0
                for id_cl in range(id_bs + 1, num_cols):
                    mt1[id_r][id_cl] = (
                        mt1[id_r][id_cl] - arrMultiple2[mt1[temp_r][id_cl]][hs_temp]
                    ) % module
                print(mt1, end="\n\n")
        temp_r -= 1
    print("\n################################################################\n")
    # tìm ind phần tử khác 0 cuối cùng
    print(mt1, end="\n\n")


# changeToBacThangModule(mt1, 2)





def solveSystemGFZ(matrixA, columnB, mod, arrMultiple2, arrInverseSubtraction2):
    num_rows, num_cols = matrixA.shape
    if num_rows != len(columnB):
        print("num_rows != len(columnB) error!!!")
        return
    # Thêm cột mới vào cuối cùng của mảng
    matrixA = np.append(matrixA, columnB[:, np.newaxis], axis=1)
    # for i in range(num_rows):
    #     np.append(matrixA[i], columnB[i])
    print(matrixA)
    changeToBacThangModule(matrixA, arrMultiple2, arrInverseSubtraction2, module=mod)




if __name__ == "__main__":
    module = 5
    arrMultiple, arrInverseSubtraction = createArrayMultModule(module)
    matrix = np.array([[2, 3, 1,1],
                        [1, 2, 3,1],
                        [1, 1, 2,3],
                        [3, 1, 1,0]
                        ])
    colB2 = np.array([1, 2, 1, 0])
    solveSystemGFZ(matrix,colB2,module,arrMultiple, arrInverseSubtraction)
