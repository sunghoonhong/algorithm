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
    책 나눠주기

    네트워크 플로우(이분매칭)

    n권의 책과 m명의 학생이 있고,
    각 학생이 받고 싶은 책의 범위가 주어졌을때,
    그때 책을 받는 학생 수의 최댓값을 구하자.

    n<10^3 m<10^3

    m명의 집단이 n명의 집단과 매칭된다.
    n집단의 범위가 주어지므로,
    m집단에서 n집단의 범위만큼 간선을 이어주면 될듯하다.
*/

int n,m;

bool dfs(int b, vBool &visited, vvInt &prefer, vInt &book) {
    if(visited[b]) return false;
    visited[b] = true;
    for(int i=0, there; i<prefer[b].size(); ++i) {
        there = prefer[b][i];
        if(book[there]==-1 || dfs(book[there], visited, prefer, book)) {
            book[there]=b;
            return true;
        }
    }
    return false;
}

int match(vvInt &prefer, vInt &book) {
    int ret = 0;
    for(int i=0; i<m; ++i) {
        vBool visited(n, false);
        if(dfs(i, visited, prefer, book)) ret++;
    }
    return ret;
}

int main() {
    int t = getInt();
    while(t--) {
        n=getInt(); m=getInt();
        vvInt prefer(m);
        vInt book(n, -1);
        for(int i=0,a,b; i<m; ++i) {
            a=getInt()-1; b=getInt()-1;
            prefer[i].resize(b-a+1);
            // cout << i << ": ";
            for(int j=a; j<=b; ++j) {
                prefer[i][j-a]=j;
                // cout << prefer[i][j] << ' ';
            }
            // enter();
        }
        putInt(match(prefer, book));
        enter();
    }
    return 0;
}