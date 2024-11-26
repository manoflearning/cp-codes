#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const ll INF = 1e18;

ll f(vector<ll> &s) {
    ll n = sz(s);

    auto t = s;
    sort(all(t));
    if (s == t) return 0;

    map<ll, queue<int>> idxs;
    for (int i = 0; i < n; i++) {
        idxs[t[i]].push(i);
    }

    vector<ll> dst(n);
    for (int i = 0; i < n; i++) {
        dst[i] = idxs[s[i]].front();
        idxs[s[i]].pop();
        if (dst[i] == i) dst[i] = n;
    }

    vector<ll> sdst(n);
    sdst[n - 1] = dst[n - 1];
    for (int i = n - 2; i >= 0; i--)
        sdst[i] = min(dst[i], sdst[i + 1]);

    ll ret = INF;
    ret = min(ret, (n - sdst[0]) * (n - sdst[0]));
    for (ll i = 0; i + 1 < n; i++) {
        ret = min(ret, (i + 1) * (i + 1) + (n - sdst[i + 1]) * (n - sdst[i + 1]));
    }
    ret = min(ret, n * n);

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n; cin >> n;

    vector<ll> s;
    s.resize(n);
    for (auto &i : s) cin >> i;

    ll ans = INF;
    ans = min(ans, f(s));
    {
        for (int i = 0; i < sz(s) / 2; i++)
            swap(s[i], s[sz(s) - 1 - i]);
        for (int i = 0; i < sz(s); i++)
            s[i] = (1ll << 31) - s[i];
    }
    ans = min(ans, f(s));

    cout << ans;
}
