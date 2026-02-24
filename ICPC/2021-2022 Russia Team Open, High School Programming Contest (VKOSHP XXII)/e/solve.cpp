#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr ll INF = 4e18;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    cout << fixed;
    cout.precision(10);

    int n; cin >> n;
    vector<ll> a(n);
    for (auto &i : a) cin >> i;

    vector<ll> pmin(n), pmax(n), smin(n), smax(n);
    pmin[0] = pmax[0] = a[0];
    for (int i = 1; i < n; i++) {
        pmin[i] = min(pmin[i - 1], a[i]);
        pmax[i] = max(pmax[i - 1], a[i]);
    }
    smin[n - 1] = smax[n - 1] = a[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        smin[i] = min(smin[i + 1], a[i]);
        smax[i] = max(smax[i + 1], a[i]);
    }

    cout << 1.0l << ' ';
    for (int k = 1; k < n; k++) {
        ld t{1.0l};

        const ld lb = smin[k], ub = smax[k];
        if (pmin[k - 1] < t * lb) {
            t = pmin[k - 1] / (t * lb);
        }

        // now t * lb <= pmin[k - 1]

        if (pmax[k - 1] < t * ub) {
            t = pmax[k - 1] / ub;
        }

        cout << 1 - t << ' ';
    }
    cout << '\n';
}