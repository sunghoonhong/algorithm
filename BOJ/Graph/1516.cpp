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
    각 건물마다 dfs로 끝점리스트(from)를 구하고,
    끝점리스트의 각 정점을 시작점,
    현재 건물을 끝점으로 해서 다익스트라로 풀어보자.
*/


void adfs(int v, vvint &in, vvint &out, vbool &visited, vint &ans, vvint &from, int start=-1) {
    visited[v] = true;
    if(in[v].empty()) {
        start = v;
    }
    for(unsigned int i=0; i<in[v].size(); ++i) {
        if(!visited[in[v][i]]) {
            adfs(in[v][i], in, out, visited, ans, from, start);
        }
    }
    if(start!=-1) from[start].push_back(v);
    ans.push_back(v);
}

vvint dfs(int v, vvint in, vvint out) {
    vint ans;
    vbool visited(in.size(), false);
    vvint from(in.size());
    adfs(v, in, out, visited, ans, from);
    for(int i=0; i<from.size(); ++i) {
        if(!from[i].empty()) {
            printf("start from %d: ", i+1);
            for(int j=0; j<from[i].size(); ++j) {
                putInt(from[i][j]+1); putchar(' ');
            }
            enter();
        }
    }
    return from;
}

int ts(int v, vvint in, vvint out, vint& cost) {
    vvint lists = dfs(v, in, out);
    int ans = 0;
    // cout << "DFS: ";
    for(unsigned int i=0; i<lists.size(); ++i) {
        if(!lists[i].empty()) {
            int temp = 0;
            printf("costs from %d... ", i+1);
            for(unsigned int j=0; j<lists[i].size(); ++j) {
                putInt(lists[i][j]+1); putchar(' ');
                temp += cost[lists[i][j]];
            }
            putInt(temp);
            if(ans<temp) ans=temp;
            enter();
        }
    }
    return ans+cost[v];
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
        printf("dfs... %d\n",i+1);
        putInt(ts(i, in, out, cost));
        enter();
    }

    return 0;
}