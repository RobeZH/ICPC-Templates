#include<bits/stdc++.h>
#define ls(x) x * 2 + 1
#define rs(x) x * 2 + 2

using namespace std;

typedef long long ll;
const int N = (int)1e6 + 50;
int INF = (int)1e9 + 50;

int n,m,q;
int a[N], b[N];
int num[N];

struct node {
    int mn, add;

    void add_val(int x) {
        mn += x;
        add += x;
    }

    void merge(node &ls, node &rs) {
        mn = min(ls.mn, rs.mn);
    }
};

struct Tree {
    node dat[4 * N];

    void push_down(int x, int l, int r) {
        if(dat[x].add) {
            if(l < r) {
                dat[ls(x)].add_val(dat[x].add);
                dat[rs(x)].add_val(dat[x].add);
            }
            dat[x].add = 0;
        }
    }

    void init(int x = 0, int l = 0, int r = n-1) {
        if(l == r) {
            dat[x].mn = num[l];
            dat[x].add = 0;
            return ;
        }
        int mid = (l + r) / 2;
        init(ls(x), l, mid);
        init(rs(x), mid + 1, r);
        dat[x].add = 0;
        dat[x].merge(dat[ls(x)], dat[rs(x)]);
    }

    node query(int a, int b, int x = 0, int l = 0, int r = N-1) {
        int mid = (l + r) / 2;
        if(r < a || l > b) return {INF, 0};

        push_down(x, l, r);

        if(l >= a && r <= b) return dat[x];

        node LHS = query(a, b, ls(x), l, mid);
        node RHS = query(a, b, rs(x), mid+1, r);
        node res;
        res.merge(LHS, RHS);
        return res;
    }

    void update(int a, int b, int x, int l, int r, int delta) {
        int mid = (l + r) / 2;
        if(r < a || l > b) return ;

        push_down(x, l, r);

        if(l >= a && r <= b) {
            dat[x].add_val(delta);
            return ;
        }

        update(a, b, ls(x), l, mid, delta);
        update(a, b, rs(x), mid+1, r, delta);

        dat[x].merge(dat[ls(x)], dat[rs(x)]);
    }

    void update(int a, int b, int delta) {
        update(a, b, 0, 0, N - 1, delta);
    }

    int find(int x, int l, int r) {
        if(l == r) return l;
        int mid = (l + r) / 2;
        push_down(x, l, r);

        if(dat[rs(x)].mn < 0) return find(rs(x), mid + 1, r);
        else return find(ls(x), l, mid);
    }

    int find() {
        if(dat[0].mn >= 0) return -1;
        else return find(0, 0, N-1);
    }

} tree;

