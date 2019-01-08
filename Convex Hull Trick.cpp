#include <iostream>
#include <cstdio>
#include <deque>

using namespace std;
using ll = long long;

const int N = (int)5e5 + 500;

int n,m;
int num[N];
int dp[N], psum[N];

deque<int> que;

int get_up(int i){return dp[i] + psum[i] * psum[i];}
int get_down(int i){return 2 * psum[i];}

int check(int i, int j, int slope){
    return (get_up(i) - get_up(j)) - slope * (get_down(i) - get_down(j));
}
int check(int i1, int j1, int i2, int j2){
    return (get_up(i1) - get_up(j1)) * (get_down(i2) - get_down(j2))
           - (get_up(i2) - get_up(j2)) * (get_down(i1) - get_down(j1));
}

int main(){
    while(scanf("%d%d", &n, &m) == 2){
        for(int i = 1; i <= n; i++) scanf("%d", &num[i]), psum[i] = psum[i-1] + num[i];

        que.clear();
        que.push_back(0);
        for(int i = 1; i <= n; i++){
            while(que.size() > 1){
                if(check(que[1], que[0], psum[i]) <= 0) que.pop_front();
                else break;
            }
            int ft = que.front();

            dp[i] = dp[ft] + (psum[i] - psum[ft]) * (psum[i] - psum[ft]) + m;
            while(que.size() > 1){
                int ls = que.size() - 1;
                if(check(que[ls], que[ls-1], i, que[ls]) >= 0) que.pop_back();
                else break;
            }
            que.push_back(i);
        }
        printf("%d\n", dp[n]);
    }
}