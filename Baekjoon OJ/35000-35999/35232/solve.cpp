#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;

// const int MAX_PR = 5'000'000;
// bitset<MAX_PR> isprime;
// vi eratosthenesSieve(int lim) {
// 	isprime.set(); isprime[0] = isprime[1] = 0;
// 	for (int i = 4; i < lim; i += 2) isprime[i] = 0;
// 	for (int i = 3; i*i < lim; i += 2) if (isprime[i])
// 		for (int j = i*i; j < lim; j += i*2) isprime[j] = 0;
// 	vi pr;
// 	rep(i,2,lim) if (isprime[i]) pr.push_back(i);
// 	return pr;
// }

// void bt(int i, ll acc, const vector<pll> &pp, vector<ll> &divs) {
//     if (i == sz(pp)) {
//         divs.push_back(acc);
//         return;
//     }

//     ll mul = 1;
//     bt(i + 1, acc * mul, pp, divs);
//     for (int j = 0; j < pp[i].second; j++) {
//         mul *= pp[i].first;
//         bt(i + 1, acc * mul, pp, divs);
//     }
// }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    // const vector<int> primes = eratosthenesSieve(1e5);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<ll> a(n);
        for (auto &i : a) cin >> i;

        ll ans{-1};
        for (int i = 0; i + 1 < sz(a); i++) {
            const ll d = a[i + 1] - a[i];

            if (d <= 0) {
                const ll p = a[i + 1] - 1;
                const ll q = a[i] / p;

                ans = q;
                break;
            }
        }

        if (ans == -1) {
            const ll p = a[n - 1] - a[n - 2];
            const ll q = a[n - 1] / p;
            ans = max(p, q);
        }

        cout << ans << '\n';

        // vector<vector<ll>> b;
        // for (ll i : a) {
        //     vector<ll> divs;

        //     vector<pll> pp;
        //     for (const ll p : primes) {
        //         if (p * p > i) break;
        //         ll cnt = 0;
        //         while (i % p == 0) {
        //             cnt++;
        //             i /= p;
        //         }
        //         if (cnt) pp.push_back({p, cnt});
        //     }
        //     if (i > 1) pp.push_back({i, 1});

        //     bt(0, 1, pp, divs);

        //     sort(all(divs));

        //     // DEBUG
        //     for (ll &d : divs) cout << d << ' ';
        //     cout << '\n';

        //     b.push_back(std::move(divs));
        // }

        // ll l = 1, r = 1e9;
        // while (l < r) {
        //     const ll k = (l + r) >> 1;

        //     bool yes = 1;

        //     ll p = 1, q = 0;

        //     for (int i = 0; i < n; i++) {
        //         auto it = lower_bound(all(b[i]), p);

        //         if (it == b[i].end()) { yes = 0; break; }
        //         while ((*it == p && a[i] <= q * (*it)) || k * (*it) < a[i]) {
        //             it++;
        //             q = 0;
        //             if (it == b[i].end()) { yes = 0; break; }
        //         }
        //         if (!yes) break;

        //         p = *it, q = a[i] / p;

        //         if (p > k) { yes = 0; break; }

        //         // if (k == (int)5e8) cout << p << ' ' << q << '\n';
        //     }

        //     if (yes) r = k;
        //     else l = k + 1;
        // }

        // cout << l << '\n';
    }
}
