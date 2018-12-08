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

    sn.push_back('\0');  // 别忘了哦

    return sn.length();  // 返回 sn 的长度
}

int Manacher()
{
    int len = Init();  // 取得新字符串长度并完成向 sn 的转换
    int max_len = -1;  // 最长回文长度

    int id = 0;
    int mx = 0;

    for (int i = 1; i < len; i++)
    {
        if (i < mx)
            p[i] = min(p[2 * id - i], mx - i);  // 需搞清楚上面那张图含义, mx 和 2*id-i 的含义
        else
            p[i] = 1;

        while (sn[i - p[i]] == sn[i + p[i]])  // 不需边界判断，因为左有'$',右有'\0'
            p[i]++;

        // 我们每走一步 i，都要和 mx 比较，我们希望 mx 尽可能的远，这样才能更有机会执行 if (i < mx)这句代码，从而提高效率
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