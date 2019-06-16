#include <iostream>
#include <vector>
#include <set>
#include <stack>

using namespace std;

const int N = (int)3e5 + 50;

struct edge {
    int to, id;
};

int n, m;
vector<edge> G[N];
set<int> nG[N];
int low[N], pre[N];
int ccnt = 0;
int cmp[N];
stack<int> S;
int cnt = 0;

void dfs(int v, int id) {
    pre[v] = low[v] = ++cnt;
    S.push(v);
    for(int j = 0; j < G[v].size(); j++) {
        edge e = G[v][j];
        if(e.id == id) continue;
        if(pre[e.to] == 0) {
            dfs(e.to, e.id);
            low[v] = min(low[v], low[e.to]);
        }
        else low[v] = min(low[v], pre[e.to]);
    }

    if(pre[v] == low[v]) {
        int cur;
        do {
            cur = S.top(); S.pop();
            cmp[cur] = ccnt;
        } while(cur != v);
        ccnt++;
    }
}