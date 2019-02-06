// Given g^x=y(mod p),
// find x in log(p)*sqrt(p)
struct BSGS {
    const static int p = 998244353;
    const static int g = 3;
    int m;
    map<int, int> mp;
    vector<int> V;

    void pre() {
        m = (int)ceil(sqrt(p + 0.0) + 1);
        int cg = 1, revgm = 1;
        int invm = (int)(fp(fp(g, m), p - 2));
        for(int i = 0; i < m; i++)  {
            mp[cg] = i;
            V.push_back(revgm);
            cg = (int)(1LL * cg * g % p);
            revgm = (int)(1LL * revgm * invm % p);
        }
    }

    int find(int y) {
        for(int i = 0; i < m; i++) {
            int cur = (int)(1LL * V[i] * y % p);
            if(mp.count(cur)){
                return i * m + mp[cur];
            }
        }
        return -1;
    }

};