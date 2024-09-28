#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 6060;
const int MOD = 998'244'353;

ll fac[MAXN], inv[MAXN], facInv[MAXN], p2[MAXN];
inline ll binom(int n, int r) {
    return fac[n] * facInv[r] % MOD * facInv[n - r] % MOD;
}

int u[MAXN], v[MAXN];

bool is_valid(const string& s) {
    int top = 0;
    for (auto& c : s) {
        if (c == '(') top++;
        else top--;
        if (top < 0) return 0;
    }
    return 1;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    // preprocessing
    fac[0] = fac[1] = inv[1] = 1;
    facInv[0] = facInv[1] = 1;
    p2[0] = 1, p2[1] = 2;
    for (int i = 2; i < MAXN; i++) {
        fac[i] = i * fac[i - 1] % MOD;
        inv[i] = -(MOD / i) * inv[MOD % i] % MOD;
        if (inv[i] < 0) inv[i] += MOD;
        facInv[i] = facInv[i - 1] * inv[i] % MOD;
        p2[i] = 2 * p2[i - 1] % MOD;
    }

    // solve
    int n;
    string s;
    cin >> n >> s;

    if (is_valid(s)) {
        cout << (p2[sz(s)] + MOD - 1) % MOD;
        return 0;
    }

    n <<= 1;
    s = '*' + s;

    int mx = 0;
    for(int i = 1; i <= n; i++){
        u[i] = (s[i] == '(') + u[i - 1];
        v[i] = (s[i] == ')') + v[i - 1];
        mx = max(mx, v[i] - u[i]);
    }

    int t = (mx + 1) / 2 + 1;
    int a = (s[1] == ')'), b = (s[n] == '(');

    // cout << "n: " << n << '\n';
    // cout << "t: " << t << '\n';
    // cout << "a: " << a << '\n';
    // cout << "b: " << b << '\n';

    ll ans = 1;
    ans = ans * (p2[t - a] + MOD - 1) % MOD * (p2[t - b] + MOD - 1) % MOD;

    // cout << "p2[n - 2 * t + (a + b)]: " << p2[n - 2 * t + (a + b)] << '\n'; 
    ans = ans * p2[n - 2 * t + (a + b)] % MOD;

    cout << ans;
}
