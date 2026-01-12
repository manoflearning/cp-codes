#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int n, k, x;
vector<ll> a;

vector<pll> r;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> k >> x;
    a.assign(n, 0);
    for (auto &i : a) cin >> i;

    sort(a.rbegin(), a.rend());

    if (n == 2) {
        ll delta = a[0] - a[1];
        for (int i = 0; i < x; i++) {
            cout << k * a[0] - i * delta << '\n';
        }
        exit(0);
    }

    // base case
    for (int i = 0; i < n; i++) r.push_back({a[i], i});

    // inductive step
    int cnt = 0;

    int t = 1;
    for (; t < k; t++) {
        vector<pll> tmp;

        for (int i = 0; i < sz(r); i++) {
            for (int j = r[i].sc; j < sz(a); j++) {
                const ll u = r[i].fr;
                const ll v = a[j];
                tmp.push_back({u + v, j});
            }
        }

        r = tmp;
        sort(r.rbegin(), r.rend());
        if (sz(r) > x) r.resize(x);

        if (sz(r) == x) cnt++;
        if (cnt == 20) break;
        // cout << t << ' ' << sz(r) << endl;
    }
    for (auto &i : r) i.fr += (k - t - 1) * a[0];

    for (auto &i : r)
        cout << i.fr << '\n';
}