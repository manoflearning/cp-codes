#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int n; cin >> n;

    vector<array<int, 3>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i][0] >> a[i][1] >> a[i][2];
        sort(all(a[i]));
    }

    int ans = 0;
    for (int ww = 1; ww <= 1000; ww++) {
        for (int hh = ww; hh <= 1000; hh++) {
            int dd = 1000;
            bool is_valid = 1;
            for (int i = 0; i < n; i++) {
                bool fill_w = 0, fill_h = 0;
                for (int j = 0; j < 3; j++) {
                    if (!fill_w && ww <= a[i][j]) {
                        fill_w = 1;
                        continue;
                    }
                    if (fill_w && !fill_h && hh <= a[i][j]) {
                        fill_h = 1;
                        continue;
                    }

                    dd = min(dd, a[i][j]);
                }
                if (!fill_w || !fill_h) {
                    is_valid = 0;
                    break;
                }
            }

            if (is_valid) {
                ans = max(ans, ww * hh * dd);
            }
        }
    }
    cout << ans;
}