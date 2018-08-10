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
    Z
    분할 정복
    
    N=1일 때를 기본으로해서,
    N=k일 때 어떻게 할지 고민해보자.
    
    x,y라는 변수명과 r,c 변수 사이의 관계에 유의하자.
    좌표평면상에서는 x는 c, y는 r에 대응한다.
    
    N=1일때는
    01
    23
    F(x,y,1): (y,x)부터 N=1일때 순서를 쓰면,
    (y,x), (y,x+1), (y+1,x), (y+1,x+1)
    순으로 방문한다.
    F(x,y,2)=
    F(x,y,1),F(x+2,y,1),F(x,y+2,1),F(x+2,y+2,1)
    F(x,y,n)=
    F(x,y,n-1),F(x+2^(n-1),y,n-1),...
    과 같은 관계가 생긴다.

    # 개선점
    순진하게 처음부터 끝까지 순회하지않고,
    분할시에 어떤 사분면에 속하는 지에 따라
    시작위치를 한번에 옮길수 있다.

*/

int ans = 0;
bool solved = false;
int r, c;

void drawZ(int x, int y, int n) {
    if(solved) return;
    if(n==1) {
        for(int i=0; i<2; ++i) {
            for(int j=0; j<2; ++j) {
                // printf("%d, %d: %d\n",x+j, y+i,ans);
                if(x+j==c&&y+i==r) {
                    solved = true;
                    return;
                }
                ans++;
            }
        }
    }
    else {
        int d=1;
        for(int i=0; i<n-1; ++i, d*=2);
        for(int i=0; i<2; ++i) {
            for(int j=0; j<2; ++j) {
                drawZ(x+d*j,y+d*i,n-1);
            }
        }
    }

}
int main() {
    int n = getInt();
    r = getInt();
    c = getInt();
    drawZ(0,0,n);
    putInt(ans);
    return 0;
}