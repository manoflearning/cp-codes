#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (ll)(x).size()
#define all(x) (x).begin(), (x).end()

vector<ll> buildsa(const string& s) {
    ll n = sz(s), m = max(256ll, n) + 1;
    vector<ll> sa(n), r(2 * n), nr(2 * n), cnt(m), idx(n);
    for (int i = 0; i < n; i++) sa[i] = i, r[i] = s[i];
    for (int d = 1; d < n; d <<= 1) {
        auto cmp = [&](int i, int j) {
            if (r[i] ^ r[j]) return r[i] < r[j];
            return r[i + d] < r[j + d];
        };
        for (int i = 0; i < m; i++) cnt[i] = 0;
        for (int i = 0; i < n; i++) cnt[r[i + d]]++;
        for (int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; ~i; i--) idx[--cnt[r[i + d]]] = i;
        for (int i = 0; i < m; i++) cnt[i] = 0;
        for (int i = 0; i < n; i++) cnt[r[i]]++;
        for (int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; ~i; i--) sa[--cnt[r[idx[i]]]] = idx[i];
        nr[sa[0]] = 1;
        for (int i = 1; i < n; i++) nr[sa[i]] = nr[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
        for (int i = 0; i < n; i++) r[i] = nr[i];
        if (r[sa[n - 1]] == n) break;
    }
    return sa;
}
vector<ll> buildlcp(const string& s, const vector<ll>& sa) {
    int n = sz(s);
    vector<ll> lcp(n), isa(n);
    for (int i = 0; i < n; i++) isa[sa[i]] = i;
    for (int k = 0, i = 0; i < n; i++) if (isa[i]) {
        for (int j = sa[isa[i] - 1]; s[i + k] == s[j + k]; k++);
        lcp[isa[i]] = (k ? k-- : 0);
    }
    return lcp;
}

int n;
vector<string> s;
string t;
vector<ll> lcpub, id;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    // input
    cin >> n;
    s.resize(n);
    for (auto& i : s) cin >> i;

    // solve
    ll ans = 0;
    for (int i = 0; i < sz(s); i++) {
        t += s[i];
        ans += sz(s[i]) + sz(s[i]) * (sz(s[i]) - 1) / 2;
        for (int j = 0; j < sz(s[i]); j++) {
            lcpub.push_back(sz(s[i]) - j);
            id.push_back(i);
        }
    }

    vector<ll> sa = buildsa(t);
    vector<ll> lcp = buildlcp(t, sa);

    ll acc = 0;
    for (int i = 0; i < sz(t); i++) {
        if (0 <= i - 1) {
            if (id[sa[i - 1]] == id[sa[i]]) {
                acc = min(acc, lcp[i]);
            }
            else acc = lcp[i];
        }

        ll res = 0;
        if (0 <= i - 1) res = max(res, acc);
        if (i + 1 < sz(t)) res = max(res, lcp[i + 1]);
        res = min(res, lcpub[sa[i]]);
        // cout << res << '\n';
        ans -= res;
    }

    cout << ans;
}
