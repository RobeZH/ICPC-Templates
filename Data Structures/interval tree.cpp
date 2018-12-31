#include <bits/stdc++.h>

using namespace std;

const int N = (int)1e5 + 500, LOGN = 20;

int n,q;
int num[N];
int dat[LOGN][N];

void build(int dep, int l, int r){
    if(l == r){dat[dep][l] = num[l]; return ;}
    int mid = (l + r) / 2;
    build(dep + 1, l, mid);
    build(dep + 1, mid + 1, r);
    int j = mid + 1, cur = l;
    for(int i = l; i <= mid; i++){
        while(j <= r && dat[dep+1][j] < dat[dep+1][i]){
            dat[dep][cur++] = dat[dep+1][j++];
        }
        dat[dep][cur++] = dat[dep+1][i];
    }
    while(j <= r) dat[dep][cur++] = dat[dep+1][j++];
}

int query(int ql, int qr, int dep, int l, int r, int val){
    if(r < ql || l > qr) return 0;
    if(ql <= l && r <= qr){
        return int(upper_bound(dat[dep] + l, dat[dep] + r + 1, val) - (dat[dep] + l));
    }
    int mid = (l + r) / 2;
    int LHS = query(ql, qr, dep + 1, l, mid, val);
    int RHS = query(ql, qr, dep + 1, mid + 1, r, val);
    return LHS + RHS;
}


int main(){
    int T;
    scanf("%d", &T);
    int t = 0;
    while(T--){
        printf("Case %d:\n", ++t);
        scanf("%d%d", &n, &q);
        for(int i = 0; i < n; i++) scanf("%d", &num[i]);
        build(0, 0, n-1);
        while(q--){
            int a, b, h;
            scanf("%d%d%d", &a, &b, &h);
            printf("%d\n", query(a, b, 0, 0, n-1, h));
        }
    }
}