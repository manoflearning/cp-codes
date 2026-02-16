#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr double EPS = 1e-8;

struct Order {
    ll p, b, s;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; cin >> n;

    vector<Order> a(n);
    for (auto &i : a) {
        string ps;
        cin >> ps >> i.b >> i.s;
        i.p = (ll)(stod(ps) * 100 + EPS);
    }

    sort(all(a), [&](const Order &i, const Order &j) {
        return i.p < j.p;
    });

    ll opt_p = 0, opt_c = 0;
    
    vector<ll> ps(n), sb(n);
    for (int i = 0; i < n; i++) {
        ps[i] = a[i].s + (i > 0 ? ps[i - 1] : 0);
    }
    for (int i = n - 1; i >= 0; i--) {
        sb[i] = a[i].b + (i + 1 < n ? sb[i + 1] : 0);
    }

    for (int i = 0; i < n; i++) {
        const ll both = min(ps[i], sb[i]);
        if (both * a[i].p > opt_c) {
            opt_p = a[i].p;
            opt_c = both * a[i].p;
        }
    }

    if (opt_c == 0) {
        cout << "impossible\n";
    } else {
        cout << fixed;
        cout.precision(2);
        cout << opt_p / 100.0l << ' ' << opt_c / 100.0l << '\n';
    }
}
