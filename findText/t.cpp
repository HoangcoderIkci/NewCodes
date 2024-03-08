#include <iostream>
#include <string>
#include <locale>

int main()
{
    // Khai báo chuỗi kiểu wchar_t
    std::wstring text = L"текст";

    // In từng ký tự của chuỗi
    for (wchar_t ch : text)
    {
        std::wcout << ch << L" ";
    }
    std::wcout << std::endl;
    std::cout << "endl" << std::endl;
    return 0;
}
