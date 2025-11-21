#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int N = 202020;

int gcd(int x, int y) {
    if (!y) return x;
    return gcd(y, x % y);
}

int n, p[N];
ll pgcd[N], sgcd[N];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> p[i];

    pgcd[1] = p[1];
    for (int i = 2; i <= n; i++) {
        pgcd[i] = gcd(p[i], pgcd[i - 1]);
    }
    sgcd[n] = p[n];
    for (int i = n - 1; i >= 1; i--) {
        sgcd[i] = gcd(p[i], sgcd[i + 1]);
    }

    ll ans = 0;
    for (int i = 2; i <= n - 1; i++) {
        ans += min(pgcd[i], sgcd[i]);
    }
    ans += pgcd[n];
    cout << ans;
}