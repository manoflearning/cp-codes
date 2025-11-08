#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr ll INF = 1e18;

ll power(ll x, int y, int mod) {
    ll ret = 1;
    while (y) {
        if (y & 1) ret = ret * x % mod;
        x = x * x % mod; y >>= 1;
    }
    return ret;
}

ll get_res(ll a, ll b, ll s, ll p, ll xi) {
    ll ret = 0;

    ll paxip = power(a, xi, p);
    ret = (ret + paxip * s % p) % p;
    ret = (ret + ((1 - paxip + p) % p) * power(1 - a, p - 2, p) % p * b % p) %p;

    return ret;
}

constexpr int MAX = 1e5;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dt(0, INT32_MAX);

    vector<ll> x, y;
    while (sz(x) < MAX) {
        x.push_back(dt(gen));
    }
    while (sz(y) < MAX) {
        y.push_back(dt(gen));
    }

    int tc; cin >> tc;
    while (tc--) {
        ll a, b, s, p, v;
        cin >> a >> b >> s >> p >> v;

        vector<ll> div;
        for (ll i = 1; i * i <= p - 1; i++) {
            if ((p - 1) % i == 0) {
                div.push_back(i);
                if (i != (p - 1) / i) div.push_back((p - 1) / i);
            }
        }
        sort(all(div));

        ll len = INF;
        for (auto &i : div) {
            if (power(a, i, p) == 1) {
                len = i;
                break;
            }
        }

        assert(len != INF);

        unordered_map<int, int> mp;
        for (int xi : x) {
            xi %= len;

            int res = get_res(a, b, s, p, xi);
            mp.insert({res, xi});
        }

        int ans = -1;
        for (int yi : y) {
            yi %= len;

            int res = get_res(a, b, v, p, yi);
            
            auto it = mp.find(res);
            if (it == mp.end()) continue;

            int xi = it->sc;

            ans = ((xi - yi) % len + len) % len;
            break;
        }

        if (ans != -1) {
            cout << ans << '\n';
        } else {
            cout << "IMPOSSIBLE\n";
        }
    }
}
