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

    int already = 1;
    for (int i = 1; i < n; i++)
        if (a[i] > a[i + 1]) already = 0;
    
    if (already) {
        cout << 0;
        return 0;
    }

    int cnt = 1, up = 1, down = 0;
    for (int i = 1; i < n; i++) {
        if (a[i] < a[i + 1]) {
            if (down) cnt++, up = 1, down = 0;
        }
        if (a[i] > a[i + 1]) {
            if (up) up = 0, down = 1;
        }
    }

    int ans = 1;
    for (int i = 1; i < cnt; i <<= 1, ans++);

    cout << ans;
}