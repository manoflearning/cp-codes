#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 1e9 + 7;

int n;
vector<int> a, b;
vector<ll> arr;
ll dp[3030];

void input() {
    cin >> n;
    int cnt; cin >> cnt;
    a.resize(cnt);
    for (auto& i : a) cin >> i;
    cin >> cnt;
    b.resize(cnt);
    for (auto& i : b) cin >> i;
}

void splitBlock() {
    int ia = 0, ib = 0;
    while (ia < a.size() && ib < b.size()) {
        if (a[ia] == b[ib]) {
            ia++, ib++;
            continue;
        }
        if (a[ia] > b[ib] && a[ia] == b[ib] + b[ib + 1]) {
            arr.push_back(2);
            ia++, ib += 2;
            continue;
        }
        if (a[ia] < b[ib] && a[ia] + a[ia + 1] == b[ib]) {
            arr.push_back(2);
            ia += 2, ib++;
            continue;
        }

        if (a[ia] > b[ib] && a[ia] < b[ib] + b[ib + 1]) {
            ia++, ib += 2;
            int lena = 2, lenb = 3;
            while (a[ia] == 2 && b[ib] == 2) {
                lena += 2, lenb += 2;
                ia++, ib++;
            }
            if (a[ia] == 2) {
                lena += 2, lenb++;
                ia++, ib++;
            }
            else lena++, ia++;
            arr.push_back(lena);
            continue;
        }
        if (a[ia] < b[ib] && a[ia] + a[ia + 1] > b[ib]) {
            ia += 2, ib++;
            int lena = 3, lenb = 2;
            while (a[ia] == 2 && b[ib] == 2) {
                lena += 2, lenb += 2;
                ia++, ib++;
            }
            if (b[ib] == 2) {
                lena++, lenb += 2;
                ia++, ib++;
            }
            else lenb++, ib++;
            arr.push_back(lena);
            continue;
        }
    }
}

ll powxy(ll x, ll y) { 
    if (y == 0) return 1;
    if (y == 1) return x;
    ll res = powxy(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

ll fac[3030], inv[3030], facInv[3030];
ll binom(int n, int r) {
	return fac[n] * facInv[r] % MOD * facInv[n - r] % MOD;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    splitBlock();

    // Preprocessing in O(N)
	fac[0] = fac[1] = inv[1] = 1;
	facInv[0] = facInv[1] = 1;
	for (int i = 2; i < 3030; i++) {
		fac[i] = i * fac[i - 1] % MOD;
		inv[i] = -(MOD / i) * inv[MOD % i] % MOD;
		if (inv[i] < 0) inv[i] += MOD;
		facInv[i] = facInv[i - 1] * inv[i] % MOD;
	}

    dp[1] = dp[2] = 1;
    for (int i = 3; i < 3030; i++) {
        for (int j = 1; j < i; j += 2) {
            ll res = dp[j] * dp[i - j] % MOD;
            res = res * binom(i - 1 - 1, i - j - 1);
            dp[i] = (dp[i] + res) % MOD;
        }
    }

    ll ans = 1;
    for (auto& i : arr) ans = ans * dp[i] % MOD;

    ll sum = 0;
    for (auto& i : arr) sum += i - 1;
    
    ans = ans * fac[sum] % MOD;
    for (auto& i : arr)
        ans = ans * powxy(fac[i - 1], MOD - 2) % MOD;
    cout << sum << ' ' << ans;
}