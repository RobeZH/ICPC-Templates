#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

const int N = 505;
const int INF = (int)1e9;

string str[N];
int hx[N], hy[N], mx[N], my[N], hi=0, mi=0;
int n,m,nx,ny;
int match[N],lx[N],ly[N],slack[N];
int visx[N],visy[N],w[N][N];

int abs(int a){
    return a > 0 ? a : -a;
}

int dis(int h, int m){
    return abs(hx[h] - mx[m]) + abs(hy[h] - my[m]);
}

int dfs(int x){
    visx[x]=1;
    for(int y=1;y<=ny;y++){
        if(visy[y])
            continue;
        int tmp=lx[x]+ly[y]-w[x][y];
        if(tmp==0){
            visy[y]=1;
            if(match[y]==-1 || dfs(match[y])){
                match[y]=x;
                return 1;
            }
        }else if(slack[y]>tmp){
            slack[y]=tmp;
        }
    }
    return 0;
}

int KM(bool max_w){
    for(int i = 0; i < N; i++) match[i] = -1;
    if(!max_w){
        for(int i = 1; i <= nx; i++)
            for(int j = 1; j <= ny;j++)
                w[i][j] = -w[i][j];

    }
    int i,j;

    memset(ly,0,sizeof(ly));
    memset(lx,0, sizeof(lx));
    for(int i = 0; i < N; i++) hx[i]= hy[i] = mx[i] = my[i] = ly[i] = lx[i] = 0;
    for(i=1;i<=nx;i++)
        for(j=1,lx[i]=-INF;j<=ny;j++)
            if(w[i][j]>lx[i])
                lx[i]=w[i][j];
    for(int x=1;x<=nx;x++){
        for(i=1;i<=ny;i++)
            slack[i]=INF;
        while(1){
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(dfs(x))
                break;
            int d=INF;
            for(i=1;i<=ny;i++)
                if(!visy[i] && d>slack[i])
                    d=slack[i];
            for(i=1;i<=nx;i++)
                if(visx[i])
                    lx[i]-=d;
            for(i=1;i<=ny;i++)
                if(visy[i])
                    ly[i]+=d;
                else
                    slack[i]-=d;
        }
    }
    int res=0;
    for(i=1;i<=ny;i++)
        if(match[i]!=-1)
            res+=w[match[i]][i];
    if(!max_w) return -res;
    else return res;
}
int main(){
    while(true){
        cin >> n >> m;
        if(n == 0 && m == 0) break;
        for(int i = 0; i < n; i++){
            cin >> str[i];
            for(int j = 0; j < m; j++){
                if(str[i][j] == 'H') hx[hi] = i, hy[hi++] = j;
                if(str[i][j] == 'm') mx[mi] = i, my[mi++] = j;
            }
        }

        for(int i = 0; i < hi; i++){
            for(int j = 0; j < hi; j++){
                w[i+1][j+1] = dis(i, j);
            }
        }
        nx=ny=n=hi;
        int ans=KM(false);
        printf("%d\n",ans);
    }
    return 0;
}