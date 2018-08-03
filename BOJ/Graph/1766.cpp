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

    dfs로 하지말고, 순수하게 위상정렬의 관점에서 생각해보자.
    그다음 그 순서대로 다음과 같이 위상정렬을 한다.
    0. 진입간선만 필요하므로 오히려 간선의 방향을 바꿔주면 세기 편할듯하다.
    ex) (1,2)면 1->2였지만 (2,1)이 1->2 인걸로 하면 진입간선을 세기 편하다.
    1. 진입간선이 없는 노드를 찾는다.
    1.1. 검색순서를 오름차순으로 하면 조건3이 보장된다.
    보류: 1-1. 우선순위큐로 정렬된 상태이므로, 1을 만족하며 최소인 노드가 선택된다.
    2. 노드와 모든 진출간선을 지우고 해당 노드를 정답리스트의 뒤에 추가한다.
    3. 1~2를 반복한다.
*/

typedef sint::iterator iter;

void del_outs(vector<sint>& in, vector<sint>& out, int v) {
    for(iter i=out[v].begin(); i!=out[v].end(); ++i) {
        in[*i].erase(in[*i].find(v));
        // printf("%d->%d erased\n", v, *i);
    }
}

void ts(vector<sint>& in, vector<sint>& out, dqint& ans) {
    int n = in.size();
    vbool visited(n, false);
    while(ans.size()!=in.size()) {
        for(unsigned int i=0; i<in.size(); ++i) {
            if(!visited[i] && in[i].empty()) {
                // printf("%d selected\n", i);
                del_outs(in,out,i);
                visited[i] = true;
                ans.push_back(i+1);
                break;
            }
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    vector<sint> in(n);
    vector<sint> out(n);
    dqint ans;
    int a, b;

    for(int i=0; i<m; ++i) {
        scanf("%d %d", &a, &b);
        in[b-1].insert(a-1);
        out[a-1].insert(b-1);
    }
    // for(int i=0; i<n; ++i) {
    //     printf("out[%d]: ",i);
    //     for(unsigned j=0; j<out[i].size(); ++j) {
    //         cout << *next(out[i].begin(), j) << ' ';
    //     }
    //     cout << endl;
    // }
    ts(in, out, ans);
    cout << ans[0];
    for(int i=1; i<n; ++i) {
        cout << ' ' << ans[i];
    }
    return 0;
}