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


typedef pair<int, int> P2;
typedef vector<P2> vP2;
void putP(P2 a) {printf("(%lld, %lld)",a.first,a.second);}

int d2(P2 a, P2 b) {
    return (a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second);
}

int diff(int x) {return x>0?x:-x;}
bool direct(P2 a, P2 b, ll x) {
    return diff(a.first-b.first)<=x || diff(a.second-b.second)<=x;
}

bool possible(int B, int E, int x, vP2 &list, vBool &visited) {
    P2 b=list[B], e=list[E];
    visited[E] = true;
    // cout << x  << ' '; putP(b); putchar(' '); putP(e); cout << endl;
    if(direct(b,e,x)) {
        return true;
    }
    else {
        for(unsigned int i=0; i<list.size(); ++i) {
            if(!visited[i] && direct(list[i], e, x)) {
                if(possible(B, i, x, list, visited)) {
                    return true;
                }
            }
        }
        return false;
    }
}

int main() {
    int n,q;
    n=getInt(); q=getInt();
    vP2 list(n);
    for(int i=0,a,b; i<n; ++i) {
        a=getInt(); b=getInt();
        list[i] = make_pair(a,b);
    }
    for(int i=0,a,b,x; i<q; ++i) {
        vBool visited(n, false);
        a=getInt()-1;
        b=getInt()-1;
        x=getInt();
        if(possible(a,b,x,list,visited)) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}