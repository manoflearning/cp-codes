#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr ll INF = 1e18;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n, m;
        ll a, b;
        cin >> n >> m >> a >> b;

        vector<vector<ll>> arr(n, vector<ll>(m));
        vector<int> cnt(n * m + 1);
        for (auto &i : arr) for (auto &j : i) {
            cin >> j;
            cnt[j]++;
        }

        vector<int> ord(n * m);
        iota(all(ord), 1);
        sort(all(ord), [&](int i, int j) {
            return cnt[i] > cnt[j];
        });

        while (!ord.empty() && cnt[ord.back()] == 0) ord.pop_back();

        // case 1: 색깔 레이어 여러 개 깔기
        ll ans = INF;

        vector<ll> suf(n * m);
        for (int i = sz(ord) - 1; i >= 0; i--) {
            if (ord[i] > 0) {
                suf[i] = cnt[ord[i]];
            }
            if (i + 1 < sz(ord)) {
                suf[i] += suf[i + 1];
            }
        }

        ll acc = 0;
        for (int i = 0; i < sz(ord); i++) {
            ll res = 0;
            res += acc + suf[i] * a;
            res += cnt[0] * i * b;

            ans = min(ans, res);

            acc += min(i * b, a) * cnt[ord[i]];
        }
        ll res = 0;
        res += acc;
        res += cnt[0] * sz(ord) * b;
        
        ans = min(ans, res);

        cout << ans << '\n';
    }
}
