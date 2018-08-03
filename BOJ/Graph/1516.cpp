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
#include <inttypes.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vint;
typedef vector<vint> vvint;
typedef vector<bool> vbool;
typedef vector<vbool> vvbool;
typedef deque<int> dqint;

inline bool isNum(char ch) { return ch>='0'&&ch<='9'; }
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
inline void putInt(int n) { printf("%d", n); }
inline void enter() {putchar('\n');}

/*
    각 건물마다 건물의 진입간선들만을 따라가는 dfs 탐색을 하자.
*/


void adfs(int v, vvint &in, vvint &out, vbool &visited, vint &ans) {
    visited[v] = true;
    for(unsigned int i=0; i<in[v].size(); ++i) {
        if(!visited[in[v][i]]) {
            adfs(in[v][i], in, out, visited, ans);
        }
    }
    ans.push_back(v);
}

vint dfs(int v, vvint in, vvint out) {
    vint ans;
    vbool visited(in.size(), false);
    adfs(v, in, out, visited, ans);
    return ans;
}
int ts(int v, vvint in, vvint out, vint& cost) {
    vint list = dfs(v, in, out);
    int ans = 0;
    // cout << "DFS: ";
    for(unsigned int i=0; i<list.size(); ++i) {
        // putInt(list[i]);
        // putchar(' ');
        ans += cost[list[i]];
    }
    // enter();
    return ans;
}

int main() {
    int n = getInt();
    vvint in(n), out(n);
    vint cost(n);
    for(int i=0,t; i<n; ++i) {
        cost[i] = getInt();
        while((t=getInt())!=-1) {
            in[i].push_back(t-1);
            out[t-1].push_back(i);
        }
    }
    for(int i=0; i<n; ++i) {
        // printf("dfs... %d\n",i);
        putInt(ts(i, in, out, cost));
        enter();
    }

    return 0;
}