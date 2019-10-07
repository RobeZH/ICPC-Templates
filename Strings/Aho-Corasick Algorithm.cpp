#include <bits/stdc++.h>
using namespace std;

const int M = (int)5e5 + 500;

struct Trie{
    const int B = 26;

    int next[M][B], fail[M], end[M];
    int root, L;
    int newnode(){
        for(int i = 0; i < B; i++) next[L][i] = -1;
        end[L++] = 0;
        return L - 1;
    }
    // Please do initalize it !!!
    void init(){
        L = 0;
        root = newnode();
    }
    void insert(const string &buf){
        int len = buf.length();
        int now = root;
        for(int i = 0; i < len; i++){
            if(next[now][buf[i]-'a'] == -1) next[now][buf[i]-'a'] = newnode();
            now = next[now][buf[i]-'a'];
        }
        end[now] ++;
    }
    void build(){
        queue<int> Q;
        fail[root] = root;
        for(int i = 0; i < B; i++){
            if(next[root][i] == -1) next[root][i] = root;
            else{
                fail[next[root][i]] = root;
                Q.push(next[root][i]);
            }
        }
        while(!Q.empty()){
            int now = Q.front();
            Q.pop();
            for(int i = 0; i < B; i++){
                if(next[now][i] == -1) next[now][i] = next[fail[now]][i];
                else{
                    fail[next[now][i]] = next[fail[now]][i];
                    Q.push(next[now][i]);
                }
            }
        }
    }
    int query(const string &buf){
        int len = buf.length();
        int now = root;
        int res = 0;
        for(int i = 0; i < len; i++){
            now = next[now][buf[i]-'a'];
            int temp = now;
            while(temp != root){
                res += end[temp];
                end[temp] = 0;
                temp = fail[temp];
            }
        }
        return res;
    }
};

Trie Aho;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    while(T--){
        Aho.init();
        int n;
        string s;
        cin >> n;
        for(int i = 0; i < n; i++){
            cin >> s;
            Aho.insert(s);
        }
        Aho.build();
        string t;
        cin >> t;
        cout << Aho.query(t) << endl;
    }

}