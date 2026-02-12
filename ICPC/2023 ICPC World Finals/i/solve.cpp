#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

const ld PI = cos(-1.0L);
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n, m; cin >> n >> m;
    vector<vector<ll>> p(n, vector<ll>(m));
    rep(i, 0, n) rep(j, 0, m) cin >> p[i][j];

    vector<ld> E(n);
    for(int i = 0; i < n; i++) {
        ld res = 0;
        rep(j, 0, m) res += p[i][j];
        E[i] = res / m;
    }

    vector<ld> area(n + 1);
    ld t = 0;
    for(int i = 1; i <= n / 2; i++) {
        ld s = acos(1.0L - (ld)(2.0L / n) * i);
        area[i] = (cos(t) - cos(s)) / 2;
        t = s;
    }
    if(n & 1) {
        ld &d = area[(n + 1) / 2] = 1.0L;
        for(int i = 1; i < (n + 1) / 2; i++) {
            d -= 2.0L * area[i];
        }
    }

    ld ans = 0;
    if(n & 1) {
        for(int i = 1; i < (n + 1) / 2; i++) {
            ans += area[i] * E[i - 1];
        }
        ans += area[(n + 1) / 2] * E[(n + 1) / 2 - 1];
        for(int i = (n + 1) / 2 - 1; i >= 1; i--) {
            ans += area[i] * E[n - i];
        }
    } else {
        for(int i = 1; i <= n; i++) {
            ans += area[min(i, n - i + 1)] * E[i - 1];
        }
    }

    cout << fixed << setprecision(10);
    cout << ans << '\n';
}
