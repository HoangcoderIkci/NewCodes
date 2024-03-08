#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#define U64 unsigned long long
#define MAXSIZE 10
int main()
{
    ifstream file("numbers.txt");
    string line;
    int count = 0;
    U64 numbers[MAXSIZE];

    while (getline(file, line))
    {
        // Chuyển đổi chuỗi hex thành số nguyên 64-bit và thêm vào vector
        unsigned long long number = stoull(line, nullptr, 16);
        numbers[count++] = number;
    }
    file.close();
    // In các số ra màn hình
    for (int i = 0; i < count; i++)
    {
        cout << hex << numbers[i] << endl;
    }
    return 0;
}
