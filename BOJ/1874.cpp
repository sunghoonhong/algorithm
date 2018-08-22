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
    스택 수열

    스택

    n이하의 자연수들로 스택을 이용하여 해당 수열을 만들 수 있는가?
    (n<=1e5)

    현재까지의 최댓값보다 작은 수가 나오는 경우 무조건 내림차순을 지켜야한다.
    
    여러 방법을 생각해봤지만 실제 스택을 사용하는 것보다 깔끔한 방법을 찾지 못했다.
    더 깔끔하고 좋은 방법이 있으면 개선해보자.
*/
#include <stack>

int main() {
    int n = getInt();
    string a;
    stack<int> s;
    for(int i=0, t, mx=0; i<n; ++i) {
        t = getInt();
        if(mx<t) {
            for(int j=0; j<t-mx; ++j) {
                a+="+\n";
                s.push(mx+j+1);
            }
            s.pop();
            a+="-\n";
            mx=t;
        }
        else {
            if(s.top()!=t) {
                printf("NO");
                return 0;
            }
            s.pop();
            a+="-\n";
        }
    }
    cout << a;
    return 0;
}