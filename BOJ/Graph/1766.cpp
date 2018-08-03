#include <iostream>
#include <cstdio>
#include <string>
#include <string.h>
#include <array>
#include <vector>
#include <queue>
#include <deque>
#include <set>
#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

typedef vector<int> vint;
typedef vector<vint> vvint;
typedef vector<bool> vbool;
typedef vector<vbool> vvbool;
typedef deque<int> dqint;
typedef set<int> sint;

/*
    위상 정렬(Topological Sort)
    위상 정렬을 통해 선후 관계, 우선 순위를 정할 수 있다.
    기본적인 순서조건는 조건 1,2를 만족시킬 수 있다.
    가설:
    조건 3은 g[k]=[k보다 큰 수]로 관계를 추가하는 것으로 해겷.
    단, 입력받은 기존의 순서가 있으면 추가목록에서 제외하자.

    가설:
        dfs()에서 vertex를 고르는 순서를 미리 정렬해볼까?
*/


typedef sint::iterator iter;

void adfs(int v, vector<sint> &g, vbool &visited, dqint &ans) {
    printf("visit... %d\n", v);
    visited[v] = true;
    for(iter i=g[v].begin(); i!=g[v].end(); i++) {
        int link = *i;
        if(!visited[link]) {
            adfs(link, g, visited, ans);
        }
    }
    ans.push_front(v+1);
}

void dfs(vector<sint> &g, dqint &ans) {
    int n = g.size();
    vbool visited(n, false);
    for(int i=0; i<n; ++i) {
        if(!visited[i]) {
            adfs(i, g, visited, ans);
        }
    }
}

void test(int v, vector<sint> &g, dqint &ans) {
    int n = g.size();
    vbool visited(n, false);
    for(int i=0; i<n; ++i) {
        if(!visited[i]) {
            adfs(i, g, visited, ans);
        }
    }
}


int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    vector<sint> g(n);
    dqint ans(n);
    int a, b;

    for(int i=0; i<m; ++i) {
        scanf("%d %d", &a, &b);
        g[a-1].insert(b-1);
    }
    for(int i=0; i<n; ++i) {
        if(g[i].empty()) {
            for(int j=i+1; j<n; ++j) {
                if(g[j].find(i)==g[j].end()) {
                    // g[i].insert(j);
                    break;
                }
            }
        }
    }
    for(int i=0; i<n; ++i) {
        printf("g[%d]: ",i);
        for(unsigned j=0; j<g[i].size(); ++j) {
            cout << *next(g[i].begin(), j) << ' ';
        }
        cout << endl;
    }
    dfs(g, ans);
    cout << ans[0];
    for(int i=1; i<n; ++i) {
        cout << ' ' << ans[i];
    }
    return 0;
}