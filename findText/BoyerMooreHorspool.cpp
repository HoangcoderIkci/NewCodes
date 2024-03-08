#include <iostream>
#include <string>
#include <map>
#include <stdint.h>
#define U16 uint16_t
#define loop(i, a, n) for (int i = a; i < n; i++)
using namespace std;

string table_alphabit_global = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя";
// Создание таблицы сдвига: Функция createShiftTable создаёт таблицу сдвига для определения количества символов, которые можно пропустить при несоответствии. Таблица создаётся на основе шаблона (pattern).

// Функция поиска Horspool: Функция horspoolSearch выполняет поиск шаблона в тексте (text), используя созданную таблицу сдвига. Если шаблон не найден, функция возвращает string::npos.

// Проверка и сдвиг: Во время поиска алгоритм сравнивает шаблон справа налево. При обнаружении несоответствия алгоритм сдвигает позицию проверки в тексте, основываясь на значении из таблицы сдвига или на количестве символов, которые ещё не были проверены в шаблоне.

// Исполнение и результат: В функции main мы выполняем поиск и выводим позицию шаблона в тексте, если он найден.

map<char, U16> createShiftTable(const string &pattern)
{
    U16 patLen = pattern.size();
    map<char, U16> shiftTable;
    // Lặp qua mỗi ký tự trong chuỗi mẫu, trừ ký tự cuối cùng
    loop(i, 0, patLen - 1)
    {
        // Cập nhật bảng dịch chuyển cho mỗi ký tự
        shiftTable[pattern[i]] = patLen - 1 - i;
    }
    loop(i, 0, table_alphabit_global.length())
    {
        // cout << table_alphabit_global[i] << endl;
        if (shiftTable.find(table_alphabit_global[i]) == shiftTable.end())
        {
            shiftTable[table_alphabit_global[i]] = patLen;
        }
    }
    return shiftTable;
}

// Hàm tìm kiếm Horspool
int horspoolSearch(const string &text, const string &pattern)
{
    if (pattern.empty() || text.empty())
        return -1;

    // Tạo bảng dịch chuyển từ chuỗi mẫu
    map<char, U16> shiftTable = createShiftTable(pattern);
    U16 patLen = pattern.size();
    U16 textLen = text.size();

    U16 i = patLen - 1;
    U16 idx;
    // Lặp qua chuỗi văn bản
    while (i < textLen)
    {
        U16 j = patLen - 1;

        // Kiểm tra từng ký tự của chuỗi mẫu từ phải sang trái
        if (text[i] == pattern[j])
        {
            idx = i;
            while (text[i] == pattern[j])
            {
                if (j == 0)
                    return i; // Tìm thấy chuỗi mẫu, trả về vị trí bắt đầu
                --i;
                --j;
            }
            i = idx;
        }
        // Dịch chuyển vị trí kiểm tra trong chuỗi văn bản
        i += shiftTable[text[i]];
    }

    return -1; // Không tìm thấy chuỗi mẫu
}

int main()
{
    string text = "Пример текста для поиска";
    string pattern = "текст";

    int pos = horspoolSearch(text, pattern);

    if (pos != -1)
    {
        cout << "Образец найден на позиции: " << pos << endl;
    }
    else
    {
        cout << "Образец не найден." << endl;
    }

    return 0;
}
