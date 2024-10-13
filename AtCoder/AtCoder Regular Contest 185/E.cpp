// #pragma GCC optimize ("O3")
// #pragma GCC optimize ("Ofast")
// #pragma GCC optimize ("unroll-loops")
// #pragma GCC target ("avx2")

#include <bits/stdc++.h>
// #include <x86intrin.h>
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

const int MAXN = 505050;
const int MAXD = 18;

int n, a[MAXN];

vector<int> sp(101010);
vector<ll> prime;
// Determine prime numbers between 1 and MAXN in O(MAXN) 
void linearSieve() {
	for (int i = 2;i < 101010; i++) {
		if (!sp[i]) {
			prime.push_back(i);
			sp[i] = i;
		}
		for (auto j : prime) {
			if (i * j >= 101010) break;
			sp[i * j] = j;
			if (i % j == 0) break;
		}
	}
}
vector<pii> factorization(int x) {
    vector<pii> ret;
	while (x > 1) {
        if (ret.empty() || ret.back().fr != sp[x])
            ret.push_back({ sp[x], 1 });
        else ret.back().sc++;
		x /= sp[x];
	}
	return ret;
}

ll p2[101010];
ll power[101010][MAXD];
ll dp[101010][MAXD];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    // preprocessing
    linearSieve();

    p2[0] = 1;
    for (int i = 1; i < 101010; i++)
        p2[i] = 2 * p2[i - 1] % MOD;
    
    for (int i = 1; i < 101010; i++) {
        power[i][0] = 1;
        for (int j = 1; j < MAXD; j++) {
            power[i][j] = i * power[i][j - 1] % MOD;
        }
    }

    // solve
	cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    ll ans = 0;
    for (int r = 1; r <= n; r++) {
        vector<pii> pf = factorization(a[r]);
        // pf.push_back({ 1, 1 });

        for (auto& i : pf) {
            assert(i.fr < 101010);
            for (int j = 1; j < MAXD; j++) {
                ll res = dp[i.fr][j] * power[i.fr][min(i.sc, j)] % MOD;
                res = res * p2[n - r] % MOD;

                ans = (ans + res) % MOD;
            }
        }

        for (auto& i : pf) {
            dp[i.fr][i.sc] = (dp[i.fr][i.sc] + p2[r - 1]) % MOD;
        }

        cout << ans << '\n';
    }

    cout << ans;
}
