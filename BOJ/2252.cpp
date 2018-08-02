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

typedef vector<int> vint;
typedef vector<bool> vbool;
typedef deque<int> dqint;
/*
    위상 정렬(Topological Sort)
    'A가 B보다 앞에 선다.' 라는 조건이 있다.
    이런 조건들은 순서를 지정해준다.
    즉 위상 정렬을 사용해서 선후 관계(누가 앞에 오느냐)를 정해주는 것이다.

    위상정렬은 곧 DFS 경로의 역과 같다.

*/

void adfs(int v, vector<vint> &g, vbool &visited, dqint &ans) {
    visited[v] = true;
    for(unsigned int i=0; i<g[v].size(); ++i) {
        if(!visited[g[v][i]]) {
            adfs(g[v][i], g, visited, ans);
        }
    }
    ans.push_front(v+1);
    
}
void dfs(vector<vint> &g, dqint &ans) {
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
    int l, r;
    vector<vint> g(n);
    dqint ans;
    for(int i=0; i<m; ++i) {
        scanf("%d %d", &l, &r);
        g[l-1].push_back(r-1);
    }
    dfs(g, ans);
    cout << ans[0];
    for(unsigned int i=1; i<ans.size(); ++i) {
        cout << ' ' << ans[i];
    }

    return 0;
}