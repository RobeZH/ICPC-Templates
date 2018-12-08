#include <bits/stdc++.h>
using namespace std;

const int B = 20;

int dp[10000][B];
int bit[B], b;
int pw2[B];
int A, B;

int get(int rem, int d, bool flag){
    if(rem < 0) return 0;
    if(d == -1) return rem >= 0;
    if(!flag && ~dp[rem][d]) return dp[rem][d];
    int lim = flag ? bit[d] : 9;
    int res = 0;
    for(int i = 0; i <= lim; i++){
        res += get(rem - i * pw2[d], d - 1, flag && lim == i);
    }
    return flag ? res : dp[rem][d] = res;
}

int solve(int x){
    b = 0;
    int t = x;
    while(t > 0){bit[b++] = t % 10; t /= 10;}
    return get(A, b-1, true);
}

