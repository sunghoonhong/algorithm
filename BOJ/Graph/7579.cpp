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

typedef vector<int> vec;
/*
BFS
익은 토마토(1)들을 첫번째 depth(시작점)으로 한다.
(원래 bfs는 1개의 시작점에서 시작하는 알고리즘이지만,
이 문제에서는 시작점의 인접 노드가 시작시 익은 토마토들로 생각)
모든 탐색이 끝난 후의 최종 depth값이 답.

ans = -1 일때: 전부를 채우지 못했을때.
전부를 채웠느냐... 는 bfs가 끝난 후 0이 남아있는지 확인.
*/

class point {
    public: 
        point(int X, int Y, int Z) {
            x=X;
            y=Y;
            z=Z;
        }
        int x, y, z;
};

bool complete(vector<vector<vec> > &g) {
    int x = g.size();
    int y = g[0].size();
    int z = g[0][0].size();
    for(int i=0; i<x; ++i) {
        for(int j=0; j<y; ++j) {
            for(int k=0; k<z; ++k) {
                if(g[i][j][k]==0) {
                    return false;
                }
            }
        }
    }
    return true;
}

int bfs(vector<vector<vec> > &g) {
    int x = g.size();
    int y = g[0].size();
    int z = g[0][0].size();
    deque<point> q;
    int depth = -1;
    vector<vector<bool> > visit(y, vector<bool>(z, 0));
    vector<vector<vector<bool> > > visited(x, visit);

    for(int i=0; i<x; ++i) {
        for(int j=0; j<y; ++j) {
            for(int k=0; k<z; ++k) {
                if(g[i][j][k]==1) {
                    visited[i][j][k] = true;
                    q.push_back(point(i,j,k));
                }
            }
        }
    }
    while(!q.empty()) {
        // cout << "Simulation... " << depth << endl;
        // for(int i=0; i<x; ++i) {
        //     for(int j=0; j<y; ++j) {
        //         for(int k=0; k<z; ++k) {
        //             cout << g[i][j][k];
        //         }
        //         cout << endl;
        //     }
        //     cout << endl;
        // }
        deque<point> nextq;
        while(!q.empty()) {
            point u = q.front();
            q.pop_front();
            // printf("u: %d,%d,%d\nL: ", u.x,u.y,u.z);
            vector<point> link;
            if(u.x>0 && g[u.x-1][u.y][u.z]!=-1) link.push_back(point(u.x-1,u.y,u.z));
            if(u.x<x-1 && g[u.x+1][u.y][u.z]!=-1) link.push_back(point(u.x+1,u.y,u.z));
            if(u.y>0 && g[u.x][u.y-1][u.z]!=-1) link.push_back(point(u.x,u.y-1,u.z));
            if(u.y<y-1 && g[u.x][u.y+1][u.z]!=-1) link.push_back(point(u.x,u.y+1,u.z));
            if(u.z>0 && g[u.x][u.y][u.z-1]!=-1) link.push_back(point(u.x,u.y,u.z-1));
            if(u.z<z-1 && g[u.x][u.y][u.z+1]!=-1) link.push_back(point(u.x,u.y,u.z+1));

            for(unsigned int i=0; i<link.size(); ++i) {
                point t = link[i];
                // printf("%d,%d,%d ",t.x,t.y,t.z);
                if(!visited[t.x][t.y][t.z]) {
                    visited[t.x][t.y][t.z]=true;
                    g[t.x][t.y][t.z]=1;
                    nextq.push_back(t);
                }
            }
            // cout << endl;
        }
        q.assign(nextq.begin(), nextq.end());
        depth++;
    }
    return depth;
}

int main() {
    int z,y,x;
    cin >> z >> y >> x;
    vector<vec> v(y, vec(z));
    vector<vector<vec> > g(x, v);
    for(int i=0; i<x; ++i) {
        for(int j=0; j<y; ++j) {
            for(int k=0; k<z; ++k) {
                cin >> g[i][j][k];
            }
        }
    }
    int ans = bfs(g);
    if(complete(g)) cout << ans;
    else cout << -1;
    return 0;
}