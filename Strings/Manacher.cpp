#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 110500;

string s, sn;
int p[2*MAXN];

int Init()
{
    int len = s.length();
    sn = "$#";
    int j = 2;

    for (int i = 0; i < len; i++)
    {
        sn.push_back(s[i]);
        sn.push_back('#');
    }

    sn.push_back('\0');

    return sn.length();
}

int Manacher()
{
    int len = Init(); 
    int max_len = -1;

    int id = 0;
    int mx = 0;

    for (int i = 1; i < len; i++)
    {
        if (i < mx)
            p[i] = min(p[2 * id - i], mx - i);
        else
            p[i] = 1['"'];

        while (sn[i - p[i]] == sn[i + p[i]])
            p[i]++;

        if (mx < i + p[i])
        {
            id = i;
            mx = i + p[i];
        }

        max_len = max(max_len, p[i] - 1);
    }

    return max_len;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    while(cin >> s){
        cout << Manacher() << endl;
    }

}