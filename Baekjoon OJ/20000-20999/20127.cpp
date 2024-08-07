#include <bits/stdc++.h>
using namespace std;

int n, a[1010101];
int up1[1010101], down1[1010101];
int up2[1010101], down2[1010101];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    up1[1] = down1[1] = 1;
    for (int i = 2; i <= n; i++) {
        up1[i] = up1[i - 1];
        down1[i] = down1[i - 1];
        if (a[i - 1] > a[i]) up1[i] = 0;
        if (a[i - 1] < a[i]) down1[i] = 0;
    }

    up2[n] = down2[n] = 1;
    for (int i = n - 1; i >= 1; i--) {
        up2[i] = up2[i + 1];
        down2[i] = down2[i + 1];
        if (a[i] > a[i + 1]) up2[i] = 0;
        if (a[i] < a[i + 1]) down2[i] = 0;
    }


    if (up1[n] || down1[n]) {
        cout << 0;
        return 0;
    }
    for (int i = 1; i < n; i++) {
        if ((up1[i] && up2[i + 1] && a[n] <= a[1]) || (down1[i] && down2[i + 1] && a[n] >= a[1])) {
            cout << i;
            return 0;
        }
    }
    cout << -1;
}