#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <array>
#include <vector>
#include <queue>
#include <deque>
#include <map>
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
inline string getWord(size_t &max_size) {
    int len = 0;
    char ch, cstr[max_size+1];
    for(int i=0; isalpha(ch=getchar()); ++i, ++len) cstr[i] = ch;
    return string(cstr, len);
}
inline ll getLL() {ll n; scanf("%lld", &n); return n;}
inline ull getULL() {ull n; scanf("%llu", &n); return n;}
inline void putInt(int n) {printf("%d", n);}
inline void enter() {putchar('\n');}

/*
    축사 배정

    네트워크 플로우(이분매칭)

    n마리의 소와 m개의 축사가 주어지고,
    각 소가 가고싶은 축사가 주어진다. (가고싶은 축사만 간다)
    그때 축사에 들어있는 소의 최대값을 구하자.

    n개의 집단과 m개의 집단간의 최대 매칭수를 구하는 문제다.
    시작점과 끝점을 새로 만들고 각각 1로 이어주고 네트워크 플로우로 풀면 된다.

    하지만 이분매칭은 DFS로도 간단히 풀 수 있다.
*/

vvInt prefer;
vInt barn;
int n,m;

bool dfs(int b, vBool &visited) {
    if(visited[b]) return false;
    visited[b] = true;
    for(int i=0, there; i<prefer[b].size(); ++i) {
        there = prefer[b][i];
        if(barn[there]==-1 || dfs(barn[there], visited)) {
            barn[there]=b;
            return true;
        }
    }
    return false;
}

int match() {
    int ret = 0;
    for(int i=0; i<n; ++i) {
        vBool visited(m, false);
        if(dfs(i, visited)) ret++;
    }
    return ret;
}

int main() {
    n=getInt(); m=getInt();
    prefer.resize(n);
    barn.resize(m, -1);
    
    for(int i=0, t, a; i<n; ++i) {
        t = getInt();
        prefer[i].resize(t);
        // cout << i << ": " << endl;
        for(int j=0; j<t; ++j) {
            prefer[i][j]=getInt()-1;
            // cout << prefer[i][j] << endl;
        }
        // enter();
    }
    putInt(match());

    return 0;
}