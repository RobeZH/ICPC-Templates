#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int M = 100050;

bool p[M];
int mu[M], pm[M], pms;

void get_mobius_and_sieve(){
    mu[1] = 1;
    fill(p, p + M, true);
    pms = 0;
    for(int i = 2; i < M; i++){
        if(p[i]){
            pm[pms++] = i;
            mu[i] = -1;
        }
        for(int j = 0; j < pms && i * pm[j] < M; j++){
            p[i * pm[j]] = false;
            if(i % pm[j] == 0){
                mu[i * pm[j]] = 0;
                break;
            }
            mu[i * pm[j]] = -mu[i];
        }
    }
}

int main(){
    get_mobius_and_sieve();
}