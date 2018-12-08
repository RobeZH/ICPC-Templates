#include <bits/stdc++.h>
using namespace std;

// p           | k  | g
// 469762049     26   3
// 998244353     23   3
// 1004535809    21   3
// 2281701377    27   3
const int N = 65570, mod = 786433, g = 10;
int rev[2*N], w[2][2*N];
int len;

int pow(int x, int k){
    int c = 1;
    for(; k; k >>= 1, x = int(x * 1LL * x % mod)) if(k & 1) c = int(c * 1LL * x % mod);
    return c;
}

void init(){
    len = 65536 * 2;
    for(int i = 0; i < len; i++){
        int y = 0, x = i;
        for(int k = 1; k < len; k *= 2, x >>= 1) (y <<= 1) |= (x & 1);
        rev[i] = y;
    }
    w[0][0] = w[1][0] = 1;
    int mp = pow(g, (mod-1)/len), ni = pow(mp, mod - 2);
    for(int i = 1; i < len; i++){
        w[0][i] = int(w[0][i-1] * 1LL * mp % mod);
        w[1][i] = int(w[1][i-1] * 1LL * ni % mod);
    }
}

void NTT(int y[], int on){
    for(int i = 0; i < len; i++) if(i > rev[i]){int tmp = y[i]; y[i] = y[rev[i]], y[rev[i]] = tmp;}
    for(int h = 2; h <= len; h <<= 1) {
        int wi = len / h;
        for (int j = 0; j < len; j += h) {
            int l = 0;
            for (int k = j; k < j + h / 2; k++) {
                int u = y[k];
                int t = int(1LL * w[on==-1][l] * y[k + h / 2] % mod);
                y[k] = (u + t) % mod;
                y[k + h / 2] = (u - t + mod) % mod;
                l += wi;
            }
        }
    }

    if(on == -1){
        int ni = pow(len, mod-2);
        for(int i = 0; i < len; i++) y[i] = int(1LL * y[i] * ni % mod);
    }
}

int x1[2*N], x2[2*N];

int main(){
    init();

    for(int i = 0; i < 5; i++) x1[i] = x2[i] = i;
    NTT(x1, 1), NTT(x2, 1);
    for(int i = 0; i < len; i++) x1[i] = 1LL * x1[i] * x2[i] % mod;
    NTT(x1, -1);
    for(int i = 0; i < 10; i++) cout << x1[i] << " ";

}