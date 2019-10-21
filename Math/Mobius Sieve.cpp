#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int M = 100050;

bool p[M];
int mu[M], pm[M], phi[M], pms;

void get_mobius_and_sieve(){
    mu[1] = 1;
    phi[1] = 1;
    fill(p, p + M, true);
    pms = 0;
    for(int i = 2; i < M; i++){
        if(p[i]){
            pm[pms++] = i;
            mu[i] = -1;
            phi[i] = i - 1;
        }
        for(int j = 0; j < pms && i * pm[j] < M; j++){
            p[i * pm[j]] = false;
            if(i % pm[j] == 0){
                mu[i * pm[j]] = 0;
                phi[i * pm[j]] = phi[i] * pm[j];
                break;
            }
            mu[i * pm[j]] = -mu[i];
            phi[i * pm[j]] = phi[i] * (pm[j] - 1);
        }
    }
}

int main(){
    get_mobius_and_sieve();
}