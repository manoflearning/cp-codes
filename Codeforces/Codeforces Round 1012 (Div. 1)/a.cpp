#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        if (n == 2) {
            cout << 2 << ' ' << 1 << '\n';
            continue;
        }

        int p = -1;
        for (int x = n / 3; x <= 2 * (n / 3); x++) {
            bool is_prime = (x >= 2);
            for (int i = 2; i * i <= x; i++) {
                if (x % i == 0) { is_prime = 0; break; }
            }

            if (is_prime) { p = x; break; }
        }

        int lb = p - 1, ub = p + 1;
        cout << p << ' ';
        while (1 <= lb || ub <= n) {
            if (1 <= lb) cout << lb-- << ' ';
            if (ub <= n) cout << ub++ << ' ';
        }
        cout << '\n';
    }
}
