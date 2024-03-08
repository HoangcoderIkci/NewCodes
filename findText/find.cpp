#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <ctime>

using namespace std;

int findSubstring(char text[], char sub[], int len_text, int len_sub, int start_idx)
{
    if (start_idx + len_sub > len_text)
    {
        return -1;
    }
    bool match = true;
    for (int i = start_idx; i < len_text - len_sub + 1; i++)
    {
        if (text[i] == sub[0])
        {

            match = true;
            for (int j = 0; j < len_sub; j++)
            {
                if (text[i + j] != sub[j])
                {
                    match = false;
                    break;
                }
            }
            if (match)
            {
                cout << "Match found at index " << i << endl;
                return i + 1;
            }
        }
    }
    return -1;
}

int main()
{
    srand(time(NULL));

    char text[] = "Little cat, little cat, little bird, little fish, little turtle cat";
    char pattern[] = "cat";
    const int textLength = sizeof(text) / sizeof(text[0]) - 1;
    const int patternLength = sizeof(pattern) / sizeof(pattern[0]) - 1;
    int idx = 0;
    while (idx != -1)
    {
        idx = findSubstring(text, pattern, textLength, patternLength, idx);
    }
    return 0;
}