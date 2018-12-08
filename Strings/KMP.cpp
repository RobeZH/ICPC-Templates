#include <bits/stdc++.h>
using namespace std;

const int N = (int)1e6 + 500, M = (int)1e4 + 500;

string s, t;
int f[M];


void getnext(){
    int m = t.length();
    f[0] = 0; f[1] = 0;
    for(int i = 1; i < m; i++){
        int j = f[i];
        while(j && t[i] != t[j]) j = f[j];
        f[i+1] = t[i] == t[j] ? j + 1 : 0;
    }
}

int find(){
    int n = s.length(), m = t.length();
    int res = 0;
    int j = 0;
    for(int i = 0; i < n; i++){
        while(j && t[j] != s[i]) j = f[j];
        if(t[j] == s[i]) j++;
        if(j == m) res ++, j = f[j];
    }
    return res;
}


void solve(){
    scanf("\n%s %s", t, s);
    getnext();
    printf("%d\n", find());

}

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        solve();
    }
}
