#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Calculate Sigma 0 to n, floor((a*i+b)/c)
ll fd(ll a,ll b,ll c,ll n) {
    if (a == 0) return ((b / c) * (n + 1));
    if (a >= c || b >= c) return fd(a % c, b % c, c, n) + (a / c) * n * (n + 1) / 2 + (b / c) * (n + 1);
    ll m = (a * n + b) / c;
    ll v = fd(c, c - b - 1, a, m - 1);
    return n * m - v;
}