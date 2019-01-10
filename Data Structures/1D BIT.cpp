#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = (int)4e5 + 500;

//BIT is 0-indexed!!!

int n;
int num[N], bit[N];
ll bit[N];

void add(int x, int val) {
    for(int i = x; i < n; i |= i + 1) bit[i] += val;
}

ll get(int x) {
    ll res = 0;
    for(int i = x; i >= 0; i = (i & (i + 1)) - 1)  res += bit[i];
    return res;
}

int main() {
    fill(bit, bit+MAXN, 0);
}
