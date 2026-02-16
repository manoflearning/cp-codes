#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    ll d, s, e;
    cin >> d >> s >> e;

    const ld p = 1.0l / d;
    const ld q = (1.0l - s * p) / (d - s - e);

    const ll y = min(s, d - s - e);
    const ll x = s - y;

    cout << fixed;
    cout.precision(10);

    // cout << p << ' ' << q << '\n';
    // cout << x << ' ' << y << '\n';

    const ld ans{p * x + q * y};
    cout << ans << '\n';
}