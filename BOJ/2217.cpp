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
    로프

    그리디

    N개의 로프와 각 로프가 버틸 수 있는 최대 중량이 주어진다.
    w의 중량을 k개의 로프를 연결하면 w/k의 중량으로 분산된다.
    이때 N개의 로프로 버틸 수 있는 최대 중량을 구하자.
    (모든 로프를 사용할 필요는 없다)
    N<=100000

    한계가 가장 큰 로프부터 시작해서,
    다음 로프를 최대 중량이 작아지지 않을 때까지 탐색해보자.
*/

int main() {
    int n = getInt();
    vInt rope(n);
    for(int i=0; i<n; ++i) {
        rope[i]=getInt();
    }
    sort(rope.begin(), rope.end(), greater<int>());
    int ans = rope[0];
    for(int i=1; i<n; ++i) {
        if(rope[i]*(i+1)>=ans) {
            ans = rope[i]*(i+1);
        }
    }
    putInt(ans);
    return 0;
}