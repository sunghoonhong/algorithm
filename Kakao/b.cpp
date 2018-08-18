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
    인형들

    누적합

    a와 a^2의 누적합을 계산해두면
    평균(m)은 sum(a)[i:j]/(j-i+1),
    표준편차를 sum(a^2)[i:j]/(j-i+1)-m^2
    으로 O(1)에 계산할 수 있다.

    개선한 코드인데, 계속 오답이 나온다.
    도대체 뭐가 문제지...
*/


int sum[502];   // sum[a,b] = sum[b]-sum[a-1]
int sqr[502];

double stdv(int b, int e) {
    double m = sum[e]-sum[b-1];
    double m2 = sqr[e]-sqr[b-1];
    cout << m << ' ' << m2 << endl;
    int len = e-b+1;
    m/=len;
    return sqrt(m2/len - m*m);
}

int main() {
    int n=getInt(), k=getInt();
    for(int i=1,t; i<=n; ++i) {
        t=getInt();
        sum[i] = sum[i-1]+t;
        sqr[i] = sqr[i-1]+t*t;
        // cout << sum[i] << ' ' << sqr[i] << endl;
    }
    double ans = INF;
    for(int i=1; i<=n; ++i) {
        for(int j=i+k-1; j<=n; ++j) {
            // printf("%.12lf\n",stdv(i,j));
            ans = min(ans, stdv(i,j));
        }
    }
    printf("%.12lf\n", ans);
    // for(uint i=1; i<=500; ++i) printf("%d ", (i*i*i*23/47)%100+400);
    return 0;
}