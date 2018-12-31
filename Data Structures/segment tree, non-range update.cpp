#include <bits/stdc++.h>
using namespace std;

#define lson(x) 2*x+1
#define rson(x) 2*x+2

typedef long long ll;
const int N = (int)1e5 + 500;

int n,m,t,a,b;
ll dat[N * 4];
int num[N];

void init_dat(int l, int r, int x){
    if(l == r){dat[x] = num[l]; return ;}

    int mid = (l + r) / 2;
    init_dat(l, mid, lson(x));
    init_dat(mid+1, r, rson(x));
    dat[x] = dat[lson(x)] + dat[rson(x)];
}

void update(int a, int b, int x, int l, int r, int val){
    if(r < a || b < l) return ;
    int mid = (l + r) / 2;
    if(l == r) {
        dat[x] = val;
        return ;
    }
    update(a, b, lson(x), l, mid, val);
    update(a, b, rson(x), mid+1, r, val);

    dat[x] = dat[lson(x)] + dat[rson(x)];
}

ll query(int a, int b, int x, int l, int r){
    if(r < a || b < l) return 0;

    int mid = (l + r) / 2;
    if(a <= l && r <= b) return dat[x];

    ll LHS = query(a, b, lson(x), l, mid);
    ll RHS = query(a, b, rson(x), mid+1, r);

    return LHS + RHS;
}

int main(){
    scanf("%d%d", &t, &m);
    n = (1 << t);
    for(int i = 0; i < n; i++){
        scanf("%d", &num[i]);
    }
    init_dat(0, n-1, 0);
    for(int i = 0; i < m; i++){
        scanf("%d%d", &a, &b);
        a--;
        update(a,a,0,0,n-1,b);
        printf("%d\n", dat[0]);
    }
}
