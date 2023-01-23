#include <bits/stdc++.h>
using namespace std;

int n, a[303030];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    int increase = 1, decrease = 1;
    for (int i = 1; i < n; i++) {
        if (a[i] > a[i + 1]) increase = 0;
        if (a[i] < a[i + 1]) decrease = 0;
    }

    if (increase || decrease) {
        cout << 0;
        return 0;
    }

    int up = 1, down = 0, cnt = 1;
    for (int i = 2; i <= n; i++) {
        if (a[i - 1] == a[i]) continue;
        if (a[i - 1] < a[i]) {
            if (down) up = 1, down = 0, cnt++;
        }
        if (a[i - 1] > a[i]) {
            if (up) up = 0, down = 1;
        }
    }

    int ans = 1;
    for (int i = 1; i < cnt; i *= 2, ans++);
    
    cout << ans;
}