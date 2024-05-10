#include <bits/stdc++.h>
using namespace std;

int n, m;
int s[2020202], p[2020202];

void input() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> s[i];
    cin >> m;
}

void manacher() {
    for (int i = n - 1; i >= 0; i--) {
        s[i << 1 | 1] = s[i];
        s[i << 1] = -1;
    }
    n <<= 1;
    s[n++] = -1;

    int r = -1, c = -1;
    for (int i = 0; i < n; i++) {
        if (i <= r) p[i] = min(r - i, p[c * 2 - i]);
        else p[i] = 0;
        while (1) {
            if (i - p[i] - 1 < 0 || i + p[i] + 1 >= n) break;
            if (s[i + p[i] + 1] != s[i - p[i] - 1]) break;
            p[i]++;
        }
        if (i + p[i] > r) {
            r = i + p[i], c = i;
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    manacher();

    while (m--) {
        int l, r;
        cin >> l >> r;

        int len = r - l + 1;
        l--, r--;
        l = l << 1 | 1, r = r << 1 | 1;

        int mid = (l + r) >> 1;

        if (p[mid] >= len) cout << 1 << '\n';
        else cout << 0 << '\n';
    }
}