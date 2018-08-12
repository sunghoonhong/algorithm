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
    네트워크 연결
    
    MST

    컴퓨터를 노드, 선을 엣지라고 하고,
    주어진 선들로 이루어진 그래프를 기준으로
    MST의 가중치를 구하는 문제다.
    V<10^3, E<10^5, w<10^4

    MST는 N개의 노드로 구성된 그래프에서
    N-1개의 간선만 연결하여 트리를 만드는 것이므로,
    V*w < 10^7 Int 범위를 넘지 않는다.

    Prim 알고리즘을 사용했다.
*/

struct edge {
    int v, w;
};

typedef vector<vector<edge> > graph;
int v,e;


int popMin(vInt &cost, vInt &candidate) {
    int ret,min=INF,idx;
    for(uint i=0; i<candidate.size(); ++i) {
        if(cost[candidate[i]]<min) {
            min = cost[candidate[i]];
            ret = candidate[i];
            idx = i;
        }
    }
    candidate.erase(candidate.begin()+idx);
    return ret;
}

int prim(graph &g) {
    vInt cost(v, INF), candidate(v);
    vBool visited(v, false);
    for(int i=0; i<v; ++i) candidate[i]=i;

    cost[0] = 0;

    while(!candidate.empty()) {
        int selected = popMin(cost,candidate);
        visited[selected] = true;
        for(uint i=0; i<g[selected].size(); ++i) {
            edge e = g[selected][i];
            if(!visited[e.v] && cost[e.v]>e.w) {
                cost[e.v]=e.w;
            }
        }
    }
    int ans = 0;
    for(int i=0; i<v; ++i) ans+=cost[i];
    return ans;
}

int main() {
    v=getInt();
    e=getInt();
    graph g(v);
    for(int i=0,a,b,c; i<e; ++i) {
        a=getInt(); b=getInt(); c=getInt();
        g[a-1].push_back({b-1,c});
        g[b-1].push_back({a-1,c});
    }
    putInt(prim(g));
    return 0;
}