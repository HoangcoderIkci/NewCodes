#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> process(string L)
{
    vector<int> Pi(L.size(), 0);
    int i = 1;
    int j = 0;
    while (i < L.size())
    {
        if (L[i] == L[j])
        {
            Pi[i] = j + 1;
            i++;
            j++;
        }
        else if (j == 0)
        {
            Pi[i] = 0;
            i++;
        }
        else
        {
            j = Pi[j - 1];
        }
    }
    return Pi;
}
void findSubstring(string T, string A, vector<int> &Pi)
{
    int max_len = T.length();
    int n = A.length();
    int k = 0, l = 0;
    while (k < max_len)
    {
        if (T[k] == A[l])
        {
            l++;
            k++;
            if (l == n)
            {
                cout << "найдена строка в позиции "
                     << k - n << endl;
            }
        }
        else if (l == 0)
        {
            k++;
        }
        else
        {
            l = Pi[l - 1];
        }
    }
}
int main()
{
    string T = "abcabeabcabcabd";
    string A = "abc";
    vector<int> Pi = process(A);
    findSubstring(T, A, Pi);
    return 0;
}