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
    트리 순회

    전위순회(preorder traversal): P -> L -> R
    중위순회(inorder traversal): L -> P -> R
    후위순회(postorder traversal): L -> R -> P

    N(노드의개수) <= 26인데 26은 알파벳개수('A'~'Z')와 같다.
    따라서 굳이 알파벳으로 확인하지 않고 0~25로 확인해도 된다.
*/

struct Tree{
    int left, right;
};

void visit(int temp) {
    putchar(temp+'A');
}
void preorder(vector<Tree> &tree, int start) {
    visit(start);
    if(tree[start].left!=-1) preorder(tree, tree[start].left);
    if(tree[start].right!=-1) preorder(tree, tree[start].right);
}
void inorder(vector<Tree> &tree, int start) {
    if(tree[start].left!=-1) inorder(tree, tree[start].left);
    visit(start);
    if(tree[start].right!=-1) inorder(tree, tree[start].right);
}
void postorder(vector<Tree> &tree, int start) {
    if(tree[start].left!=-1) postorder(tree, tree[start].left);
    if(tree[start].right!=-1) postorder(tree, tree[start].right);
    visit(start);
}

int main() {
    int n = getInt();
    vector<Tree> tree(n);
    char t,l,r,index;
    for(int i=0; i<n; ++i) {
        scanf("%c %c %c", &t, &l, &r);
        getchar();
        index = t-'A';
        tree[index].left = l=='.' ? -1 : l-'A';
        tree[index].right = r=='.' ? -1 : r-'A';
        // printf("%c %c %c\n", index+'A', tree[index].left+'A', tree[index].right+'A');
    }
    preorder(tree, 0); enter();
    inorder(tree, 0); enter();
    postorder(tree, 0);

    return 0;
}