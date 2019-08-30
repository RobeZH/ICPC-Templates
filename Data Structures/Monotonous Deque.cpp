#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> P;
typedef long long ll;
const int N = 3005, INF = (int)1e9 + 50;

int n, m, a, b;
ll g0, x, y, z;

int num[N][N];
ll mn[N];

// Monotonous Interval Min Queries
struct MonQueue {
    deque<P> que;

    void clear() {
        que.clear();
    }
    void add(P p) {
        while(!que.empty() && que.back().first >= p.first) que.pop_back();
        que.push_back(p);
    }

    int get(int l, int r) {
        while(!que.empty() && (que.front().second < l || que.front().second > r)) que.pop_front();
        return que.empty() ? -INF : que.front().first;
    }
} mque[N], cque;