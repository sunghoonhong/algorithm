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
    divide(n): n을 서로다른 두 자연수를 더해서 만들 수 있는가?
    divide(n) = {
        n=0: true;
        n<20: check(n);
        divide(n/10) & check(n%10)
        or
        divide((n-10)/10) & check(n%10+10)
    }

     - 해결과제: check할때 0이 실제 0인지 아닌지 구분필요!
     ex) 54321 = 54320+1이 안됨. 이유는 54320 + 00001이되면
     (0,5),(0,4),(0,3),(0,2),(0,1)
     이렇게 되면 0이 계속 포함되버린다.
     게다가 위에서 (0,1)말고 (1,0)으로하면 딱 좋은데,
     그런 순서를 정하는 것도 필요하다.
*/

typedef vector<vector<pair<int, int> > > Cases;

vInt itov(int n) {
    vInt num;
    int t = n;
    while(t) {
        num.push_back(t%10);
        t/=10;
    }
    reverse(num.begin(), num.end());
    return num;
}

int vtoi(vInt &v) {
    int num = 0;
    int pow = 1;
    for(int i=v.size()-1; i>=0; --i, pow*=10) {
        num += v[i]*pow;
    }
    return num;
}

int pow10(int i) {
    int ret = 1;
    while(i--) {ret*=10;}
    return ret;
}

bool check(int digit, vBool &seen, Cases &cases, vInt &ans) {
    // printf("check %d\n", digit);
    // printf("seen\n");for(int i=0; i<10; ++i)printf("[ %d ]: %d\n",i,(int)seen[i]);
    for(int j=0; j<cases[digit].size(); ++j) {
        if(!seen[cases[digit][j].second]) {
            if(ans.size()>0 && ans[0]>0 && digit<10) {
                if(j==0) continue;
            }
            if(!seen[cases[digit][j].first]) {
                pair<int,int> p = cases[digit][j];
                seen[p.first]=true;
                seen[p.second]=true;
                ans.push_back(p.first);
                // printf("%d %d\n", p.first, p.second);
                return true;
            }
        }
    }
    // printf("fail\n");
    return false;
}

int divide(int n, vBool &seen, Cases &cases, vInt &ans) {
    vBool tempseen(seen);
    vInt tempans(ans);

    if(n==0) return true;
    if(n<18) {
        if(check(n, tempseen, cases, tempans)) {
            seen = tempseen;
            ans = tempans;
            return true;
        }
        else return false;
    }
    int ret = divide(n/10, tempseen, cases, tempans);
    if(ret) {
        if(check(n%10, tempseen, cases, tempans)) {
            seen = tempseen;
            ans = tempans;
            return true;
        }
    }
    tempseen = seen;
    tempans = ans;
    ret = divide(n/10-1, tempseen, cases, tempans);
    if(ret) {
        if(check(n%10+10, tempseen, cases, tempans)) {
            seen = tempseen;
            ans = tempans;
            return true;
        }
    }
    return false;
}

int main() {
    int n = getInt();
    if(n<3)  {
        putInt(-1);
        return 0;
    }
    if(n<10) {
        putInt(1);
        printf(" + ");
        putInt(n-1);
        return 0;
    }
    Cases cases(20);
    for(int i=0; i<10; ++i) {
        for(int j=0; j<(i+1)/2; ++j) {
            cases[i].push_back(make_pair(j, i-j));
        }
        for(int j=i+1; j<(i+1)/2+5; ++j) {
            cases[i+10].push_back(make_pair(j, i-j+10));
        }
    }
    // for(int i=0; i<20; ++i) {
    //     printf("%d: ",i);
    //     for(int j=0; j<cases[i].size(); ++j) {
    //         printf("%d %d / ", cases[i][j].first, cases[i][j].second);
    //     }
    //     enter();
    // }
    vBool seen(10, false);
    vInt ans;
    bool possible = divide(n, seen, cases, ans);
    // for(uint i=0; i<ans.size(); ++i) {printf("%d ",ans[i]);}enter();
    // printf("seen\n");for(int i=0; i<10; ++i)printf("[ %d ]: %d\n",i,(int)seen[i]);
    if(!possible) {
        putInt(-1);
        return 0;
    }
    else {
        int first = vtoi(ans);
        putInt(first);
        printf(" + ");
        putInt(n-first);
    }
    return 0;
}