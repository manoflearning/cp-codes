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

    int n, H;
    cin >> n >> H;

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ll l, w, h;
        cin >> l >> w >> h;
        ll res = INF;
        if (l <= H) res = min(res, min(w, h));
        if (w <= H) res = min(res, min(l, h));
        if (h <= H) res = min(res, min(l, w));
        if (res == INF) {
            cout << "impossible\n";
            exit(0);
        }
        ans += res;
    }
    cout << ans << '\n';
}
