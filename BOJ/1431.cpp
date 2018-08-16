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
    시리얼 번호

    문자열 정렬
*/

// vInt sum;
bool compare(string &a, string &b) {
    if(a.size()!=b.size()) return a.size() < b.size();
    int suma=0, sumb=0;
    for(int i=0; i<a.size(); ++i) if(isNum(a[i])) suma+=a[i]-'0';
    for(int i=0; i<b.size(); ++i) if(isNum(b[i])) sumb+=b[i]-'0';
    if(suma!=sumb) return suma < sumb;
    return a < b;
}

int main() {
    int n = getInt();
    vector<string> serial(n);
    // sum.resize(n,0);
    for(int i=0; i<n; ++i) {
        cin >> serial[i];
        // for(int j=0; j<serial[i].size(); ++j) {
        //     if(isNum(serial[i][j]) {
        //         sum[i]+=serial[i][j]-'0';
        //     }
        // }
    }
    sort(serial.begin(), serial.end(), compare);
    for(int i=0; i<n; ++i) {
        cout << serial[i] << endl;
    }
    return 0;
}