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
    검문

    공약수

    a[]가 주어지면 모든 인접한 원소간의 차이들의 공약수를 구하자.
*/

int main() {
    int n = getInt();
    vInt a(n);
    for(int i=0; i<n; ++i) a[i] = getInt();
    sort(a.begin(), a.end());
    int Gcd = a[1]-a[0];
    for(int i=1; i<n-1; ++i) {
        Gcd = gcd(Gcd, a[i+1]-a[i]);
    }
    vInt ans;
    for(int i=2; i*i<=Gcd; ++i) {
        if(Gcd%i==0) {
            ans.push_back(i);
            if(i*i!=Gcd) ans.push_back(Gcd/i);
        }
    }
    sort(ans.begin(), ans.end());
    for(int i=0; i<ans.size(); ++i) {
        putInt(ans[i]); enter();
    }
    putInt(Gcd);

    return 0;
}