#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <assert.h>

using namespace std;

const int N = (int)1e5 + 50;
typedef pair<int, int> P;
typedef long long ll;

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
    int ls, rs, lazy;
    ll sum;
} ns[N * 100];

int newnode(int val){
    ns[ncnt].ls = ns[ncnt].rs = 0;
    ns[ncnt].sum = val;
    ns[ncnt].lazy = 0;
    return ncnt++;
}

int newnode(int ls, int rs){
    ns[ncnt].ls = ls;
    ns[ncnt].rs = rs;
    ns[ncnt].sum = (ls ? ns[ls].sum : 0) + (rs ? ns[rs].sum : 0);
    ns[ncnt].lazy = 0;
    return ncnt++;
}

int n, q;
int num[N];
int vs[N];
int tim = 0;

int newlazynode(int v, int val, int l, int r){
    ns[ncnt].ls = ns[v].ls;
    ns[ncnt].rs = ns[v].rs;
    ns[ncnt].lazy = ns[v].lazy + val;
    ns[ncnt].sum = ns[v].sum + (r - l + 1) * val;
    return ncnt++;
}

void push_down(int v, int tl, int tr){
    if(ns[v].lazy){
        if(tl != tr){
            int mid = (tl + tr) / 2;
            ns[v].ls = newlazynode(ns[v].ls, ns[v].lazy, tl, mid);
            ns[v].rs = newlazynode(ns[v].rs, ns[v].lazy, mid + 1, tr);
        }
        ns[v].lazy = 0;
    }
}

int build(int a[], int tl = 0, int tr = n-1){
    if(tl == tr) return newnode(a[tl]);
    int mid = (tl + tr) / 2;
    return newnode(build(a, tl, mid), build(a, mid + 1, tr));
}

ll get_sum(int v, int l, int r, int tl = 0, int tr = n-1){
    if(tr < l || tl > r) return 0;
    if(l <= tl && tr <= r) return ns[v].sum;
    push_down(v, tl, tr);
    int tm = (tl + tr) / 2;

    return get_sum(ns[v].ls, l, r, tl, tm)
           + get_sum(ns[v].rs, l, r, tm + 1, tr);
}

int update(int v, int l, int r, int val, int tl = 0, int tr = n-1){
    if(tr < l || tl > r) return v;
    if(l <= tl && tr <= r) return newlazynode(v, val, tl, tr);
    push_down(v, tl, tr);
    int tm = (tl + tr) / 2;
    return newnode(update(ns[v].ls, l, r, val, tl, tm), update(ns[v].rs, l, r, val, tm+1, tr));
}

int main(){
    while(scanf("%d%d", &n, &q) == 2){
        ncnt = 1;
        for(int i = 0; i < n; i++) scanf("%d", &num[i]);
        tim = 0;
        vs[tim++] = build(num);
        while(q--){
            char c[2]; int l, r, x;
            scanf("%s", c);
            if(c[0] == 'C'){
                scanf("%d%d%d", &l, &r, &x); l--, r--;
                vs[tim] = update(vs[tim-1], l, r, x);
                tim++;
            }
            else if(c[0] == 'Q'){
                scanf("%d%d", &l, &r); l--, r--;
                printf("%lld\n", get_sum(vs[tim-1], l, r));
            }
            else if(c[0] == 'H'){
                scanf("%d%d%d", &l, &r, &x); l--, r--;
                printf("%lld\n", get_sum(vs[x], l, r));
            }
            else{
                scanf("%d", &x);
                tim = x + 1;
            }
        }

    }

}