#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> P;
const int mods[4] = {(int)1e9 + 7, (int)1e9 + 9, (int)1e9 + 21, (int)1e9 + 33};
const int N = (int)1e6 + 500;

int n;
string s;
int p = 10;
ll pw[4][N];

struct hs {
    ll val[4];

    hs() { fill(val, val + 4, 0); }

    hs(ll a, ll b, ll c, ll d) {
        val[0] = a, val[1] = b, val[2] = c, val[3] = d;
    }

    bool operator<(const hs &other) const {
        for (int i = 0; i < 4; i++) if (val[i] != other.val[i]) return val[i] < other.val[i];
        return false;
    }

    bool operator==(const hs &other) const {
        for (int i = 0; i < 4; i++) if (val[i] != other.val[i]) return false;
        return true;
    }

    hs operator + (const hs &other) const{
        hs res;
        for(int i = 0; i < 4; i++) res.val[i] = ( val[i] + other.val[i]) % mods[i];
        return res;
    }

    hs operator - (const hs &other) const{
        hs res;
        for(int i = 0; i < 4; i++) res.val[i] = (val[i] - other.val[i] + mods[i]) % mods[i];
        return res;
    }

    void add(int x, int pwi){
        for(int i = 0; i < 4; i++) val[i] = (val[i] + x * pw[i][pwi]) % mods[i];
    }

    void up_pow(int pwi){
        for(int i = 0; i < 4; i++) val[i] = (val[i] * pw[i][pwi]) % mods[i];
    }
};

hs ssum[N];

int main(){
    getline(cin, s);
    n = s.length();
    for(int t = 0; t < 4; t++){
        pw[t][n] = 1;
        for(int i = 1; i < N; i++) pw[t][i] = pw[t][i+1] * p % mods[t];
    }
}