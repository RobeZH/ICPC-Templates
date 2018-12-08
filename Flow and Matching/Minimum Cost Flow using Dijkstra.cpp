#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

const int N = 105, MAX_V = 105, INF = (int)1e9;

typedef pair<int, int> P;
struct edge{int to, cap, cost, rev;};

int n,m,k;
int V; //Please set V!!!!
vector<edge> G[MAX_V];
int h[MAX_V];
int dist[MAX_V];
int prevv[MAX_V], preve[MAX_V];
int ord[N][N], stk[N][N], cst[N][N][N];

void add_edge(int from, int to, int cap, int cost){
    G[from].push_back((edge){to, cap, cost, G[to].size()});
    G[to].push_back((edge){from, 0, -cost, G[from].size() - 1});
}

int min_cost_flow(int s, int t, int f){
    int res = 0;
    fill(h, h + V, 0);
    while(f > 0){
        priority_queue<P, vector<P>, greater<P> > que;
        fill(dist, dist + V, INF);
        dist[s] = 0;
        que.push(P(0, s));
        while(!que.empty()){
            P p = que.top(); que.pop();
            int v = p.second;
            if(dist[v] < p.first) continue;
            for(int i = 0; i < G[v].size(); i++){
                edge &e = G[v][i];
                if(e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]){
                    dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
                    prevv[e.to] = v;
                    preve[e.to] = i;
                    que.push(P(dist[e.to], e.to));
                }
            }
        }
        if(dist[t] == INF) return -1;
        for(int v = 0; v < V; v++) h[v] += dist[v];

        int d = f;
        for(int v = t; v != s; v = prevv[v]){
            d = min(d, G[prevv[v]][preve[v]].cap);
        }
        f -= d;
        res += d * h[t];
        for(int v = t; v != s; v = prevv[v]){
            edge &e = G[prevv[v]][preve[v]];
            e.cap -= d;
            G[v][e.rev].cap += d;
        }
    }
    return res;
}

int get(int id){
    for(int i = 0; i < MAX_V; i++) G[i].clear();

    int s = m + n, t = s + 1, tot = 0;
    V = t + 1;
    for(int i = 0; i < m; i++) if(stk[i][id]) add_edge(s, i, stk[i][id], 0);
    for(int i = m; i < m + n; i++) if(ord[i-m][id]) add_edge(i, t, ord[i-m][id], 0), tot += ord[i-m][id];
    for(int i = 0; i < m; i++){
        for(int j = m; j < m + n; j++){
            add_edge(i, j, stk[i][id], cst[id][j-m][i]);
        }
    }
    return min_cost_flow(s, t, tot);
}

int main(){
    while(true){
        cin >> n >> m >> k;
        if(n == 0 && m == 0 && k == 0) break;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < k; j++) cin >> ord[i][j];
        }
        for(int i = 0; i < m; i++){
            for(int j = 0; j < k; j++) cin >> stk[i][j];
        }
        for(int i = 0; i < k; i++){
            for(int j = 0; j < n; j++){
                for(int u = 0; u < m; u++) cin >> cst[i][j][u];
            }
        }
        int res = 0;
        for(int i = 0; i < k; i++){
            int cur = get(i);
            if(cur == -1){res = -1; break;}
            res += cur;
        }
        cout << res << endl;
    }
}