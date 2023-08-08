#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()
#define ll long long

const int MOD = 1e9 + 7;
const int MAXN = 202020;
ll fac[MAXN], inv[MAXN], facInv[MAXN];
ll binom(int n, int r) {
	return fac[n] * facInv[r] % MOD * facInv[n - r] % MOD;
}
void preprocessing() {
    fac[0] = fac[1] = inv[1] = 1;
	facInv[0] = facInv[1] = 1;
	for (int i = 2; i < MAXN; i++) {
		fac[i] = i * fac[i - 1] % MOD;
		inv[i] = -(MOD / i) * inv[MOD % i] % MOD;
		if (inv[i] < 0) inv[i] += MOD;
		facInv[i] = facInv[i - 1] * inv[i] % MOD;
	}
}

int n;
vector<int> a;
vector<int> psum;

void input() {
    cin >> n;
    a.resize(n);
    for (auto& i : a) cin >> i;
}

void comp() {
    vector<int> c = a;
    c.push_back(-1);
    sort(all(c));
    c.erase(unique(all(c)), c.end());
    for (auto& i : a) {
        i = lower_bound(all(c), i) - c.begin();
    }
}

void buildPsum() {
    psum.resize(n + 1);
    for (auto& i : a) psum[i]++;
    for (int i = 1; i <= n; i++)
        psum[i] += psum[i - 1];
}
int sum(int l, int r) { return psum[r] - psum[l - 1]; }

// A / B = A * B^{p - 2} (mod p)
ll powxy(ll x, ll y) { 
    if (y == 0) return 1;
    if (y == 1) return x;
    ll res = powxy(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    preprocessing();

    input();

    comp();

    buildPsum();

    ll ans = 0;
    for (auto& i : a) {
        int cnt1 = sum(1, i - 1);
        int cnt2 = sum(i, n);

        ll de = binom(cnt1 + cnt2, cnt1);
        ll nu = 0;
        // for (int i = 0; i < cnt1; i++) {
        //     nu = (nu + binom(i + cnt2, i)) % MOD;
        // }
        // for (int i = 1; i <= cnt1; i++) {
        //     nu += binom(cnt1 + cnt2 - i, cnt1 - i);
        // }

        // cnt := cnt1 + cnt2
        // nu = (0 + cnt2, 0) + (1 + cnt2, 1) + (2 + cnt2, 2) + ... + (cnt1 + cnt2 - 1, cnt1 - 1)
        // = (cnt1 + cnt2, cnt1 - 1);
        if (cnt1 > 0) nu = binom(cnt1 + cnt2, cnt1 - 1) % MOD;
        // cout << cnt1 + cnt2 + 1 << ' ' << cnt1 << ' ' << nu << '\n';
        // cout << de << '\n';
        ans = (ans + nu * powxy(de, MOD - 2) % MOD) % MOD;
    }

    cout << ans;
}