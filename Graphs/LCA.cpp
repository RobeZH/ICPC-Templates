#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> P;

const int N = 100050, INF = (int)1e9;
const int LOG_N = 17;
int root = 0;
int n,m,a,b;

vector<int> G[N];
int parent[LOG_N][N];
int depth[N], par[N];

void dfs(int v, int p, int d){
    parent[0][v] = p;
    depth[v] = d;
    for(int nxt : G[v]){
        if(nxt != p) dfs(nxt, v, d+1);
    }
}

void init(int V){
    dfs(root, -1, 0);

    for(int k = 0; k+1 < LOG_N; k++){
        for(int v = 0; v < V; v++){
            if(parent[k][v] < 0) parent[k+1][v] = -1;
            else parent[k+1][v] = parent[k][parent[k][v]];
        }
    }
}

int lca(int u, int v){
    if(depth[u] > depth[v]){int tmp = u; u = v; v = tmp;}
    for(int k = 0; k < LOG_N; k++){
        if((depth[v] - depth[u]) >> k & 1){
            v = parent[k][v];
        }
    }
    if(u == v) return u;
    for(int k = LOG_N - 1; k >= 0; k--){
        if(parent[k][u] != parent[k][v]){
            u = parent[k][u];
            v = parent[k][v];
        }
    }
    return parent[0][u];
}

int min_dis(int u, int v){
    int ca = lca(u, v);
    return depth[u] + depth[v] - 2 * depth[ca];
}


int main(){
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n-1; i++){
        scanf("%d%d", &a, &b);
        a--, b--;
        G[a].emplace_back(b);
        G[b].emplace_back(a);
    }
    init(n);
}
