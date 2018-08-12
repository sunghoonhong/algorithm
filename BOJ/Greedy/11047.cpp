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
    동전 0
    그리디

    여러 단위의 동전으로 K를 만들 때,
    동전 개수의 최솟값을 구하는 문제.

    눈여겨볼 조건은 동전의 가치가 오름차순으로 주어지는데,
    다음에 오는 동전은 이전 동전의 배수라는 점이다.
    배수가 아니면 복잡한 문제가 되지만,
    배수조건을 보장함으로써 간단한 문제가 된다.
    ex) 1,4,5로 12를 만들 때, 아래와 같이 풀려고 하면
    4*3(3) / 5*2+1*2(4) 와 같은 반례가 생긴다.
    (정답은 3이지만 단순하게 풀면 4가 나와서 오답이다.)

    가장 큰 가치의 동전부터 K를 만들어보자.
*/

int main() {
    int n = getInt();
    int k = getInt();
    vInt coin(n);
    for(int i=0; i<n; ++i) {
        coin[i] = getInt();
    }
    int ans = 0;
    int idx = n-1;
    while(k && idx>-1) {
        ans += k/coin[idx];
        k%=coin[idx--];
    }
    putInt(ans);
    return 0;
}