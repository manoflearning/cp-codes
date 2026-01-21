#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int MOD = 998'244'353;
constexpr int S = 202020;

struct Tree {
	typedef ll T;
	static constexpr T unit = 0;
	T f(T a, T b) { return (a + b) % MOD; } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

array<ll, S> fac, ifac;

ll pow_mod(ll x, ll y) {
    if (!y) return 1;
    ll res = pow_mod(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    fac[0] = 1;
    for (int i = 1; i < S; i++)
        fac[i] = i * fac[i - 1] % MOD;
    ifac[S - 1] = pow_mod(fac[S - 1], MOD - 2);
    for (int i = S - 1; i >= 1; i--)
        ifac[i - 1] = i * ifac[i] % MOD;

    int n, m;
    cin >> n >> m;

    vector<int> s(n), t(m);
    for (auto &i : s) cin >> i;
    for (auto &i : t) cin >> i;

    ll ans = 0;

    vector<int> cnt(S);
    for (auto &i : s) cnt[i]++;

    Tree seg(S);

    ll d_base = 1;
    for (int i = 0; i < S; i++) {
        if (!cnt[i]) continue;

        d_base = d_base * ifac[cnt[i]] % MOD;
        seg.update(i, fac[cnt[i]] * ifac[cnt[i] - 1] % MOD);
    }

    for (int i = 0; i < m; i++) {
        if (i < n) {
            ll res = 1;
            res = res * fac[n - i - 1] % MOD;
            res = res * d_base % MOD * seg.query(1, t[i]) % MOD;
            ans = (ans + res) % MOD;
        }

        if (cnt[t[i]] == 0) {
            if (i == n) ans = (ans + 1) % MOD;
            break;
        }

        cnt[t[i]]--;
        d_base = d_base * fac[cnt[t[i]] + 1] % MOD;
        d_base = d_base * ifac[cnt[t[i]]] % MOD;
        if (cnt[t[i]] > 0) {
            seg.update(t[i], fac[cnt[t[i]]] * ifac[cnt[t[i]] - 1] % MOD);
        } else {
            seg.update(t[i], 0);
        }
    }

    // bool empty = 1;
    // for (int i = 0; i < S; i++) {
    //     empty &= cnt[i] == 0;
    // }
    // ans = (ans + empty) % MOD;

    cout << ans << '\n';
}
