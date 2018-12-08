#include <bits/stdc++.h>
using namespace std;

const int N = (int)3e5 + 500;
typedef pair<int, int> P;

vector<int> G[N];
int n, m;
int tin[N], fup[N], timer;

void IS_BRIDGE(int u, int v){
}

void IS_NOT_BRIDGE(int u, int v){

}


void dfs(int x, int par = -1)
{
    tin[x] = timer++;
    fup[x] = tin[x];
    for(auto nxt : G[x])
    {
        if(tin[nxt] > 0)
        {
            if(par != nxt)
                fup[x] = min(fup[x], tin[nxt]);
        }
        else
        {
            dfs(nxt, x);
            fup[x] = min(fup[x], fup[nxt]);
            if(fup[nxt] > tin[x])
                IS_BRIDGE(x, nxt);
            else
                IS_NOT_BRIDGE(x, nxt);
        }
    }
}


void find_bridges() {
    timer = 1;
    fill(tin, tin + n, 0);
    fill(fup, fup + n, 0);
    for (int i = 0; i < n; ++i) {
        if (tin[i] == 0)
            dfs(i);
    }
}

int main(){
    int a, b;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++){
        scanf("%d%d", &a, &b);
        a--, b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    find_bridges();
}