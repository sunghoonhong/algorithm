#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <array>
#include <vector>
#include <queue>
#include <deque>
#include <map>
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
inline string getWord(size_t &max_size) {
    int len = 0;
    char ch, cstr[max_size+1];
    for(int i=0; isalpha(ch=getchar()); ++i, ++len) cstr[i] = ch;
    return string(cstr, len);
}
inline ll getLL() {ll n; scanf("%lld", &n); return n;}
inline ull getULL() {ull n; scanf("%llu", &n); return n;}
inline void putInt(int n) {printf("%d", n);}
inline void enter() {putchar('\n');}

void swap(int &a, int &b) {int t=a; a=b; b=t;}
int gcd(int a, int b) {
    if(a<b) swap(a,b);
    for(int t; b; t=a%b, a=b, b=t);
    return a;
}

/*
    퇴사

    DP

    상담 가능한 기간(<=15)과
    각 상담의 소요시간(<=5)과 보수(<1000)가 주어진다.

    0번째일 부터 시작한다고 했을 때,
    solve(n)은 n번째일 이전까지 얻은 보수의 최댓값이다.
*/

int n;
int t[16], p[16], dp[16];

// k일 이전까지 최대 수익
int solve(int k) {
    int &ret = dp[k];
    if(ret!=-1) return ret;
    int lim = k<5 ? k : 5;
    int ans = 0;
    
    for(int i=1,a; i<=lim; ++i) {
        if(t[k-i]==i) a = solve(k-i)+p[k-i];
        else a = solve(k-i);
        ans = max(a,ans);
    }
    return ret = ans;
}

int main() {
    n = getInt();
    memset(dp, -1, sizeof(dp));
    for(int i=0,a,b; i<n; ++i) {
        a=getInt(); b=getInt();
        t[i] = a; p[i] = b;
    }
    // for(int i=0; i<=n; ++i) {
    //     cout << i << ": " << solve(i) << endl;
    // }
    putInt(solve(n));
    return 0;
}