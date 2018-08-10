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
    피보나치 함수
    DP
    피보나치 수열을 재귀함수를 통해 구할 때,
    n이 0, 1인 경우에 도달하는 횟수를 각각 구한다.

    시간제한이 250ms인데,
    자연스럽게 실제로 재귀함수를 그대로 구현하는 것은
    시간초과로 오답이 된다.

    따라서 DP를 이용하여,
    f(n)=n번째 피보나치수열을 구하는 과정에서
    f(0), f(1)이 각각 호출되는 횟수

    n<=40이므로 그냥
    f0(n), f1(n)으로 각각 해주는게 편해보인다.
*/


int mem0[42], mem1[42];

int f0(int n) {
    int &ret = mem0[n];
    if(ret!=-1) return ret;
    if(n==0) return ret=1;
    if(n==1) return ret=0;
    return ret=f0(n-1)+f0(n-2);
}

int f1(int n) {
    int &ret = mem1[n];
    if(ret!=-1) return ret;
    if(n==0) return ret=0;
    if(n==1) return ret=1;
    return ret=f1(n-1)+f1(n-2);
}

int main() {
    int t = getInt();
    memset(mem0, -1, sizeof(mem0));
    memset(mem1, -1, sizeof(mem1));

    while(t--) {
        int n = getInt();
        putInt(f0(n));
        putchar(' ');
        putInt(f1(n));
        enter();
    }
    return 0;
}