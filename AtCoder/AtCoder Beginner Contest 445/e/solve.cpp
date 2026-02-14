#pragma GCC optimize ("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;

constexpr int MOD = 998'244'353;

const int MAX_PR = 5'000'000;
bitset<MAX_PR> isprime;
vi eratosthenesSieve(int lim) {
	isprime.set(); isprime[0] = isprime[1] = 0;
	for (int i = 4; i < lim; i += 2) isprime[i] = 0;
	for (int i = 3; i*i < lim; i += 2) if (isprime[i])
		for (int j = i*i; j < lim; j += i*2) isprime[j] = 0;
	vi pr;
	rep(i,2,lim) if (isprime[i]) pr.push_back(i);
	return pr;
}

ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % MOD, e /= 2)
		if (e & 1) ans = ans * b % MOD;
	return ans;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    const vector<int> primes = eratosthenesSieve((int)1e5);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        vector<ll> a(n);
        for (auto &i : a) cin >> i;

        vector<vector<pll>> factor;
        for (ll x : a) {
            vector<pll> res;
            for (ll p : primes) {
                if (x < p * p) break;

                int cnt = 0;
                while (x % p == 0) {
                    x /= p;
                    cnt++;
                }
                if (cnt) res.push_back({p, cnt});
            }
            if (x > 1) res.push_back({x, 1});

            factor.push_back(std::move(res));
        }

        vector<ll> ans(n, 1);

        ll acc = 1;
        unordered_map<ll, multiset<int>> mp;
        for (int i = 0; i < n; i++) {
            for (const auto [p, cnt] : factor[i]) {
                const int prv_mx = (sz(mp[p]) ? *(--mp[p].end()) : 0);
                if (prv_mx < cnt) {
                    acc = acc * modpow(p, cnt - prv_mx) % MOD;
                }
                mp[p].insert(cnt);
            }
        }

        for (int i = 0; i < n; i++) {
            ll res = acc;

            for (auto &[p, cnt] : factor[i]) {
                auto it = --mp[p].end();

                int prv_mx = (sz(mp[p]) >= 1 ? *it : 0);
                int now_mx = (*it == cnt ? (sz(mp[p]) >= 2 ? *(--it) : 0) : *it);

                if (now_mx < prv_mx) {
                    res = res * modpow(modpow(p, prv_mx - now_mx), MOD - 2) % MOD;
                }
            }

            cout << res << ' ';
        }
        cout << '\n';
    }

    return 0;
}
