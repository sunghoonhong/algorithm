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
    집합의 표현

    Disjoint set

    0~n의 원소 1개의 집합이 n+1개 있을때,
    Union과 Find를 구현하라.

    n < 10^6

    시간초과로 오답...

*/
int n;
vInt parent;

bool find_set(int a, int b) {
    while(a!=parent[a]) a=parent[a];
    while(b!=parent[b]) b=parent[b];
    return a==b;
}

void union_set(int a, int b) {
    while(a!=parent[a]) a=parent[a];
    while(b!=parent[b]) b=parent[b];
    if(a!=b) parent[b]=a;
}

int main() {
    n = getInt();
    int m = getInt();
    parent.resize(n+1);
    for(int i=0; i<n+1; ++i) {
        parent[i]=i;
    }
    int op, a, b;
    while(m--) {
        op=getInt();
        a=getInt();
        b=getInt();
        if(op) {
        // find
            if(find_set(a,b)) printf("YES\n");
            else printf("NO\n");
        }
        else {
        // union
            union_set(a,b);
        }
    }
    return 0;
}