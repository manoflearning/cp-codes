#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

ll modpow(ll b, ll e, const ll mod) {
    if (!e) return 1;
    const ll res = modpow(b, e / 2, mod);
    return res * res % mod * (e & 1 ? b : 1) % mod;
}

ll f(const ll l, const ll mod, const vector<ll> &a) {
    set<ll> st;
    for (const ll i : a) st.insert(i);

    ll cnt_free = l - a.back();
    while (sz(st) >= 2) {
        const ll y = *prev(st.end());
        const ll x = *prev(prev(st.end()));
        const ll a = (sz(st) > 2 ? *prev(prev(prev(st.end()))) : 0ll);

        if (2 * x <= y) {
            st.erase(y);
            cnt_free += (y - 2 * x + 1) / 2;
        } else {
            st.erase(x), st.erase(y);

            const ll d = y - x;
            const ll thres = max(a, d);
            const ll t = (x - thres + d - 1) / d;

            const ll r = x - t * d;
            const ll u = r + d;

            st.insert(r);
            if (r <= a) st.insert(u);
            else cnt_free += (d - r + 1) / 2;
        }
    }
    cnt_free += (*st.begin() + 1) / 2;

    return modpow(2, cnt_free, mod);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    ll l; int n, m;
    cin >> l >> n >> m;

    vector<ll> a(n);
    for (auto &i : a) cin >> i;

    sort(all(a));
    a.erase(unique(all(a)), a.end());

    cout << f(l, m, a) << '\n';    
}
