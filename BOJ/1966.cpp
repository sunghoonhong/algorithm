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

void swap(int &a, int &b) {int t=a; a=b; b=t;}
int gcd(int a, int b) {
    if(a<b) swap(a,b);
    for(int t; b; t=a%b, a=b, b=t);
    return a;
}

/*
    프린터 큐

    큐

    중요도를 고려한 큐
    프론트보다 중요도가 높은 원소가 있다면 프론트를 뒤로 넘긴다.
    프론트가 가장 중요도가 높다면 바로 꺼낸다.

    실패)
    그냥 내림차순으로 정렬 후에 중복 원소 간의 순서만 고려하자.
    원소간의 순서와 실제 결과와는 차이가있다.

    해결)
    그냥 큐로 직접 시뮬레이션 해보자.
    중요도의 최댓값은 미리 중요도를 내림차순 정렬해놓고 인덱스를 바꾸는 것으로 계산하자

    개선)
    큐로 해도 되지만, 그냥 배열로 해도 문제없다.
    어차피 큐의 상태가 중요한게 아니라 인쇄되는 순서만 고려하면된다.
    0번째 원소부터 차례로 보면서
    인덱스가 n보다 커질 경우에 다시 n을 빼주거나, %n으로 계속 할 수 있게 해줘도된다.

*/

int main() {
    int t = getInt();
    while(t--) {
        int n = getInt(), m = getInt();
        int a[101], mx[101];
        for(int i=0; i<n; ++i) {
            a[i] = getInt();
            mx[i] = a[i];
        }
        int maxidx=n-1, ans=0;
        sort(mx,mx+n);
        for(int i=0; i<n; ++i) {
            if(a[i]==mx[maxidx]) {
                if(i==m) break;
                maxidx--;
                ans++;
            }
            if(i==n-1) i-=n;
        }
        putInt(ans+1); enter();
    }
    return 0;
}