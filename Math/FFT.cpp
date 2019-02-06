#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);

#define swap(a, b) auto tmp = a; a = b, b = tmp;

struct Complex{
    double x, y;
    Complex(double _x = 0.0, double _y = 0.0){
        x = _x, y = _y;
    }
    Complex operator - (const Complex &b) const{
        return Complex(x - b.x, y - b.y);
    }
    Complex operator + (const Complex &b) const{
        return Complex(x + b.x, y + b.y);
    }
    Complex operator * (const Complex &b) const{
        return Complex(x * b.x - y * b.y, x * b.y + y * b.x);
    }
};

void change(Complex y[], int len){
    int i, j, k;
    for(i = 1, j = len/2; i < len - 1; i++){
        if(i < j){Complex tmp = y[i]; y[i] = y[j], y[j] = tmp;}
        k = len / 2;
        while(j >= k){
            j = j - k;
            k = k / 2;
        }
        if(j < k) j += k;
    }
}

void fft(Complex y[], int len, int on){
    change(y, len);
    for(int h = 2; h <= len; h <<= 1){
        Complex wn(cos(-on*2*PI/h), sin(-on*2*PI/h));
        for(int j = 0; j < len; j += h){
            Complex w(1,0);
            for(int k = j; k < j + h/2; k++){
                Complex u = y[k];
                Complex t = w * y[k + h/2];
                y[k] = u + t;
                y[k + h/2] = u - t;
                w = w * wn;
            }
        }
    }
    if(on == -1){
        for(int i = 0; i < len; i++){
            y[i].x /= len;
        }
    }
}

const int N = 200050;

Complex x1[N], x2[N];
string s1, s2;
int sum[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    while(cin >> s1 >> s2){
        int len1 = s1.length(), len2 = s2.length();
        int len = 1;
        while(len < len1 * 2 || len < len2 * 2) len *= 2;
        for(int i = 0; i < len1; i++) x1[i] = Complex(s1[len1-1-i] - '0', 0);
        for(int i = len1; i < len; i++) x1[i] = Complex(0, 0);
        for(int i = 0; i < len2; i++) x2[i] = Complex(s2[len2-1-i] - '0', 0);
        for(int i = len2; i < len; i++) x2[i] = Complex(0, 0);
        fft(x1, len, 1);
        fft(x2, len, 1);
        for(int i = 0; i < len; i++) x1[i] = x1[i] * x2[i];
        fft(x1, len, -1);
        for(int i = 0; i < len; i++) sum[i] = (int)(x1[i].x + 0.5);

        for(int i = 0; i < len; i++){
            sum[i+1] += sum[i] / 10;
            sum[i] %= 10;
        }
        len --;
        while(len > 0 && sum[len] == 0) len--;

        for(int i = len; i >= 0; i--) cout << sum[i];
        cout << endl;
    }
}