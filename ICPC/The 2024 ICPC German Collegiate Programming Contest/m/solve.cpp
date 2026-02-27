#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr ll INF = 4e18;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; cin >> n;

    vector<ll> t(n);
    for (int i = 0; i < n; i++) {
        cin >> t[i]; t[i] -= i;
    }

    sort(all(t));

    vector<ll> ps(n + 1), ss(n + 1);
    for (int i = 0; i < n; i++) ps[i + 1] = t[i] + ps[i];
    for (int i = n - 1; i >= 0; i--) ss[i] = t[i] + ss[i + 1];

    ll ans = INF;
    for (int i = 0; i < n; i++) {
        ll res = 0;
        res += t[i] * i - ps[i];
        res += ss[i + 1] - t[i] * (n - i - 1);
        ans = min(ans, res);
    }

    cout << ans << '\n';
}
