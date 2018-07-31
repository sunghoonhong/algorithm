#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;

int main() {
    int len = 'z'-'a'+1;
    vector<int> count(len, 0);
    char ch;
    while(1) {
        ch = cin.get();
        if(ch>='a' && ch<='z') {
            count[ch-'a']++;
        }
        else if(ch==' '||ch=='\n')
            continue;
        else
            break;
    }
    int max = *max_element(count.begin(), count.end());
    for(int i=0; i<len; ++i) {
        if(count[i]==max) {
            cout << char(i+'a');
        }
    }
    return 0;
}