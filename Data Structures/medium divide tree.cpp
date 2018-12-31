#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

// I unofficially named it medium divide tree.
// HDU 2665 / POJ 2104
// O(logn) query for kth number in certain interval
const int N = (int)1e5 + 500, LOGN = 20;

int n,q;
int num[N], sorted[N];
int tree[LOGN][N], toleft[LOGN][N];

void build(int dep, int l, int r){
    if(l == r) return ;
    int mid = (l + r) / 2;
    int same = mid - l + 1;
    for(int i = l; i <= r; i++) if(tree[dep][i] < sorted[mid]) same--;
    int lpos = l, rpos = mid + 1;
    for(int i = l; i <= r; i++){
        if(tree[dep][i] < sorted[mid]){
            tree[dep+1][lpos++] = tree[dep][i];
        }
        else if(tree[dep][i] == sorted[mid] && same > 0){
            tree[dep+1][lpos++] = tree[dep][i]; same--;
        }
        else tree[dep+1][rpos++] = tree[dep][i];
        toleft[dep][i] = toleft[dep][l-1] + lpos - l;
    }
    build(dep + 1, l, mid);
    build(dep + 1, mid + 1, r);
}

void init(){
    for(int i = 1; i <= n; i++) sorted[i] = tree[0][i] = num[i];
    sort(sorted + 1, sorted + n + 1);
    build(0, 1, n);
}

int query(int dep, int l, int r, int ql, int qr, int k){
    if(ql == qr) return tree[dep][ql];
    int mid = (l + r) / 2;
    int cnt = toleft[dep][qr] - toleft[dep][ql - 1];
    if(cnt >= k){
        int newl = l + toleft[dep][ql-1] - toleft[dep][l-1];
        int newr = newl + cnt - 1;
        return query(dep + 1, l, mid, newl, newr, k);
    }
    else{
        int newr = qr + toleft[dep][r] - toleft[dep][qr];
        int newl = newr - (qr - ql - cnt);
        return query(dep + 1, mid + 1, r, newl, newr, k - cnt);
    }
}

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        scanf("%d%d", &n, &q);
        for(int i = 1; i <= n; i++) scanf("%d", &num[i]);
        init();
        while(q--){
            int a, b, k;
            scanf("%d%d%d", &a, &b, &k);
            printf("%d\n", query(0, 1, n, a, b, k));
        }
    }
}