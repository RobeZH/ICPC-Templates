#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <assert.h>

using namespace std;

const int N = (int)1e5 + 50;
typedef pair<int, int> P;

void scanf_(int &num){
    char in;
    while((in=getchar())>'9'||in<'0');
    num=in-'0';
    while(in=getchar(),in>='0'&&in<='9')
        num*=10,num+=in-'0';
}

//Need to initialize before every test case!
int ncnt = 1;

struct node{
    int ls, rs, sum;
} ns[N * 30];

int newnode(int val){
    ns[ncnt].ls = ns[ncnt].rs = 0;
    ns[ncnt].sum = val;
    return ncnt++;
}

int newnode(int ls, int rs){
    ns[ncnt].ls = ls;
    ns[ncnt].rs = rs;
    ns[ncnt].sum = (ls ? ns[ls].sum : 0) + (rs ? ns[rs].sum : 0);
    return ncnt++;
}

int n, q;
int num[N];
int x[N], zeros[N];
int vs[N];

int build(int a[], int tl = 0, int tr = n-1){
    if(tl == tr) return newnode(a[tl]);
    int mid = (tl + tr) / 2;
    return newnode(build(a, tl, mid), build(a, mid + 1, tr));
}

int get_sum(int v, int l, int r, int tl = 0, int tr = n-1){
    if(tr < l || tl > r) return 0;
    if(l <= tl && tr <= r) return ns[v].sum;
    int tm = (tl + tr) / 2;

    return get_sum(ns[v].ls, l, r, tl, tm)
           + get_sum(ns[v].rs, l, r, tm + 1, tr);
}

int update(int v, int pos, int tl = 0, int tr = n-1){
    if(tl == tr) return newnode(ns[v].sum + 1);
    int tm = (tl + tr) / 2;
    if(pos <= tm) return newnode(update(ns[v].ls, pos, tl, tm), ns[v].rs);
    else return newnode(ns[v].ls, update(ns[v].rs, pos, tm+1, tr));
}

int main(){
    int T, t = 0;
    scanf_(T);
    while(T--){
        ncnt = 1;
        printf("Case %d:\n", ++t);
        scanf_(n); scanf_(q);
        for(int i = 1; i <= n; i++){
            scanf_(num[i]);
            x[i-1] = num[i];
        }
        sort(x, x + n);
        for(int i = 1; i <= n; i++) num[i] = (int)(lower_bound(x, x + n, num[i]) - x);

        vs[0] = build(zeros);
        for(int i = 1; i <= n; i++) vs[i] = update(vs[i-1], num[i]);
        while(q--){
            int a, b, h;
            scanf_(a); scanf_(b); scanf_(h); a++, b++;
            h = (int)(upper_bound(x, x + n, h) - x) - 1;
            if(h < 0) printf("0\n");
            else printf("%d\n", get_sum(vs[b], 0, h) - get_sum(vs[a-1], 0, h));
        }
    }

}