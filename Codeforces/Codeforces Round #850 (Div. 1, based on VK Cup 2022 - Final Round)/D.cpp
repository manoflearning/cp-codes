//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 998244353;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

const int MAXN = (1 << 21);
ll fac[MAXN], inv[MAXN], facInv[MAXN];
ll binom(int n, int r) {
	return fac[n] * facInv[r] % MOD * facInv[n - r] % MOD;
}

ll p2[MAXN];

void init() {
    // Preprocessing in O(N)
	fac[0] = fac[1] = inv[1] = 1;
	facInv[0] = facInv[1] = 1;
	for (int i = 2; i < MAXN; i++) {
		fac[i] = i * fac[i - 1] % MOD;
		inv[i] = -(MOD / i) * inv[MOD % i] % MOD;
		if (inv[i] < 0) inv[i] += MOD;
		facInv[i] = facInv[i - 1] * inv[i] % MOD;
	}

    // 
    p2[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        p2[i] = (p2[i - 1] << 1) % MOD;
    }
}

int n, mx;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    init();
    
	cin >> n;
    mx = (1 << n);

    ll x = mx - (n + 1), res2 = 1;
    for (int i = 1; i <= n - 1; i++) {
        res2 = (res2 * x) % MOD;
        x--;
    }
    
    assert(!(x & 1));
    while (x) {
        res2 = res2 * binom(x, 2) % MOD;
        x -= 2;
    }

    //cout << res2 << '\n';
    //vector<int> arr = { 0, 0, 0, 1536, 4224, 7680, 11520, 15360 };
    //vector<int> arr = { 0, 0, 8, 16 };
    //vector<int> arr = { 0, 2 };

    ll sum = 0;
    for (int i = 1; i <= mx; i++) {
        if (i <= n) {
            cout << 0 << '\n';
            continue;
        }

        ll res = binom(i - 2, n - 1);

        res = res * res2 % MOD;

        res2 = (res2 - 1) % MOD;
        res2 = (res2 + MOD) % MOD;
        //cout << res2 << ' ';
        
        res = (res * p2[mx - 1]) % MOD;

        cout << res << '\n';
        sum += res;
        sum %= MOD;

        //cout << arr[i - 1] << ' ' << res << ' ' << arr[i - 1] / res << ' ' << arr[i - 1] % res << '\n';
    }

    //cout << sum << ' ' << fac[mx] << '\n';
    //assert(sum == fac[mx]);

	return 0;
}