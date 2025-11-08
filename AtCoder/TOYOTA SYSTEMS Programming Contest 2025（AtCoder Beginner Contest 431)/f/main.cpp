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
constexpr int MOD = 998'244'353;

const int MAXN = 4040404;
ll fac[MAXN], inv[MAXN], facInv[MAXN];
ll binom(int n, int r) {
    return fac[n] * facInv[r] % MOD * facInv[n - r] % MOD;
}

constexpr int N = 202020;
constexpr int A = 1010101;

int n, d;
int a[N], ra[A], pra[A];

void input() {
    cin >> n >> d;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        ra[a[i]]++;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    // Preprocessing in O(N)
    fac[0] = fac[1] = inv[1] = 1;
    facInv[0] = facInv[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        fac[i] = i * fac[i - 1] % MOD;
        inv[i] = -(MOD / i) * inv[MOD % i] % MOD;
        if (inv[i] < 0) inv[i] += MOD;
        facInv[i] = facInv[i - 1] * inv[i] % MOD;
    }

    input();

    // sort(a + 1, a + n + 1);

    for (int i = 1; i < A; i++) {
        pra[i] = ra[i] + pra[i - 1];
    }

    ll ans = 1;
    for (int i = 1; i < A; i++) {
        if (!ra[i]) continue;

        int x = pra[i - 1] - pra[max(0, i - d - 1)] + 1;
        int y = ra[i];

        ans = ans * binom(x + y - 1, y) % MOD;
    }

    cout << ans;
}