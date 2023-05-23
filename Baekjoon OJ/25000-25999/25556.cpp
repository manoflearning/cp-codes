#include <bits/stdc++.h>
using namespace std;

int stk[4];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n; cin >> n;
    int ans = 1;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        int idx = -1;
        for (int j = 0; j < 4; j++) {
            if (x < stk[j]) continue;
            if (idx == -1 || stk[idx] < stk[j]) idx = j;
        }
        if (idx == -1) ans = 0;
        else stk[idx] = x;
    }

    cout << (ans ? "YES" : "NO");
}