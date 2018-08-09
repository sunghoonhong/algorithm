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
    트리의 부모 찾기
    루트 없는 트리가 주어진다.
    이 때, 트리의 루트를 1이라고 정했을 때,
    각 노드의 부모를 구하는 프로그램을 작성하시오.
    N<=100000

    먼저 연결관계만 입력받은 후에,
    1번 노드부터 순회하며 노드 간의 관계를 확인하자.
    1번은 루트로 가정하므로, 순서대로 연결된 것을 따라가면 된다.
    ex) 1번의 자식이 4라면, 4의 부모는 1이다.
    처음에는 연결사실만 알고있으므로,
    한번 확인한 노드는 재방문하지 않도록 체크하자.
*/

void probe(vvInt &connect, vInt &parents, vBool &visited, int start) {
    // cout << "probing " << start << endl;
    visited[start] = true;
    for(uint i=0; i<connect[start].size(); ++i) {
        int connected = connect[start][i];
        if(!visited[connected]) {
            parents[connected] = start;
            // cout << connected << "'s parent is " << start << endl;
            probe(connect, parents, visited, connected);
        }
    }
}

int main() {
    int n = getInt();
    vvInt connect(n);
    vInt parents(n);
    vBool visited(n, false);
    for(int i=0,a,b; i<n-1; ++i) {
        a=getInt(); b=getInt();
        connect[a-1].push_back(b-1);
        connect[b-1].push_back(a-1);
    }
    probe(connect, parents, visited, 0);
    for(int i=1; i<n; ++i) {
        putInt(parents[i]+1); enter();
    }
    return 0;
}