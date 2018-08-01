#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

typedef vector<bool> vb;

void tri(int n, int mid, int head, vector<vb> &matrix) {
    
    // h[k] = 3*2^k = n, w[k] = 2*w[k-1]+1 = 6*2^k-1
    // h와 w의 관계:  w = 2*h-1
    // w[k-1] = 3*2*k-1 = n-1

    // tri(n, mid, head) :
    //     mid를 중심으로 위에서 head부터 n줄짜리 삼각형을 그린다.
    //     => tri(n/2)를 위에 그리고, 그 밑에 tri(n/2)를 공백 하나(mid)를 중심으로 양쪽에 복사한다.
    //     => tri(n/2, mid, head), tri(n/2,mid-n/2,head+n/2), tri(n/2,mid+n/2,head+n/2)
    // tri(3, mid, head) : mid를 중심으로 head번쨰 줄부터 3줄짜리 삼각형을 그린다.
    
    if(n==3) {
        matrix[head][mid]=1;
        matrix[head+1][mid+1]=1;
        matrix[head+1][mid-1]=1;
        for(int i=0; i<5; ++i) {
            matrix[head+2][mid-2+i]=1;
        }
    }
    else {
        tri(n/2, mid, head, matrix);
        tri(n/2, mid-n/2, head+n/2, matrix);
        tri(n/2, mid+n/2, head+n/2, matrix);
    }
}

vector<vb> set(int n) {
    int width = n*2 - 1;
    vector<vb> matrix(n, vb(width,0));
    return matrix;
}

int main() {
    int n;
    cin >> n;
    vector<vb> matrix = set(n);
    tri(n, n-1, 0, matrix);

    for(int i=0; i<matrix.size(); ++i) {
        for(int j=0; j<matrix[i].size(); ++j) {
            if(matrix[i][j]) cout << '*';
            else cout << ' ';
        }
        cout << endl;
    }
    
    return 0;
}