#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <cstdint>
#define P (1 << 31 - 1)
#define base 31
#define U32 unsigned int
#define U64 uint64_t
#define ord(x) (x - '0')
// #define mulBase(x) ()
#define loop(i, n) for (int i = 0; i < n; i++)

using namespace std;

U64 mulBase(U64 x)
{
    U64 res = 0;
    loop(i, 5)
    {
        res += x;
        x <<= 1;
    }
    return res;
}

int gornerScheme(string text)
{
    int result = ord(text[0]);
    loop(i, text.length() - 1)
    {
        result = result * base + ord(text[i + 1]);
    }
    return result;
}

int calculateHash(string text)
{
    return gornerScheme(text) % P;
}

int searchText(string text, string sub_text, int idx_start = 0)
{
    int sub_hash = calculateHash(sub_text);
    int m = sub_text.length();
    U64 base_power_m = pow(base, m - 1);
    base_power_m %= P;
    int len_text = text.length();
    int idx = idx_start;
    if (idx + m >= len_text)
        return -1;

    U64 current_hash = calculateHash(text.substr(idx, m));
    while (1)
    {
        if (current_hash == sub_hash)
        {
            // cout << text.substr(idx, idx + m) << endl;
            if (sub_text == text.substr(idx, m))
            {
                cout << "found element in index : " << idx << endl;
                return idx;
            }
            else
            {
                cout << sub_text << " not equal " << text.substr(idx, m) << endl;
            }
        }
        if (idx + m >= len_text)
            break;
        current_hash = (mulBase(current_hash - ord(text[idx]) * base_power_m) + ord(text[idx + m])) % P;
        idx++;
    }
    return -1;
}

bool check_lengths_subtexts(vector<string> sub_texts)
{
    int len_subtexts = sub_texts[0].length();
    loop(i, sub_texts.size())
    {
        if (sub_texts[i].length() != len_subtexts)
            return false;
    }
    return true;
}

int searchTexts(string text, vector<string> sub_text, int idx_start = 0)
{
    int amount_of_subtexts = sub_text.size();
    if (amount_of_subtexts == 0)
    {
        cout << "lenghts of subtexts is not equal" << endl;
        return -1;
    }
    bool check = check_lengths_subtexts(sub_text);
    if (check == false)
        return -1;
    vector<int> hash_subtexts;
    loop(i, amount_of_subtexts)
    {
        hash_subtexts.push_back(calculateHash(sub_text[i]));
    }
    // int sub_hash = calculateHash(sub_text);
    int m = sub_text[0].length();
    U64 base_power_m = pow(base, m - 1);
    base_power_m %= P;
    int len_text = text.length();
    int idx = idx_start;
    if (idx + m >= len_text)
        return -1;

    U64 current_hash = calculateHash(text.substr(idx, m));
    while (1)
    {
        loop(i1, amount_of_subtexts)
        {
            if (current_hash == hash_subtexts[i1])
            {
                // cout << text.substr(idx, idx + m) << endl;
                if (sub_text[i1] == text.substr(idx, m))
                {
                    cout << "found '" << sub_text[i1] << "' in index : " << idx << endl;
                    return idx;
                }
            }
        }
        if (idx + m >= len_text)
            break;
        current_hash = (mulBase(current_hash - ord(text[idx]) * base_power_m) + ord(text[idx + m])) % P;
        idx++;
    }
    return -1;
}
void findSubstring(string text, string sub_text)
{
    int idx_start = 0;
    while (1)
    {
        idx_start = searchText(text, sub_text, idx_start);
        if (idx_start == -1)
            break;
        idx_start++;
    }
}
void findSubstring(string text, vector<string> subs_text)
{
    int idx_start = 0;
    while (1)
    {
        idx_start = searchTexts(text, subs_text, idx_start);
        if (idx_start == -1)
            break;
        idx_start++;
    }
}
int main()
{
    string text = "apple Awer fruit some apple";
    vector<string> sub_texts = {"apple", "Awers", "fruit"};
    string sub_text = "apple";
    findSubstring(text, sub_texts);
    return 0;
}