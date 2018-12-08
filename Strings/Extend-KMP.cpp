#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = (int)4e5 + 500;

int Z[MAXN], extend[MAXN];
string t, s;

void getnext(string t)
{
    int a = 0;
    int m = t.length();
    Z[0] = m;
    while(a < m - 1 && t[a] == t[a+1]) a++;
    Z[1] = a;
    a = 1;
    for(int k = 2; k < m; k++)
    {
        int p = a + Z[a] - 1,L = Z[k-a];
        if((k-1) + L >= p)
        {
            int j= (p-k+1) > 0 ? p-k+1 : 0;
            while(k + j < m && t[k+j] == t[j]) j++;
            Z[k] = j;
            a = k;
        }
        else Z[k] = L;
    }
}

void getextend(string s, string t)
{
    int a=0;
    getnext(t);
    int n = s.length();
    int m = t.length();
    int minlen = n < m ? n : m;
    while(a < minlen && s[a] == t[a]) a++;
    extend[0] = a;
    a = 0;
    for(int k = 1; k < n; k++){
        int p = a + extend[a] - 1, L = Z[k-a];
        if((k-1) + L >= p)
        {
            int j = (p-k+1)>0 ? p-k+1 : 0;
            while(k + j < n && j < m && s[k+j] == t[j]) j++;
            extend[k] = j;
            a = k;
        }
        else extend[k] = L;
    }
}

int main(){
    while(cin >> t >> s){
        getextend(s,t);
        string res = "";
        int n = s.length();
        for(int i = 0; i < n; i++){
            if(extend[i] + i == n){
                res = s.substr(i, extend[i]);
                break;
            }
        }
        if(res == "") printf("0\n");
        else cout << res << " " << res.length() << endl;
    }
}