#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n, k;
        cin >> n >> k;

        vector<int> a(n), ps(n + 2);
        for (auto &i : a) {
            cin >> i;
            ps[i]++;
        }

        for (int i = 1; i <= n + 1; i++) ps[i] += ps[i - 1];

        int opt_x = -1, opt_y = -1;
        for (int x = 1; x <= n; x++) {
            int l = x, r = n + 1;
            while (l < r) {
                int mid = (l + r) >> 1;
                if (2 * (ps[mid] - ps[x - 1]) - n >= k) r = mid;
                else l = mid + 1;
            }

            if (l == n + 1) continue;
            if (opt_x == -1 || l - x < opt_y - opt_x) {
                opt_x = x, opt_y = l;
            }
        }

        cout << opt_x << ' ' << opt_y << '\n';

        int st = 0, acc = 0;
        for (int i = 0; i < k; i++) {
            if (i + 1 < k) {
                int j;
                for (j = st; acc <= i; j++) {
                    if (opt_x <= a[j] && a[j] <= opt_y) acc++;
                    else acc--;
                }
                j--;

                cout << st + 1 << ' ' << j + 1 << '\n';
                st = j + 1;
            } else {
                cout << st + 1 << ' ' << n << '\n';
            }
        }
    }
}
