#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 100 + 2;
int mod;

int n, m;
ll inv[N];
int num[N][N];

void calc_inv() {
    inv[1] = 1;
    for(int i = 2; i < N; i++) inv[i] = (mod - (mod / i) * inv[mod % i] % mod) % mod;
}

struct matrix {
    static const int maxn = 405;
    int n, m;
    ll mat[maxn][maxn];
    ll x[maxn];
    ll res[maxn];
    matrix() { memset(mat, 0, sizeof(mat)); }
    void print() {
        cout << "MATRIX " << n << " " << m << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << mat[i][j] << "\t";
            }
            cout << "= " << res[i];
            cout << endl;
        }
    }
    bool gauss() {
        for (int i = 0; i < n; i++) {
            int sid = -1;
            for (int j = i; j < n; j++)
                if (mat[j][i] > 0) {
                    sid = j;
                    break;
                }
            if (sid == -1) continue;
            if (sid != i) {
                for (int j = 0; j < n; j++) {
                    swap(mat[sid][j], mat[i][j]);
                }
                swap(res[sid], res[i]);
            }
            for (int j = i + 1; j < n; j++) {
                ll ratio = mat[j][i] * inv[mat[i][i]] % mod;
                for (int k = 0; k < n; k++) {
                    mat[j][k] -= mat[i][k] * ratio % mod;
                    mat[j][k] += mod;
                    if(mat[j][k] >= mod) mat[j][k] -= mod;

                }
                res[j] -= res[i] * ratio % mod;
                res[j] += mod;
                if(res[j] >= mod) res[j] -= mod;

            }
        }
        for(int i = m - 1; i >= 0; i--) {
            ll sum = res[i];
            for(int j = i + 1; j < m; j++) {
                sum -= x[j] * mat[i][j] % mod;
                sum %= mod;
            }
            sum = (sum + mod) % mod;
            x[i] = sum * inv[mat[i][i]] % mod;
            if(mat[i][i] == 0 && sum != 0) return false;
        }
        return true;
    }
} mat;
