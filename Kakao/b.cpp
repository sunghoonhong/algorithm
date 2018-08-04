#include <iostream>
#include <cstdio>
#include <string>
#include <string.h>
#include <array>
#include <vector>
#include <queue>
#include <deque>
#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vInt;
typedef vector<vInt> vvInt;
typedef vector<bool> vBool;
typedef vector<vBool> vvBool;
typedef deque<int> dqInt;

inline bool isNum(char ch) {return ch>='0'&&ch<='9';}
inline int getInt() {
    int ret = 0, ch;
    bool sign = 0;
    for(ch=getchar(); !(isNum(ch)||ch=='-'); ch=getchar());
    if(ch=='-') { sign = 1; ch=getchar(); }
    if(!isNum(ch)) return getInt(); // InvalidInputError
    else for(ret=ch-'0', ch=getchar(); isNum(ch); ch=getchar()) ret = ret*10 + ch-'0';
    return sign?-ret:ret;
}
inline ll getLL() {ll n; scanf("%lld", &n); return n;}
inline ull getULL() {ull n; scanf("%llu", &n); return n;}
inline void putInt(int n) {printf("%d", n);}
inline void enter() {putchar('\n');}


double sum[501];   // sum[a,b] = sum[b]-sum[a-1]

double stdv(vector<double> &like, int b, int e) {
    double m = b ? sum[e]-sum[b-1] : sum[e];
    m/=(long double)(e-b+1);
    double ret = 0;
    for(int i=b; i<=e; ++i) {
        ret += (like[i]-m)*(like[i]-m);
    }
    ret = sqrt(ret / (e-b+1));
    return ret;
}

int main() {
    int n,k;
    cin >> n >> k;
    vector<double> like(n, 0);
    for(int i=0; i<n; ++i) {
        cin >> like[i];
        if(i==0) sum[i] = like[i];
        else sum[i]+=sum[i-1]+like[i];
        // cout << sum[i] << endl;
    }
    double ans = stdv(like, 0, k-1);
    for(int i=0; i<n; ++i) {
        for(int j=k; i+j-1<n; ++j) {
            double t = stdv(like, i,i+j-1);
            if(ans>t) ans = t;
        }
    }
    printf("%0.8lf", ans);
    return 0;
}