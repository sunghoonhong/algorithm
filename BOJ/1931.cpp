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
    회의실배정
    그리디

    시작과 끝이 주어질때
    겹치지않는 것들을 최대한 고르기

    N<=10^6
    가장 빨리 끝나는 회의부터 고르자.
    끝이 같으면 시작이 더 빠른걸 고르자.

    # 의문
    이전에 제출한 코드는 왜 틀렸을까?
    완전히 같은 알고리즘이다.
    혹시나 해서 <말고도 > == 도 추가해봤고,
    그냥 compare함수를 sort()에 줘보기도 했는데,
    전부 오답이었다.
    아니면 입력받는 부분에서 getInt()를 쓰면 안되는건가?
*/

int main() {
    int n = getInt();
    vector<pair<int, int> > confs(n);
    for(int i=0,s,e; i<n; ++i) {
        s=getInt(); e=getInt();
        confs[i]=make_pair(e,s);
    }
    sort(confs.begin(), confs.end());
    int bound = -1, ans = 0;
    for(int i=0; i<n; ++i) {
        // printf("%d ~ %d\n",confs[i].second,confs[i].first);
        if(bound <= confs[i].second) {
            // printf("%d ~ %d\n",confs[i].second,confs[i].first);
            bound = confs[i].first;
            ans++;
        }
    }
    putInt(ans);

    return 0;
}