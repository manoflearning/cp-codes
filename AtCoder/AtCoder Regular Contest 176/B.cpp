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
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int p2mod10(ll exp) {
    if (exp == 0) return 1;
    if (exp == 1) return 2;
    int res = p2mod10(exp / 2);
    return res * res % 10 * (exp & 1 ? 2 : 1) % 10;
}

int solve(ll N, ll M, ll K) {
    if (N < M) return p2mod10(N);

    ll mod = M - K;
    // ll N_new = N - (M - K);
    ll N_new = M / mod * mod + N % mod;
    while (M <= N_new) N_new -= mod;
    return solve(N_new, M, K);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        ll N, M, K;
        cin >> N >> M >> K;

        cout << solve(N, M, K) << '\n';
    }
}