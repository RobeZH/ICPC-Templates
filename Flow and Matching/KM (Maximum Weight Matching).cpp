#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2010;
const int oo = 1000000007;

int dist[MAXN][MAXN];
// Finding the minimum weight prefect matching (of size n) in O(N^3)
// The dist matrix is 1-indexed.
int hungarian(int n, int m){
	vector<int> u(n + 1), v(m + 1), p(m + 1), way(m + 1);
	for(int i = 1; i <= n; i++){
		p[0] = i;
		int j0 = 0;
		vector<int> minv(m + 1, oo);
		vector<char> used(m + 1, false);
		do{
			used[j0] = true;
			int i0 = p[j0], delta = oo, j1;
			for(int j = 1; j <= m; j++){
				if(!used[j]){
					int cur = dist[i0][j] - u[i0] - v[j];
					if(cur < minv[j]){
						minv[j] = cur;
						way[j] = j0;
					}
					if(minv[j] < delta){
						delta = minv[j];
						j1 = j;
					}
				}
			}
			for(int j = 0; j <= m; j++){
				if(used[j]){
					u[p[j]] += delta;
					v[j] -= delta;
				} else {
					minv[j] -= delta;
				}
			}
			j0 = j1;
		} while (p[j0] != 0);
		do{
			int j1 = way[j0];
			p[j0] = p[j1];
			j0 = j1;
		} while(j0);
	}
	return -v[0];
}

