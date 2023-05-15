#include <bits/stdc++.h>
using namespace std;

int ans[33][33];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    for (int i = 1; i <= 15; i++) ans[16][i] = 1;
    for (int i = 1; i <= 15; i++) ans[i][16] = 16;
    for (int i = 17; i <= 30; i++) ans[16][i] = 256;
    for (int i = 17; i <= 30; i++) ans[i][16] = 3840;

    for (int i = 1; i <= 30; i++) {
        for (int j = 1; j <= 30; j++) {
            cout << ans[i][j] << ' ';
        }
        cout << '\n';
    }
}