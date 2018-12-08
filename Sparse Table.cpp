#include <bits/stdc++.h>
using namespace std;

const int N = (int)3e5 + 500, LOGN = 19;
typedef pair<int, int> P;

int n;
int st[LOGN + 1][N], num[N];

void init(){
    for(int i = 0; i < n; i++){
        st[0][i] = num[i];
    }
    for(int lg = 1; lg < LOGN; lg++){
        for(int j = 0; j + (1 << lg) - 1 < n; j++){
            st[lg][j] = min(st[lg-1][j], st[lg-1][j+(1<<(lg-1))]);
        }
    }
}

int rmq(int l, int r){
    int k = mm[r - l + 1];
    return min(st[k][l], st[k][r-(1<<k)+1]);
}

int main(){
	mm[0]=-1;
    for(int i = 1; i < N; i++) mm[i]= (i & (i-1)) == 0 ? mm[i-1] + 1 : mm[i-1];
}
