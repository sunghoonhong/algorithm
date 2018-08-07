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
    divide(index, n, seen, cases) :
        n을 앞부터 볼때, index번째부터 본 숫자가 나눠질수있는지?
        지금 확인하는게 첫째자리면(index=0) 지금 자리가 서로 다른 두 자연수로 더해서 만들수 있는지.
        둘째자리라면(index=1) 그리고 첫째자리가 1이라면 더해서 carry가 생기는(두자연수를 더했을때 10이상이되는) 경우만을 확인.

        divide(index-1, n) && check(n[index])
        or
        divide(index-1, n에서 index-1자리에서 1뺸 수) && check(n[index]+10))

    - 문제점: carry가 넘어가는 경우를 확인할때 index가 제대로 붙지않는다.
    ex) div(20,1) = div(20,0)&check(0) || div(10,0)&check(10)
    인데 div(10,1)&check(10)로 되는게 맞다. index를 예외처리해야하는게 불편하다.
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
    int pow = v.size()-1;
    for(uint i=0; i<v.size(); ++i, pow/=10) {
        num += v[i]*pow;
    }
    return num;
}

int pow10(int i) {
    int ret = 1;
    while(i--) {ret*=10;}
    return ret;
}

bool check(int digit, vBool &seen, Cases &cases, pair<int, int> &p) {
    
    // printf("check %d\n", digit);
    // printf("seen\n");for(int i=0; i<10; ++i)printf("[ %d ]: %d\n",i,(int)seen[i]);
    for(int j=0; j<cases[digit].size(); ++j) {
        if(!(seen[cases[digit][j].first]|seen[cases[digit][j].second])) {
            p = cases[digit][j];
            seen[p.first]=true;
            seen[p.second]=true;
            // printf("%d %d\n", p.first, p.second);
            return true;
        }
    }
    // printf("fail\n");
    return false;
}

int divide(int index, int n, vBool &seen, Cases &cases) {
    vInt num = itov(n);
    int end = num.size()-1;
    // printf("num: ");for(int i=0; i<num.size(); ++i) printf("%d",num[i]); enter();
    if(index<0) index++;
    int digit = num[index];
    // printf("%d째자리 %d을 체크하자\n",index, digit);
    pair<int, int> correct;
    vBool tempseen(seen);
    int ans;
    if(index==0) {
        // 지금이 맨 앞자리다.
        tempseen = seen;
        if(digit==0) {
            // printf("%d째자리 0 성공!\n", index);
            return 0;
        }
        else if(check(digit, tempseen, cases, correct)) {
            seen = tempseen;
            // printf("%d째자리 성공!\n", index);
            return correct.first*pow10(end-index);
        }
        else {
            // printf("%d째자리 실패...\n", index);
            return -1;
        }
    }
    if(index==1) {
        // 지금이 앞에서 두번째 자리다.
        tempseen = seen;
        if(num[0]==1 && check(digit+10, tempseen, cases, correct)) {
            seen = tempseen;
            // printf("%d째자리 10이상 성공!\n", index);
            return correct.first*pow10(end-index);
        }
        // else {
        //     ans = divide(index-1, n, seen, cases);
        //     if(ans>-1) {
        //         tempseen = seen;
        //         if(check(digit, tempseen, cases, correct)) {
        //             seen = tempseen;
        //             printf("%d째자리 10이하 성공!\n", index);
        //             ans+=correct.first*pow10(num.size()-1-index);
        //             return ans;
        //         }
        //     }
        //     printf("%d째자리 실패...\n", index);
        //     return -1;
        // }
    }
    tempseen = seen;
    ans = divide(index-1, n, tempseen, cases);
    if(ans>-1) {
        if(check(digit, tempseen, cases, correct)) {
            seen = tempseen;
            // printf("%d째자리 10이하 성공!\n", num.size()-index);
            ans+=correct.first*pow10(end-index);
            return ans;
        }
        // printf("%d째자리 10이하 실패...\n", num.size()-index);
    }
    tempseen = seen;
    ans = divide(index-1, n-pow10(end+1-index), tempseen, cases);
    if(ans>-1) {
        if(check(digit+10, tempseen, cases, correct)) {
            seen = tempseen;
            // printf("%d째자리 10이상 성공!\n", num.size()-index);
            ans+=correct.first*pow10(end-index);
            return ans;
        }
        // printf("%d째자리 10이상 실패...\n", num.size()-index);
    }
    return -1;
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
    int ans = divide(itov(n).size()-1, n, seen, cases);
    // printf("seen\n");for(int i=0; i<10; ++i)printf("[ %d ]: %d\n",i,(int)seen[i]);
    if(ans==-1) {
        putInt(-1);
        return 0;
    }
    putInt(ans);
    printf(" + ");
    putInt(n-ans);
    return 0;
}