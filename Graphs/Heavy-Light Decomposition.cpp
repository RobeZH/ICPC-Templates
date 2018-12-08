#include <bits/stdc++.h>
using namespace std;

const int N = 100050, LOG_N = 17;

int n,q;
vector<int> G[N];
int chainNo, chainHead[N], chainInd[N], totPos[N], totsize, veridx[N];
int subsize[N], par[N];
bool black[N];

int depth[N];

int min_v(int u, int v){
    if(u == -1) return v;
    if(v == -1) return u;
    return depth[u] < depth[v] ? u : v;
}


int dfs(int v, int p, int d){
    par[v] = p;
    subsize[v] = 1;
    depth[v] = d;
    for(auto nxt : G[v]){
        if(nxt == p) continue;
        subsize[v] += dfs(nxt, v, d + 1);
    }
    return subsize[v];
}

int hld(int v, int p){
    if(chainHead[chainNo] == -1) chainHead[chainNo] = v;
    chainInd[v] = chainNo;
    totPos[v] = totsize;
    veridx[totsize++] = v;
//    v_cost[totsize ++] = cost;

    int idx = -1;
    for(auto nxt : G[v]){
        if(nxt == p) continue;
        if(idx == -1 || subsize[nxt] > subsize[idx]) idx = nxt;
    }

    if(idx != -1) hld(idx, v);
    for(auto nxt : G[v]){
        if(nxt == p || nxt == idx) continue;
        chainNo ++;
        hld(nxt, v);
    }
}

int dat[N * 4];


void update(int a, int x, int l, int r){
    if(r < a || a < l) return ;
    int mid = (l + r) / 2;
    if(l == r) {
        if(black[l]){
            black[l] = false;
            dat[x] = -1;
        }
        else{
            black[l] = true;
            dat[x] = veridx[l];
        }
        return ;
    }
    int c1 = (x<<1) | 1 , c2 = (x << 1) + 2;
    update(a, c1, l, mid);
    update(a, c2, mid+1, r);

    dat[x] = min_v(dat[c1], dat[c2]);
}

int query(int a, int b, int x, int l, int r){
    if(r < a || b < l) return -1;
    if(a > b) return -1;
    int mid = (l + r) / 2;
    if(a <= l && r <= b) return dat[x];

    int c1 = (x<<1) | 1 , c2 = (x << 1) + 2;
    int LHS = query(a, b, c1, l, mid);
    int RHS = query(a, b, c2, mid+1, r);

    return min_v(LHS, RHS);
}


void init_hld(){
    chainNo = totsize = 0;
    fill(chainHead, chainHead + n, -1);
    dfs(0, -1, 0);
    hld(0, -1);
    fill(dat, dat + 4 * N, -1);
}

int query_single(int v){
    int res = -1;
    while(chainInd[v] != chainInd[0]){
        int cur = query(totPos[chainHead[chainInd[v]]], totPos[v], 0, 0, n-1);
        res = min_v(cur, res);
        v = par[chainHead[chainInd[v]]];
    }
    int cur = query(totPos[0], totPos[v], 0, 0, n-1);
    res = min_v(res, cur);
    return res;
}

int main(){
    scanf("%d%d", &n, &q);
    for(int i = 0; i < n; i++) G[i].clear();
    for(int i = 0; i < n - 1; i++){
        int a, b;
        scanf("%d%d", &a, &b);
        a--, b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    init_hld();

    while(q--){
        int a, b;
        scanf("%d%d", &a, &b);
        if(a == 0){
            b--;
            update(totPos[b], 0, 0, n-1);
        }
        else{
            b--;
            int res = query_single(b);
            if(res != -1) res ++;
            printf("%d\n", res);
        }

    }
    return 0;
}