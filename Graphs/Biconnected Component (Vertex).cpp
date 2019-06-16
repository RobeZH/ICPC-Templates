#include <iostream>
#include <vector>
#include <set>
#include <stack>

using namespace std;
typedef pair<int, int> P;

const int N = (int)1e4 + 50, M = (int)1e5 + 50;

struct edge {
    int to, id;
};

int n, m;
vector<edge> G[N];
P p[M];
int low[N], pre[N];
int ccnt = 0;
vector<int> bcc[N];
int cut[N];
stack<int> S;
int cnt = 0;

void init(int n) {
    for(int i = 0; i < n; i++) G[i].clear();
    for(int i = 0; i < n; i++) bcc[i].clear();
    ccnt = cnt = 0;
    fill(cut, cut + n, 0);
    fill(pre, pre + n, 0);
    fill(low, low + n, 0);
    while(!S.empty()) S.pop();
}

void dfs(int v, int par) {
    low[v] = pre[v] = ++cnt;

    int childcnt = 0;
    for(int j = 0; j < G[v].size(); j++) {
        edge e = G[v][j];
        if(e.to == par) continue;
        if(!pre[e.to]) {
            S.push(e.id);
            childcnt++;
            dfs(e.to, v);
            low[v] = min(low[v], low[e.to]);
            if(low[e.to] >= pre[v]) {
                cut[v] = true;
                int cur;
                do {
                    cur = S.top();
                    S.pop();
                    bcc[ccnt].push_back(cur);
                } while(cur != e.id);
                ccnt++;
            }
        }
        else if(pre[e.to] < pre[v]){
            S.push(e.id);
            low[v] = min(low[v], pre[e.to]);
        }
    }

    if(childcnt < 2 && par == -1) cut[v] = false;

}

int main() {
    cin >> n >> m;
    init(n);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b; a--, b--;
        p[i].first = a, p[i].second = b;
        G[a].push_back({b, i});
        G[b].push_back({a, i});
    }
    for(int i = 0; i < n; i++) {
        if(!pre[i]) {
            dfs(i, -1);
        }
    }

}