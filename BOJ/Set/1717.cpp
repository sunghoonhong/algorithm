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

    n < 10^6    m < 10^5

    weigth를 고려한 union으로 원소가 적은 집합이 원소가 많은 집합에 합쳐짐.
    각 set의 head마다 그 집합의 마지막 원소를 저장하는 last를 추가.
    원소가 많은 집합은 tail로 연결해서 탐색할 필요없이 last만 검색.
    원소가 적은 집합은 tail로 순회하며 각 원소의 head를 갱신해준다.

    head와 tail을 사용한 연결리스트로 구현했는데,  -> O(m+nlogn)
    이것보단 parent를 가리키는 트리로 만들어서
    경로압축을 포함한 find를 사용하는 것이 훨씬 나은듯하다 ->O(mlog*n)
*/

struct element {
    int head, tail, weight;
};
vector<element> djset;
vInt last;
int n;

bool find_set(int a, int b) {
    return djset[a].head==djset[b].head;
}

void swap(int &a, int &b) {
    int t = a; a = b; b = t;
}

void printE(element &a) {
    printf("%d %d %d\n", a.head, a.tail, a.weight);
}

void union_set(int a, int b) {
    int ha = djset[a].head;
    int hb = djset[b].head;
    int wa = djset[ha].weight;
    int wb = djset[hb].weight;
    if(ha!=hb) {
        if(wa<wb) {
            swap(ha, hb);
        }
        int t = ha;
        if(last[t]!=-1) t = last[ha];
        djset[t].tail = hb;
        for(t = hb; djset[t].tail!=-1; t=djset[t].tail) {
            djset[t].head = ha;
        }
        djset[t].head = ha;
        last[ha] = t;
        djset[ha].weight+=djset[hb].weight;
    }
}

int main() {
    n = getInt();
    int m = getInt();
    djset.resize(n+1);
    last.resize(n+1);
    for(int i=0; i<n+1; ++i) {
        djset[i]={i,-1, 1};
        last[i] = -1;
    }
    int op, a, b;
    while(m--) {
        // for(int i=0; i<n+1; ++i) { printf("%d: ",i); printE(djset[i]); }
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