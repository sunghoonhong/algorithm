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
    ATM
    그리디

    각각 걸리는 시간이 주어졌을때,
    여러가지 순서를 시도해보며,
    처음부터 각 행동이 끝날때까지의 시간의 합의 최소.

    시간이 작은 것이 앞에 있을 수록
    뒤에 오는 시간의 합도 줄어든다.

    일단 시간의 오름차순으로 정렬하고 더해보자.
*/

int main() {
    int n = getInt();
    vInt q(n);
    for(int i=0; i<n; ++i) {
        q[i]=getInt();
    }
    sort(q.begin(), q.end());
    int ans = q[0];
    for(int i=1; i<n; ++i) {
        q[i] += q[i-1];
        ans += q[i];
    }
    putInt(ans);
    return 0;
}