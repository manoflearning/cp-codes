#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int INF = 1e9 + 7;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n, d;
    cin >> n >> d;

    vector<int> p(n);
    vector<vector<int>> rp(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        rp[p[i]].push_back(i);
    }

    for (int x = 0; x <= n; x++) {
        bool yes = 1;

        int prv = -d;
        for (int i = 0; i < sz(rp[x]); i++) {
            if (rp[x][i] - prv < d) {
                yes = 0;
                break;
            }

            int now = max(rp[x][i] - d + 1, prv + d);
            const int ub = rp[x][i];

            while (i + 1 < sz(rp[x]) && rp[x][i + 1] - ub < d) {
                now = max(now, rp[x][i + 1] - d + 1);
                i++;
            }

            // if (ub < now) { yes = 0; break; }

            prv = now + d;
        }
        // if (prv > n) yes = 0;

        if (yes) {
            cout << x << '\n';
            exit(0);
        }
    }

    assert(0);
}
