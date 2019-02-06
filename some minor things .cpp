#include <bits/stdc++.h>
using namespace std;

int main(){
	//random number
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	cout << rng() % 5 << endl;
    	std::shuffle(v.begin(), v.end(), rng);
}
