#include <iostream>
#include <vector>
#include <algorithm> // For std::find
#include <cmath>
using namespace std;

const int FIELD_SIZE = 16;       // số lượng phần tử trong trường hữu hạn
const int CHAR_SIZE = 2;         // character
const int POLYNOMIAL_DEGREE = 4; // bậc đa thức f
int LIMIT_VALUE = 0;             // giới hạn dùng cho phép dịch bit vòng ; với t = 4 tương ứng với 0b1111 = 0xF
int primitive_polynomial = 19;   // tương ứng với x^4 + x + 1

std::vector<std::vector<int>> multiplicationTable(FIELD_SIZE, std::vector<int>(FIELD_SIZE, 0));
std::vector<int> inverseArray(FIELD_SIZE, 0);      // tại vị trí x là nghịch đảo của x
std::vector<int> powerSupportArray(FIELD_SIZE, 0); // tại vị trí i là giá trị của x^i
std::vector<std::vector<int>> powerTable;          // tại vị trí[x][i]  là x^i

// Phép nhân hai phần tử trong trường hữu hạn
int multiply(int a, int b)
{
    int tempA = a;
    int tempB = b;
    int result = 0;
    int highestBit = (1 << POLYNOMIAL_DEGREE);
    while (tempB != 0)
    {
        if (tempB & 0x1)
        {
            result ^= tempA;
        }
        tempA <<= 1;
        tempB >>= 1;
        if (tempA & highestBit)
        {
            tempA ^= primitive_polynomial;
        }
    }
    return result;
}

// Tạo bảng nhân
void createMultiplicationTable()
{
    for (int i = 0; i < FIELD_SIZE; ++i)
    {
        for (int j = i; j < FIELD_SIZE; ++j)
        {
            int temp = multiply(i, j);
            multiplicationTable[i][j] = temp;
            multiplicationTable[j][i] = temp;
            if (temp == 1)
            {
                inverseArray[i] = j;
                inverseArray[j] = i;
            }
        }
    }
}

// Tạo bảng lũy thừa
void createPowerTable()
{
    powerSupportArray[0] = 1;
    int temp = 2;
    for (int idx1 = 1; idx1 < FIELD_SIZE; ++idx1)
    {
        powerSupportArray[idx1] = temp;
        temp = multiplicationTable[2][temp];
    }
    std::vector<int> tempVector;
    powerTable.push_back(std::vector<int>(FIELD_SIZE, 0));
    powerTable.push_back(std::vector<int>(FIELD_SIZE, 1));
    powerTable.push_back(powerSupportArray);
    for (int idx1 = 3; idx1 < FIELD_SIZE; ++idx1)
    {
        temp = idx1;
        tempVector.clear();
        tempVector.push_back(1);
        tempVector.push_back(temp);
        int index_temp = std::find(powerSupportArray.begin(), powerSupportArray.end(), temp) - powerSupportArray.begin();
        for (int idx2 = 2; idx2 < FIELD_SIZE; ++idx2)
        {
            temp = (idx2 * index_temp) % (FIELD_SIZE - 1);
            tempVector.push_back(powerSupportArray[temp]);
        }
        powerTable.push_back(tempVector);
    }
}

// Khởi tạo bảng nhân và bảng lũy thừa
void initializeTables()
{
    createMultiplicationTable();
    createPowerTable();
    powerTable[0][0] = 1;
}

// Phép dịch bit vòng
int circularShift(int X, int r)
{
    r %= POLYNOMIAL_DEGREE;
    return (X >> POLYNOMIAL_DEGREE - r) ^ (X << r) & (LIMIT_VALUE);
}

// Thay đổi giới hạn
void changeLimit(int t)
{
    LIMIT_VALUE = (1 << t) - 1;
}

int F(int x, int b, int r)
{
    return circularShift((x + b) % FIELD_SIZE, r);
}

// Tạo bảng giá trị hàm F
std::vector<int> createFTable(int b)
{
    int valFunc = 0;
    int r = 2;
    std::vector<int> functionValues;
    int binary_x = 0;
    for (int idx1 = 0; idx1 < FIELD_SIZE; ++idx1)
    {
        valFunc = F(idx1, b, r);
        functionValues.push_back(valFunc);
        binary_x = idx1;
        std::cout << binary_x << "  " << valFunc << std::endl;
    }
    return functionValues;
}

// Tìm hệ số của hàm F
std::vector<int> findFCoefficients(std::vector<int> &functionValues)
{
    int coeff = 0;
    std::vector<int> coefficients;
    int temp1 = 0;
    for (int deg = 0; deg < FIELD_SIZE; ++deg)
    {
        coeff = 0;
        for (int elem = 0; elem < FIELD_SIZE; ++elem)
        {
            temp1 = multiplicationTable[functionValues[elem]][powerTable[elem][FIELD_SIZE - 1 - deg]];
            coeff ^= temp1;
        }
        coefficients.push_back(coeff);
    }
    return coefficients;
}

// Tìm hệ số của hàm F (phiên bản 2)
std::vector<int> findFCoefficientsVersion2(std::vector<int> &functionValues)
{
    int coeff = 0;
    std::vector<int> coefficients;
    int temp1 = 0;
    coefficients.push_back(functionValues[0]);
    for (int deg = 0; deg < FIELD_SIZE - 1; ++deg)
    {
        coeff = 0;
        for (int elem = 0; elem < FIELD_SIZE; ++elem)
        {
            temp1 = multiplicationTable[functionValues[elem]][powerTable[elem][FIELD_SIZE - 2 - deg]];
            coeff ^= temp1;
        }
        coefficients.push_back(coeff);
    }
    return coefficients;
}

// Tính giá trị hàm F tại một giá trị x
int FValueAt(std::vector<int> &hsCoefficients, int a)
{
    int result = 0;
    int temp = 1;
    for (size_t idx = 0; idx < hsCoefficients.size(); ++idx)
    {
        result ^= multiplicationTable[hsCoefficients[idx]][temp];
        temp = multiplicationTable[temp][a];
    }
    return result;
}

// In ra bảng giá trị
void printTables()
{
    // bảng nhân:

    std::cout << "Bảng nhân" << std::endl;
    for (const auto &row : multiplicationTable)
    {
        for (const auto &element : row)
        {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
    // bảng lũy thừa:

    std::cout << "Bảng lũy thừa" << std::endl;
    for (const auto &row : powerTable)
    {
        for (const auto &value : row)
        {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
}
int main()
{
    initializeTables();             // Khởi tạo bảng nhân và bảng lũy thừa
    changeLimit(POLYNOMIAL_DEGREE); // Thay đổi giới hạn
    printTables();
    std::vector<int> functionValues = createFTable(10);                        // Tạo bảng giá trị hàm F
    std::vector<int> coefficients = findFCoefficientsVersion2(functionValues); // Tìm hệ số của hàm F
    int i = 0;
    int t = 0;
    std::cout << "Hệ số hàm f(X) : " << std::endl;
    for (const auto &coeff : coefficients)
    {
        std::cout << std::hex << coeff << "x^" << i << " + ";
        ++i;
        t ^= coeff;
    }
    return 0;
}