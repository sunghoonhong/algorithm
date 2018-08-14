#include <iostream>
#include <cstdio>
#include <string>
#include <string.h>
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
inline string getWord(size_t max_size) {
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
    친구 네트워크

    Disjoint Set

    이름 두개가 주어지면 두 이름은 같은 집합에 속한다.
    그 둘이 속한 집합의 개수를 구하자.
    m < 10^5

    rank와 경로압축을 이용한 트리형 disjoint set을 사용했다.

    시간에 영향을 주는 부분은 union 부분과
    문자열 입력 부분이다.
    union은 rank와 경로압축을 이용했기 때문에 괜찮다.
    문자열 입력은 getchar()로 구현해봤다.

    # 개선할 점
    원소값이 string이기 때문에 map을 사용했는데,
    대신에 hash를 직접 구현한다면 시간을 훨씬 줄일 수 있다.
*/

typedef struct Element {
    string parent;
    int rank;
    int weight;
} Element;

void swap(int &a, int &b) {
    int t = a; a = b; b = t;
}

string find_set(string a, map<string, Element> &net) {
    string p = net[a].parent;
    if(p==a) return p;
    return net[a].parent = find_set(p, net);
}

int union_set(string a, string b, map<string, Element> &net) {
    string pa = find_set(a, net);
    string pb = find_set(b, net);
    if(pa==pb) return net[pa].weight;

    if(net[pa].rank < net[pb].rank) swap(pa,pb);
    if(net[pa].rank == net[pb].rank) net[pa].rank++;
    net[pb].parent = pa;
    return net[pa].weight += net[pb].weight;
}

int main() {
    int t = getInt();
    while(t--) {
        int n = getInt();
        map<string, Element> net;
        while(n--) {
            string a = getWord(20), b = getWord(20);
            Element A = {a,0,1}, B = {b,0,1};
            if(net.find(a)==net.end()) net.insert(make_pair(a,A));
            if(net.find(b)==net.end()) net.insert(make_pair(b,B));
            putInt(union_set(a,b,net));         
            enter();
        }
    }
    return 0;
}