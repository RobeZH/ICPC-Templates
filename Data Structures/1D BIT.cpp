#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = (int)4e5 + 500;

//BIT is 1-indexed!!!

int n;
int num[N], bit[N];

int get(int i){
    int ans = 0;
    while(i){ans += bit[i]; i -= (i&-i);}
    return ans;
}

int add(int i, int val){
    while(i < N){bit[i] += val; i += (i&-i);}
}


int main() {
    fill(bit, bit+MAXN, 0);
}
