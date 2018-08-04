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

int prize(int a, int b) {
    int pa=0, pb=0;
    if(a) {
        int i=1, rank=1;
        int reward[6] = {500, 300, 200, 50, 30, 10};
        while(i<=21) {
            if(a<=i) {
                pa=reward[rank-1];
                break;
            }
            i+=++rank;
        }
    }
    if(b) {
        int i=1, j=1, rank=1, reward=512;
        while(i<=31) {
            if(b<=i) {
                pb=reward;
                break;
            }
            j*=2;
            i+=j;
            rank++;
            reward/=2;
        }
    }
    return pa+pb;
}

int main() {
    int t = getInt();
    for(int i=0,a,b; i<t; ++i) {
        a = getInt();
        b = getInt();
        putInt(prize(a,b)*10000);
        enter();
    }
    return 0;
}