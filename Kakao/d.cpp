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

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vInt;
typedef vector<vInt> vvInt;
typedef vector<bool> vBool;
typedef vector<vBool> vvBool;
typedef deque<int> dqInt;

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


typedef pair<ll, ll> P2;

void putP(P2 a) {printf("(%lld, %lld)",a.first,a.second);}

bool equal(P2 a, P2 b) {return a.first==b.first && a.second==b.second;}

ll d2(P2 a, P2 b) {
    return (a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second);
}

bool possible(P2 b, P2 e, ll x, vector<P2> &cp) {
    P2 vert = make_pair(e.first, b.second);
    P2 hori = make_pair(b.first, e.second);
    printf("x: %d\n", x);
    if(x==0) {
        putP(b); cout << "->"; putP(e); cout << ' ' << (b.first==e.first||b.second==e.second) << endl;
        if(b.first==e.first || b.second==e.second) {
            return true;
        }
        else {
            cout << "check nearby checkpoint\n";
            for(unsigned int i=0; i<cp.size(); ++i) {
                if(cp[i]!=b) {
                    if(cp[i]==vert || cp[i]==hori) {
                        putP(cp[i]); cout << "... \n";
                        return possible(cp[i], e, x, cp);
                    }
                }
            }
        }
    }
    else{
        cout << d2(b,e) << ' ' << d2(b,vert) << ' ' << d2(b,hori) << ' ' << x*x << endl;
        if(d2(b, e) <= x*x) {return true;}
        else {
            if(d2(b, vert) < x*x) {
                // e가 있는 수직선으로 갈수있는가?
                cout << "check vertical\n";
                for(unsigned int i=0; i<cp.size(); ++i) {
                    if(cp[i]!=vert) {
                        if(possible(vert,cp[i],0,cp)) {
                            return possible(cp[i], e, x, cp);
                        }
                    }
                }
            }
            else if(d2(b, hori) < x*x) {
                // e가 있는 수평선으로 갈수있는가?
                cout << "check horizontal\n";
                for(unsigned int i=0; i<cp.size(); ++i) {
                    if(cp[i]!=hori) {
                        if(possible(hori,cp[i],0,cp)) {
                            return possible(cp[i], e, x, cp);
                        }
                    }
                }
            }
            else {
                // e로 직접 또는 수직 수평선에 갈 수 없다.
                // 그럼 부스터만으로는 갈 수 있는가?
                cout << "check booster\n";
                return possible(b, e, 0, cp);
            }
        }
    }
    return false;
}

int main() {
    ll n,q;
    n=getInt(); q=getInt();
    vector<P2> cp(n);
    for(ll i=0,a,b; i<n; ++i) {
        a=getInt(); b=getInt();
        cp[i] = make_pair(a,b);
        putP(cp[i]);
        enter();
    }
    for(ll i=0,a,b,x; i<q; ++i) {
        a=getInt()-1;
        b=getInt()-1;
        x=getInt();
        if(possible(cp[a],cp[b],x, cp)) {
            printf("YES\n");
        }
        else printf("NO\n");
    }
    return 0;
}