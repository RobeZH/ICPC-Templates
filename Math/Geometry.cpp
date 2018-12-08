#include<cstdio>
#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;

const double EPS = 1e-9;
const double PI = 3.14159265;

struct point{
    double x,y;
    point(double _x, double _y): x(_x), y(_y) {}
    
    bool operator == (point other) const {
        return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS));  
    }
    point operator + (point other) const{
        return point(x + other.x, y + other.y);
    }
};

double dist(point a,point b){
    return hypot(a.x - b.x, a.y - b.y);
}

point rotate(point p, double theta){
    double rad = theta * PI / 180.0;
    return point(p.x * cos(rad) - p.y * sin(rad), p.x * sin(rad) + p.y * cos(rad));
}

struct vec {
    double x,y;
    vec(double _x, double _y): x(_x), y(_y) {}
};



vec toVec(point a, point b){
    return vec(b.x - a.x, b.y - a.y);
}

double cross(vec a, vec b){
    return a.x * b.y - a.y * b.x;
}

bool ccw(point p, point q, point r){
    return cross(toVec(p,q),toVec(q,r)) >  EPS;
}

bool colinear(point p, point q, point r){
    return fabs(cross(toVec(p,q),toVec(q,r))) <  EPS;
}

point pivot = point(0,0);
bool angleCmp(point a, point b){
    if(colinear(pivot,a,b)) return dist(pivot,a) < dist(pivot, b);
    double d1x = a.x - pivot.x, d1y = a.y - pivot.y;
    double d2x = b.x - pivot.x, d2y = b.y - pivot.y;
    return (atan2(d1y,d1x) - atan2(d2y, d2x)) < 0;
}

vector<point> CH(vector<point> P){
    int i,j,n = (int)P.size();
    if(n <= 3){
        if(!(P[0] == P[n-1])) P.push_back(P[0]);
        return P;
    }
    int P0 = 0;
    for(int i = 1; i < n; i++)
        if(P[i].y < P[P0].y || (P[i].y == P[P0].y && P[i].x > P[P0].x))
            P0 = i;
    
    point temp = P[0]; P[0] = P[P0]; P[P0] = temp;
    
    pivot = P[0];
    //printf("smallest %lf %lf\n", P[0].x, P[0].y);
    
    sort(P.begin()+1, P.end(), angleCmp);
    
    vector<point> S;
    S.push_back(P[n-1]); S.push_back(P[0]); S.push_back(P[1]);
    i = 2; 
    while(i < n){
        j = (int) S.size() - 1;
        if(ccw(S[j-1],S[j],P[i])) S.push_back(P[i++]);
        else S.pop_back();
    }
    //printf("smallest %lf %lf\n", P[0].x, P[0].y);
    return S;
}

double area(const vector<point> &P){
    double result = 0.0, x1, y1, x2, y2;
    for(int i = 0; i < (int)P.size() - 1; i++){
        x1 = P[i].x; x2 = P[i+1].x;
        y1 = P[i].y; y2 = P[i+1].y;
        result += (x1 * y2 - x2 * y1);
    }
    return fabs(result) / 2.0;
}

vector<point> K;
vector<point> CHP;

int main(){
    int t;
    int n;
    double x,y,w,h,d;
    scanf("%d", &t);
    while(t--){
        K.clear();
        CHP.clear();
        double areaOfRecs = 0;
        scanf("%d",&n);
        for(int i = 0; i < n; i++){
            scanf("%lf%lf%lf%lf%lf", &x,&y,&w,&h,&d);
            areaOfRecs += w * h;
            point origin = point(x,y);
            K.push_back(origin + rotate(point(w/2,h/2), -d));
            K.push_back(origin + rotate(point(w/2,-h/2), -d));
            K.push_back(origin + rotate(point(-w/2,h/2), -d));
            K.push_back(origin + rotate(point(-w/2,-h/2), -d));
        }
//      for(int i = 0; i < K.size(); i++){
//          printf("%lf %lf\n", K[i].x, K[i].y);
//      }
        CHP = CH(K);
        //printf("smallest %lf %lf\n", K[0].x, K[0].y);
        //cout<<endl;
//      for(int i = 0; i < CHP.size(); i++){
//          printf("%lf %lf\n", CHP[i].x, CHP[i].y);
//      }
//      printf("smallest %lf %lf\n", pivot.x, pivot.y);
        double areaOfPoly = area(CHP);
        //printf("%lf %lf\n", areaOfRecs, areaOfPoly);
        printf("%.1lf %\n", areaOfRecs * 100 /areaOfPoly);
    }
    
}
