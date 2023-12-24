// if K = 0
// v_0 := N
// deg_0 := N - 1

// if K = 1
// v_1 := v_0 * deg_0 / 2
// deg_1 := 2 * (deg_0 - 1)

// if K = 2
// v_2 := v_1 * deg_1 / 2

// (인접한 간선의 수) = (degree - 1)

// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

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
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int N, K;

ll power(ll x, ll y) {
    if (y == 0) return 1;
    if (y == 1) return x;
    ll res = power(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N >> K;

    if (K == 0) {
        cout << N;
        return 0;
    }

    ll v = N, deg = N - 1;
    for (int i = 0; i < K; i++) {
        v = v * deg % MOD * power(2, MOD - 2) % MOD;
        deg = 2 * (deg - 1) % MOD;
    }

    cout << v;
}