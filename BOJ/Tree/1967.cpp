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
    루트 = 1번 노드
    1<=v<=10000
    0<w<=100
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
    for(int i=0,p,c,w; i<n-1; ++i) {
        // p < c 가 보장된다.
        p=getInt();
        c=getInt();
        w=getInt();
        tree[p-1].push_back({c-1, w});
        tree[c-1].push_back({p-1, w});
    }
    edge ans = dfs(tree, 0);
    ans = dfs(tree, ans.v);
    putInt(ans.w);
    return 0;
}