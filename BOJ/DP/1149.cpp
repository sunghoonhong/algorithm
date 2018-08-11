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

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vInt;
typedef vector<vInt> vvInt;
typedef vector<bool> vBool;
typedef vector<vBool> vvBool;
typedef deque<int> dqInt;

const int INF = 2147483647;
const ll INFLL = 9223372036854775807LL;
const ull INFULL = 18446744073709551615ULL;

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

/*
    RGB거리
    DP

    f(n)=n번째 집까지 칠하는 비용의 최솟값
    r(n)=n번째 집을 R로 했을때 최소값
    g(n)=n번째 집을 G로 했을때 최소값
    b(n)=n번째 집을 B로 했을때 최소값
    r(n) = min(g(n-1),b(n-1)) + r[n]
    g(n) = min(r(n-1),b(n-1)) + g[n]
    b(n) = min(r(n-1),g(n-1)) + b[n]
    ans = min(r(n),g(n),b(n))
*/
vInt r,g,b;
int mr[1003],mg[1003],mb[1003];
int G(int n);
int B(int n);

int R(int n) {
    int &ret = mr[n];
    if(ret!=-1) return ret;
    if(n==0) return ret = r[0];
    return ret = min(G(n-1),B(n-1))+r[n];
}
int G(int n) {
    int &ret = mg[n];
    if(ret!=-1) return ret;
    if(n==0) return ret = g[0];
    return ret = min(R(n-1),B(n-1))+g[n];
}
int B(int n) {
    int &ret = mb[n];
    if(ret!=-1) return ret;
    if(n==0) return ret = b[0];
    return ret = min(R(n-1),G(n-1))+b[n];
}

int main() {
    int n = getInt();
    r.reserve(n);
    g.reserve(n);
    b.reserve(n);
    memset(mr,-1,sizeof(mr));
    memset(mg,-1,sizeof(mg));
    memset(mb,-1,sizeof(mb));
    for(int i=0; i<n; ++i) {
        r[i]=getInt();
        g[i]=getInt();
        b[i]=getInt();
    }
    n--;    // index를 맞춰주기 위함. (n번째 == arr[n-1]))
    int ans = min(R(n),G(n));
    ans = min(ans,B(n));
    putInt(ans);
    return 0;
}