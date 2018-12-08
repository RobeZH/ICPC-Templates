#include <bits/stdc++.h>
using namespace std;

const int N = 200050, B = 31, INF = (int)1e9;
typedef pair<int, int> P;
typedef long long ll;

int n,x;
int cnt = 1;
int bit[B];
vector<int> num;

struct node{
    int nxt[2], cnt[2];
    int ed;
    node(){nxt[0] = nxt[1] = -1, cnt[0] = cnt[1] = 0; ed = 0;}
}trie[N * B];

void add(int x){
    for(int i = 0; i < 30; i++) bit[i] = x % 2, x /= 2;
    int cur = 0;
    for(int i = 30 - 1; i >= 0; i--){
        int b = bit[i];
        trie[cur].cnt[b]++;
        if(trie[cur].nxt[b] == -1) trie[cur].nxt[b] = cnt++;
        cur = trie[cur].nxt[b];
    }
    trie[cur].ed = 1;
}

void remove(int x){
    for(int i = 0; i < 30; i++) bit[i] = x % 2, x /= 2;
    int cur = 0;
    for(int i = 30 - 1; i >= 0; i--){
        int b = bit[i];
        trie[cur].cnt[b]--;
        cur = trie[cur].nxt[b];
    }
}

int main(){

}