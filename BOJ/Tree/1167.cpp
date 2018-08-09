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
    트리의 지름
    - 임의의 두 점 사이의 거리 중 가장 긴 것

    시작점을 모르니 다익스트라 알고리즘은 어려울것같다.
    임의의 노드에서 DFS로 가장 멀리있는 노드(n1)을 찾자. O(V)
    다시 n1에서 가장 멀리있는 노드(n2)를 찾자. O(V)
    dist(n1,n2)가 곧 지름
    V<=10^6, d<=10^4
*/

struct edge {int v, w;};
typedef vector<vector<edge> > vvEdge;

edge adfs(vvEdge &tree, int temp, vBool &visited) {
    visited[temp] = true;
    // printf("visit... %d\n", temp+1);
    edge tmp;
    int max = -1, retidx=-1;
    for(uint i=0; i<tree[temp].size(); ++i) {
        if(!visited[tree[temp][i].v]) {
            tmp = adfs(tree, tree[temp][i].v, visited);
            tmp.w += tree[temp][i].w;
            if(tmp.w>max) {
                max = tmp.w;
                retidx = tmp.v;
            }
        }
    }
    if(retidx==-1) return {temp, 0};
    return {retidx, max};
}

edge dfs(vvEdge &tree, int s) {
    vBool visited(tree.size(), false);
    edge tmp = adfs(tree, s, visited);
    // cout << tmp.v+1 << ' ' << tmp.w << endl;
    return tmp;
}

int main() {
    int n = getInt();
    vvEdge tree(n);
    for(int i=0,s,e,w; i<n; ++i) {
        s=getInt();
        while((e=getInt())!=-1) {
            w=getInt();
            tree[s-1].push_back({e-1, w});
            tree[e-1].push_back({s-1, w});
        }
    }    
    // for(int i=0; i<n; ++i) {
    //     printf("%d: ",i+1);
    //     for(uint j=0; j<tree[i].size(); ++j) {
    //         printf("%d %d ", tree[i][j].v+1, tree[i][j].w);
    //     } enter();
    // }
    edge ans = dfs(tree, 0);
    ans = dfs(tree, ans.v);
    putInt(ans.w);
    return 0;
}