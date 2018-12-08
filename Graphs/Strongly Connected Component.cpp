#include <bits/stdc++.h>
using namespace std;

const int N = (int)2e5 + 500, INF = (int)1e9;
typedef pair<int, int> P;
typedef long long ll;

int n, m;
string word[N], a, b;
vector<int> G[N], rG[N], vs;
bool used[N];
int cmp[N];
vector<int> Gn[N];

void add_edge(int from, int to){
    G[from].push_back(to);
    rG[to].push_back(from);
}

void dfs(int v){
    used[v] = true;
    for(int nxt : G[v]){
        if(!used[nxt]) dfs(nxt);
    }
    vs.push_back(v);
}

void rdfs(int v, int k){
    used[v] = true;
    cmp[v] = k;
    for(int nxt : rG[v]){
        if(!used[nxt]) rdfs(nxt, k);
    }
}

P dfsn(int v){
    if(dp[v].first != -1) return dp[v];
    cpf(dp[v], valcmp[v]);
    for(int nxt : Gn[v]){
        P p = dfsn(nxt);
        if(p < dp[v]) cpf(dp[v], p);
    }
    return dp[v];
}


int scc(){
    memset(used, 0, sizeof(used));
    vs.clear();
    for(int v = 0; v < n; v++){
        if(!used[v]) dfs(v);
    }
    memset(used, 0, sizeof(used));
    int k = 0;
    reverse(vs.begin(), vs.end());
    for(int v : vs){
        if(!used[v]) rdfs(v, k++);
    }
    return k;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie();

    cin >> m;
    for(int i = 0; i < m; i++){
        cin >> a >> b;
        add_edge(a, b);
    }
}
