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

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vInt;
typedef vector<vInt> vvInt;
typedef vector<bool> vBool;
typedef vector<vBool> vvBool;
typedef deque<int> dqInt;
typedef priority_queue<int> maxpqInt; //maxheap
typedef priority_queue<int, vInt, greater<int> > minpqInt; //minheap

const int INF = 2147483647;
// const unsigned int INFU = 4294967295U;
// const ll INFLL = 9223372036854775807LL;
// const ull INFULL = 18446744073709551615ULL;

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
    가중치가 자연수인 유향 그래프의 최단거리를 구하기 위해,
    다익스트라 알고리즘을 사용하자.
*/
struct edge {
    edge(int V, int W) { v=V; w=W; }
    int v, w;
};

typedef pair<int, int> pairI;

void dijkstra(int start, vector<vector<edge> > &edges, vInt &dist) {
    dist[start]=0;
    priority_queue<pairI, vector<pairI>, greater<pairI> > vertices;
    int n = dist.size();
    for(int i=0; i<n; ++i) {
        vertices.push(make_pair(dist[i], i));
    }
    // for(int i=0; i<n; ++i) {
    //     cout << vertices.top().first << ' ' << vertices.top().second << endl;
    //     vertices.pop();
    // }
    vBool inVertices(n, true);
    while(!vertices.empty()) {
        int u = vertices.top().second;
        inVertices[u]=false;
        vertices.pop();
        // printf("%d selected\n", u+1);
        for(unsigned int i=0; i<edges[u].size(); ++i) {
            int v = edges[u][i].v;
            int w = edges[u][i].w;
            // printf("to: %d w: %d d[%d]: %d\n",v+1, w,v+1,dist[v]);
            if(inVertices[v] && dist[u]+w<dist[v]) {
                dist[v] = dist[u] + w;
                // printf("changed to %d\n",dist[v]);
            }
            // else printf("unchanged\n");
        }
    }
}

int main() {
    int v, e, k;
    v=getInt(); e=getInt(); k=getInt()-1;
    vector<vector<edge> > edges(v);
    vInt dist(v, INF-10);
    for(int i=0,a,b,c,first; i<e; ++i) {
        a = getInt()-1;
        b = getInt()-1;
        c = getInt();
        first = 1;
        for(unsigned int j=0; j<edges[a].size(); ++j) {
            if(edges[a][j].v==b){
                first = 0;
                if(edges[a][j].w<c) break;
                else {
                    edges[a][j] = edge(b,c);
                    break;
                }
            }
        }
        if(first) edges[a].push_back(edge(b,c));
    }
    dijkstra(k, edges, dist);
    for(int i=0; i<v; ++i) {
        if(dist[i]>=INF-10) printf("INF");
        else putInt(dist[i]);
        enter();       
    }
    return 0;
}