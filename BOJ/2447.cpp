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
    별찍기

    N = 3^k (0<=k<8)
    N = 27 = 3^3, k = 3 일때,
    가로 27 = N
    세로 27 = N
    k=0일때 N=1  
    *
    
    k=1일때 N=3
    ***     S(0)S(0)S(0)
    * *     S(0)    S(0)
    ***     S(0)S(0)S(0)
    
    k=2일떄 N=9
    k=1일때의 그림을 S(1)라 하면,
    S(1)S(1)S(1)
    S(1)    S(1)
    S(1)S(1)S(1)

    S(k) = {
        S(k-1)S(k-1)S(k-1)
        S(k-1)      S(k-1)
        S(k-1)S(k-1)S(k-1)
    }
    S(3^k) = S(N)이므로
    S(3^(k-1)) = S(N/3)

    S(9) = {
        S(3)S(3)S(3)
        S(3)    S(3)
        S(3)S(3)S(3)
    }
    S(N,0,0) = 0,0부터 S(N)그리기
    N=1: S(1,y,x) = (y,x)에 *찍기
    N>1: S(N,y,x) 는 아래와 같이
    S(N/3,0,0)S(N/3,0,N/3)S(N/3,0,2*N/3)
    S(N/3,N/3,0)         S(N/3,N/3,2*N/3)
    S(N/3,2*N/3,0)S(N/3,2*N/3,N/3)S(N/3,2*N/3,2*N/3)
*/

void draw(int x, int y, int n, vvBool &matrix) {
    if(n==1) {
        matrix[y][x]=true;
    }
    else {
        int d = n/3;
        for(int i=0; i<3; ++i) {
            for(int j=0; j<3; ++j) {
                if(i==1 && j==1) continue;
                draw(x+i*d,y+j*d,d,matrix);
            }
        }
    }
}

int main() {
    int n = getInt();
    vvBool matrix(n, vBool(n,false));
    draw(0,0,n,matrix);
    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            if(matrix[i][j]) putchar('*');
            else putchar(' ');
        }
        enter();
    }
    return 0;
}