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
    최소 스패닝 트리
    
    MST(최소 스패닝 트리)

    e = (v1, v2, w) 가 주어질 때,
    그래프의 MST의 가중치를 구하라.
    V<10^4 E<10^5, |w|<10^6
    정답은 int 범위 내다.

    MST의 가중치는 MST에 포함되는 비용들(d[])의 합이다.
*/

struct edge {
    int end, w;
};
vector<vector<edge> > g;
int v, e;
ll ans=0;

int extractMin(vInt &q, vInt &d) {
    int ret=0, min=INF, idx=0;
    for(uint i=0; i<q.size(); ++i) {
        if(min>d[q[i]]) {
            min = d[q[i]];
            ret = q[i];
            idx = i;
        }
    }
    q.erase(q.begin()+idx);
    return ret;
}

void prim() {
    // start from vertex 0
    vInt q(v), d(v,INF);
    vBool visited(v, false);
    for(int i=0; i<v-1; ++i) q[i] = i+1;
    d[0] = 0;
    while(!q.empty()) {
        int u = extractMin(q,d);
        visited[u]=true;
        // printf("%d is selected\n", u);
        for(uint i=0; i<g[u].size(); ++i) {
            edge e = g[u][i];
            if(!visited[e.end] && e.w<d[e.end]) {
                d[e.end] = e.w;
                // printf("%d -> %d: %d\n",u,e.end,e.w);
                // break;
            }
        }
    }
    for(int i=0; i<v; ++i) {
        ans+=d[i];
    }
}

int main() {
    v=getInt(); e=getInt();
    g.resize(v);
    for(int i=0,a,b,c; i<e; ++i) {
        a=getInt(); b=getInt(); c=getInt();
        g[a-1].push_back({b-1, c});
        g[b-1].push_back({a-1, c});
    }
    // for(int i=0; i<v; ++i) {
    //     printf("%d: ",i);for(int j=0; j<g[i].size(); ++j) {
    //         printf("%d,%d ",g[i][j].end, g[i][j].w);
    //     }enter();
    // }
    prim();
    putInt(ans);
    return 0;
}