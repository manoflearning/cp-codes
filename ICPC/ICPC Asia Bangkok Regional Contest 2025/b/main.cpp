#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n, m;
        cin >> n >> m;

        if (n == 2) {
            if (m & 1) {
                cout << "2 1\n";
            } else {
                cout << "1 2\n";
            }
        } else if (n >= m) {
            int ub = n;
            while (m--) {
                cout << ub-- << ' ';
            }
            for (int i = 1; i <= ub; i++) {
                cout << i << ' ';
            }
            cout << '\n';
        } else {
            // if (m > n) {
                for (int i = n; i >= 1; i--) {
                    cout << i << ' ';
                }
                cout << '\n';
            // } else {
            //     for (int i = n; i >= 1; i--) {
            //         if (i > 2) cout << i << ' ';
            //         else {
            //             cout << (i == 1 ? 2 : 1) << ' ';
            //         }
            //     }
            //     cout << '\n';
            // }
        }
    }
}