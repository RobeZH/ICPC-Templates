#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, int> P;
const int N = (int)1e5 + 500;
const ll INF = (ll)1e18;

struct edge{
    int to, cost;
    edge(int _to, int _cost){
        to = _to, cost = _cost;
    }
};

int n,m,k,a,b,y;
vector<edge> G[N];
ll dis[N];

void dijkstra(){

    fill(dis, dis+N, INF);
    dis[0] = 0;
    priority_queue<P, vector<P>, greater<P> > pque;
    pque.push({0, 0});

    while(!pque.empty()){
        P p = pque.top(); pque.pop();
        int i = p.second;
        ll dist = p.first;
        if(dist > dis[i]) continue;

        for(edge e : G[i]){
            if(e.cost + dis[i] < dis[e.to]){
                dis[e.to] = e.cost + dis[i];
                pque.push({dis[e.to], e.to});
            }
        }
    }
}

