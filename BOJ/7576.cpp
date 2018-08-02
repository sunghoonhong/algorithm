#include <iostream>
#include <cstdio>
#include <string>
#include <string.h>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

/*
보류:
처음에 DFS로 집합을 먼저 구한다.

BFS
그래프를 전체를 순서대로 보며 익은 토마토(1)마다 BFS를 해본다.
그때마다 (최대)depth를 구하고 그들의 최댓값을 구해준다.

ans = -1 일때: 전부를 채우지 못했을때.

전부를 채웠느냐... 는 bfs를 돌때마다 따로 공유하는 하나의 맵에 1로 체크해서 0이 남았는지 확인하자.
*/

bool complete(vector<vector<int> > check) {
    int m = check.size();
    int n = check[0].size();
    for(int i=0; i<m; ++i) {
        for(int j=0; j<n; ++j) {
            if(check[i][j]==0) {
                return false;
            }
        }
    }
    return true;
}

int bfs(vector<vector<int> > g, pair<int, int> s, vector<vector<int> > &check) {
    queue<pair<int, int> > q;
    int depth = -1;
    int m=g.size();
    int n=g[0].size();
    vector<vector<bool> > visited(m, vector<bool>(n, false));
    visited[s.first][s.second] = true;
    q.push(s);
    while(!q.empty()) {
        cout << "Simulation...";
        cout << depth << endl;
        for(int i=0; i<m; ++i) {
            for(int j=0; j<n; ++j) {
                cout << g[i][j];
            }
            cout << endl;
        }
        queue<pair<int, int> > nextq;
        while(!q.empty()) {
            pair<int, int> u = q.front();
            q.pop();
            vector<pair<int, int> > link;
            int x = u.first;
            int y = u.second;
            printf("u: %d,%d\nL: ", x,y);
            // if(x>0) if(g[x-1][y]==0) link.push_back(make_pair(x-1, y));
            // if(x<n-1) if(g[x+1][y]==0) link.push_back(make_pair(x+1, y));
            // if(y>0) if(g[x][y-1]==0) link.push_back(make_pair(x, y-1));
            // if(y<m-1) if(g[x][y+1]==0) link.push_back(make_pair(x, y+1));
            if(x>0) if(g[x-1][y]!=-1) link.push_back(make_pair(x-1, y));
            if(x<m-1) if(g[x+1][y]!=-1) link.push_back(make_pair(x+1, y));
            if(y>0) if(g[x][y-1]!=-1) link.push_back(make_pair(x, y-1));
            if(y<n-1) if(g[x][y+1]!=-1) link.push_back(make_pair(x, y+1));
            
        
            for(int i=0; i<link.size(); ++i) {
                pair<int, int> t = link[i];
                printf("%d,%d ",t.first, t.second);
                if(!visited[t.first][t.second]) {
                    visited[t.first][t.second]=true;
                    g[t.first][t.second]=1;
                    check[t.first][t.second]=1;
                    nextq.push(t);
                }
            }
            cout << endl;
        }
        q=nextq;
        depth++;
    }
    return depth;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int> > g(m, vector<int>(n));
    for(int i=0; i<m; ++i) {
        for(int j=0; j<n; ++j) {
            cin >> g[i][j];
        }
    }
    vector<vector<int> > check = g;
    cout << "Step...\n";
    
    int ans = -1;
    int t;
    for(int i=0; i<m; ++i) {
        for(int j=0; j<n; ++j) {
            if(g[i][j]==1) {
                t = bfs(g, make_pair(i, j), check);
                if(ans<t) ans = t;
            }
        }
    }
    if(complete(check)) cout << ans;
    else cout << -1;
    return 0;
}