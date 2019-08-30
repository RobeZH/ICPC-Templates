#include <bits/stdc++.h>
using namespace std;

const int N = (int)1e5 + 50, B = 256;

struct state {
    int len, link;
    int next[B];
};

struct SAM {
    const static int MAXLEN = (int)1005;
    state st[MAXLEN * 2];
    int sz, last;

    void sam_init() {
        st[0].len = 0;
        st[0].link = -1;
        memset(st[0].next, -1, sizeof(st[0].next));
        sz = 1;
        last = 0;
    }

    void sam_extend(int c) {
        int cur = sz++;
        st[cur].len = st[last].len + 1;
        memset(st[cur].next, -1, sizeof(st[cur].next));
        int p = last;
        while(p != -1 && st[p].next[c] == -1) {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if(p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if(st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = sz++;
                st[clone].len = st[p].len + 1;
                memcpy(st[clone].next, st[q].next, sizeof(st[q].next));
                st[clone].link = st[q].link;
                while(p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }

    int calc() {
        int res = 0;
        for(int v = 0; v < sz; v++) {
            if(st[v].link != -1) res += st[v].len - st[st[v].link].len;
        }
        return res;
    }
} sam;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while(T--) {
        sam.sam_init();
        string s;
        cin >> s;
        for(char c : s) sam.sam_extend(c);
        cout << sam.calc() << endl;
    }


}