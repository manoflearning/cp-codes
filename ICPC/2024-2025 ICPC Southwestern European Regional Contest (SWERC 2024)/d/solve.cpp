#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;

constexpr ll INF = 4e18;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; cin >> n;
    vector<ll> h(n);
    for (auto &i : h) cin >> i;

    map<ll, vector<ll>> mp;
    for (int i = 0; i < n; i++) mp[-h[i]].push_back(i);

    ll ans = 0;

    set<ll> st;
    for (auto &[_, arr] : mp) {
        for (auto &i : arr) {
            ll res = INF;
            auto it = st.lower_bound(i);
            if (it != st.end()) res = min(res, *it - i);
            if (it != st.begin()) res = min(res, i - *(--it));
            if (res != INF) ans += res;
        }
        for (auto &i : arr) st.insert(i);
    }

    cout << ans << '\n';
}
