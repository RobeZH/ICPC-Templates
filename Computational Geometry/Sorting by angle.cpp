#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
    Point operator-(Point p) { return {x - p.x, y - p.y}; }
};

const int N = 2222;
Point pt[N];

bool InUpper(Point p) {
    return p.y > 0 || (p.y == 0 && p.x > 0);
}
int CrossProd(Point A, Point B) {
    return A.x * B.y - A.y * B.x;
}
int main() {
    vector<pair<Point, int> > A;
    sort(A.begin(), A.end(), [&](pair<Point, int> &A, pair<Point, int> &B) {
        int au = InUpper(A.first);
        int bu = InUpper(B.first);
        if (au != bu) {
            return au > bu;
        }
        return CrossProd(A.first, B.first) > 0;
    });
}