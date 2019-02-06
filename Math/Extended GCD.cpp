#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll a1, b1, a2, b2, L, R;

// want to solve ax + by = gcd(a,b);
// notice: gcd(a, b) can be negative.
ll extgcd(ll a, ll b, ll &x, ll &y) {
    ll d = a;
    if(b != 0) {
        d = extgcd(b, a % b, y, x);
        y -= (a / b) * x;
    }
    else {
        x = 1; y = 0;
    }
    return d;
}

ll mod(ll a, ll b){
    return (a % b + b) % b;
}

ll dvd(ll a, ll b) {
    return (a - mod(a, b)) / b;
}


int main() {

}