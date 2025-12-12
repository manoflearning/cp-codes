#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<string> a(n), b(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i] >> b[i];
        }

        set<string> p, q;
        bool ans = 1;
        for (int i = 1; i < n; i++) {
            bool x = (a[i - 1] == a[i]);
            bool y = (b[i - 1] == b[i]);

            if (!x && !y) {
                p.insert(a[i - 1]), q.insert(b[i - 1]);
            }

            if (p.count(a[i]) || q.count(b[i])) {
                ans = 0;
                break;
            }
        }

        cout << (ans ? "Yes" : "No") << '\n';
    }
}