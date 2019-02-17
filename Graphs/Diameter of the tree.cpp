#include <bits/stdc++.h>
using namespace std;

const int N = 123456 + 50;
const int INF = (int)1e9;
typedef pair<int, int> P;

int n, m;
set<int> G[N];
int dis[N];

P bfs(int v) {
    fill(dis, dis + n, INF);
    queue<int> que;
    dis[v] = 0;
    que.push(v);
    while(!que.empty()) {
        int u = que.front(); que.pop();
        for(int nxt : G[u]) {
            if(dis[nxt] > dis[u] + 1) {
                dis[nxt] = dis[u] + 1;
                que.push(nxt);
            }
        }
    }
    int res = -1, u = -1;
    for(int i = 0; i < n; i++) {
        if(dis[i] != INF) {
            if(dis[i] > res){
                res = dis[i];
                u = i;
            }
            else if(dis[i] == res) {
                if(i < u) u = i;
            }
        }
    }
    return {res, u};
}

int get_diameter() {
    int u = -1;
    for(int i = 0; i < n; i++) if(in[i]) {u = i; break;}
    P p = bfs(u);
    P p2 = bfs(p.second);
    return p2.first;
}