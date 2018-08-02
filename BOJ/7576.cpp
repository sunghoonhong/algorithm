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
BFS
익은 토마토(1)들을 첫번째 depth(시작점)으로 한다.
(원래 bfs는 1개의 시작점에서 시작하는 알고리즘이지만,
이 문제에서는 시작점의 인접 노드가 시작시 익은 토마토들로 생각)
모든 탐색이 끝난 후의 최종 depth값이 답.

ans = -1 일때: 전부를 채우지 못했을때.
전부를 채웠느냐... 는 bfs가 끝난 후 0이 남아있는지 확인.
*/

bool complete(vector<vector<int> > &g) {
    int n = g.size();
    int m = g[0].size();
    for(int i=0; i<n; ++i) {
        for(int j=0; j<m; ++j) {
            if(g[i][j]==0) {
                return false;
            }
        }
    }
    return true;
}

int bfs(vector<vector<int> > &g) {
    queue<pair<int, int> > q;
    int depth = -1;
    int n=g.size();
    int m=g[0].size();
    vector<vector<bool> > visited(n, vector<bool>(m, false));
    for(int i=0; i<n; ++i) {
        for(int j=0; j<m; ++j) {
            if(g[i][j]==1) {
                visited[i][j] = true;
                q.push(make_pair(i,j));
            }
        }
    }
    while(!q.empty()) {
        // cout << "Simulation... " << depth << endl;
        // for(int i=0; i<n; ++i) {
        //     for(int j=0; j<m; ++j) {
        //         cout << g[i][j];
        //     }
        //     cout << endl;
        // }
        queue<pair<int, int> > nextq;
        while(!q.empty()) {
            pair<int, int> u = q.front();
            q.pop();
            vector<pair<int, int> > link;
            int x = u.first;
            int y = u.second;
            // printf("u: %d,%d\nL: ", x,y);
            if(x>0) if(g[x-1][y]!=-1) link.push_back(make_pair(x-1, y));
            if(x<n-1) if(g[x+1][y]!=-1) link.push_back(make_pair(x+1, y));
            if(y>0) if(g[x][y-1]!=-1) link.push_back(make_pair(x, y-1));
            if(y<m-1) if(g[x][y+1]!=-1) link.push_back(make_pair(x, y+1));
            
        
            for(unsigned int i=0; i<link.size(); ++i) {
                pair<int, int> t = link[i];
                // printf("%d,%d ",t.first, t.second);
                if(!visited[t.first][t.second]) {
                    visited[t.first][t.second]=true;
                    g[t.first][t.second]=1;
                    nextq.push(t);
                }
            }
            // cout << endl;
        }
        q=nextq;
        depth++;
    }
    return depth;
}

int main() {
    int n, m;
    cin >> m >> n;
    vector<vector<int> > g(n, vector<int>(m));
    for(int i=0; i<n; ++i) {
        for(int j=0; j<m; ++j) {
            cin >> g[i][j];
        }
    }    
    int ans = bfs(g);
    if(complete(g)) cout << ans;
    else cout << -1;
    return 0;
}