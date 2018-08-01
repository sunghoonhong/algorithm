#include <iostream>
#include <cstdio>
#include <string.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <cstdlib>

using namespace std;

void adfs(int v, int *g, bool *visited) {
    visited[v] = 1;
    if(!visited[g[v]]) {
        adfs(g[v],g,visited);
    }
}

int dfs(int n, int *g, bool *visited) {
    int ans = 0;
    for(int i=0; i<n; ++i) {
        if(!visited[i]) {
            adfs(i,g,visited);
            ans++;
        }
    }
    return ans;
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        int arr[n];
        bool visited[n];
        memset(visited, 0, sizeof(visited));
        for(int i=0; i<n; ++i) {
            cin >> arr[i];
            arr[i]--;
        }
        cout << dfs(n, arr, visited) << endl;
    }
    return 0;
}