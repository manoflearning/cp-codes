#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int INF = 1e9 + 7;
constexpr int B = 202020;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; cin >> n;

    vector<int> a(n);
    int mn = INF;
    for (auto &i : a) {
        cin >> i;
        mn = min(mn, i);
    }
    a.push_back(a[0]);

    ll ans1 = 0;

    vector<int> ps(B);
    for (int i = 0; i < n; i++) {
        if (a[i] < a[i + 1]) {
            ps[a[i] + 1]++;
            ps[a[i + 1] + 1]--;
        }
    }

    int rem = mn;
    for (int i = 1; i < B; i++) {
        ps[i] += ps[i - 1];
        if (!ps[i]) continue;
        const int sub = min(rem, ps[i] - 1);
        rem -= sub;
        ans1 += ps[i];
    }
    ans1 += rem;
    
    cout << ans1 << '\n';
    if (ans1 > 2e5) exit(0);

    vector<pii> ans2;
    rem = mn;

    vector<int> l(B, -1);
    vector<vector<pii>> arr(B);
    for (int i = 0; i < 2 * n; i++) {
        const int h1 = a[i % n];
        const int h2 = a[(i + 1) % n];
        if (h1 < h2 && i < n) {
            for (int h = h1 + 1; h <= h2; h++) {
                assert(l[h] == -1);
                l[h] = i + 1;
            }
        }
        if (h1 > h2) {
            for (int h = h2 + 1; h <= h1; h++) {
                if (l[h] == -1) continue;
                arr[h].push_back({l[h], i});
                l[h] = -1;
            }
        }
    }

    for (int h = 1; h < B; h++) {
        if (!ps[h]) continue;

        const int sub = min(rem, ps[h] - 1);
        rem -= sub;
        for (int j = 0; j < sz(arr[h]); j++) {
            ans2.push_back({arr[h][j].first, arr[h][(j + sub) % sz(arr[h])].second});
        }
    }

    while (rem--) ans2.push_back({0, n - 1});

    for (auto &[l, r] : ans2) {
        cout << l % n + 1 << ' ' << r % n + 1 << '\n';
    }
}
