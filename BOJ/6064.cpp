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
    카잉 달력

    <m,n>이 마지막 해일때,
    <x,y>는 몇번째 해인가?
    x,y가 각각 m,n의 주기로 반복되므로
    x+m*k == y+n*l 인 지점을 찾으면 된다.
    마지막해는 lcm(m,n) = m*n/gcd(m,n)
    
    m,n<4*10^4
*/

void swap(int &a, int &b) {int t=a; a=b; b=t;}
int gcd(int a, int b) {
    if(a<b) swap(a,b);
    // int t;
    // while(b) {t=a%b; a=b; b=t;}
    for(int t; b; t=a%b, a=b, b=t);
    return a;
}

int main() {
    int t = getInt();
    while(t--) {
        int m=getInt();
        int n=getInt();
        int x=getInt();
        int y=getInt();
        int end = m*n/gcd(m,n);
        int ans = -1;
        for(int i=x; i<=end; i+=m) {
            if((i-y)%n==0) {
                ans=i;
                break;
            }
        }        
        putInt(ans); enter();
    }
    return 0;
}