#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr ll INF = 4e18;

struct Crane {
    ll x, y, h; int idx;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; cin >> n;

    int idx{};
    vector<Crane> a(n);
    for (int i = 0; i < n; i++) cin >> a[i].x >> a[i].y >> a[i].h, a[i].idx = i;

    sort(all(a), [](Crane i, Crane j) {
        return i.h > j.h;
    });

    vector<ll> ans(n);
    for (int i = 0; i < n; i++) {
        ll d2{INF};
        for (int j = 0; j < i; j++) {
            d2 = min(d2, (a[i].x - a[j].x) * (a[i].x - a[j].x) + (a[i].y - a[j].y) * (a[i].y - a[j].y));
        }

        ll lo = 1, hi = a[i].h;
        while (lo < hi) {
            const ll mid = (lo + hi + 1) >> 1;
            if (mid * mid <= d2) lo = mid;
            else hi = mid - 1;
        }

        ans[a[i].idx] = lo;
    }

    for (auto &i : ans) cout << i << '\n';
}
