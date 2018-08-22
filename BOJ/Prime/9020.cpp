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
    골드바흐의 추측

    짝수 n을 두 소수의 합으로 표현해보자.
    n <= [4,10000]
    답이 여러가지인 경우 두 소수의 차이가 작은 쪽으로 하자.

    에라토스테네스의 체로 미리 걸러놓고 O(nloglogn)

    소수인 a에 대해 b=n-a일때, b도 소수인지 체크하면된다.
    a,b의 차이가 가장 작은 경우를 찾기 때문에
    n/2부터 내림차순으로 찾으면 될듯하지만
    이번엔 소수를 따로 저장해놓았으므로,
    그냥 2부터 오름차순으로 보도록 하자.
*/

const int MAX = 10000;
const int sqrtmax = 100;
bool seen[MAX+1]={1,1};
vInt prime;

void eratos() {
    for(int i=2; i<=sqrtmax; ++i) {
        if(seen[i]) continue;
        for(int j=i*2; j<=MAX; j+=i) {
            seen[j] = true;
        }        
    }
    prime.reserve(MAX);
    for(int i=2; i<=MAX; ++i) {
        if(!seen[i]) prime.push_back(i);
    }
}

int solve(int n) {
    int ans=0;
    for(int i=0; prime[i]*2<=n; ++i) {
        if(!seen[n-prime[i]]) ans = prime[i];
    }
    return ans;
}

int main() {
    eratos();
    int t = getInt();
    while(t--) {
        int n = getInt();
        int ans = solve(n);
        putInt(ans);
        putchar(' '); 
        putInt(n-ans);
        enter();
    }    
    return 0;
}