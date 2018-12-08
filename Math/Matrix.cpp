#include <bits/stdc++.h>
using namespace std;

const int D = (int)101, mod = (int)1e9 + 7;
typedef long long ll;

struct matrix
{
    int size;
    ll a[D][D];
    void init(int _size = -1){
        if(_size != -1) size = _size;
        memset(a, 0, sizeof(a));
    }
    matrix(int _size = -1){
        (*this).init(_size);
    }
    void set_identity(){
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++) a[i][j] = (ll)(i == j);
        }
    }
    matrix operator * (const matrix &B) const
    {
        matrix C = matrix(size);

        for(int i = 0; i < size; i++)
            for(int j = 0; j < size; j++){
                for(int k = 0; k < size; k++)
                    C.a[i][j] += a[i][k] * B.a[k][j];
                C.a[i][j] %= mod;
            }
        return C;
    }

    matrix operator ^ (const ll &p) const
    {
        matrix A = (*this), res = matrix(A.size);
        res.set_identity();
        ll t = p;
        while(t > 0)
        {
            if(t % 2) res = res * A;
            A = A * A;
            t /= 2;
        }
        return res;
    }
};


