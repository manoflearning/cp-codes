#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MOD = 998'244'353;
const int N = 101010;

ll pow2[N];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    pow2[0] = 1;
    for (int i = 1; i < N; i++) {
        pow2[i] = 2 * pow2[i - 1] % MOD;
    }

    int n; cin >> n;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<int> b(n + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j += i) {
            b[i] = max(b[i], a[j]);
        }
    }

    map<int, int> mp;
    for (int i = 1; i <= n; i++) {
        mp[b[i]]++;
    }

    ll ans = 0;

    int acc = 0;
    for (auto [x, y] : mp) {
        ll cnt = pow2[acc] * (pow2[y] + MOD - 1) % MOD;
        ans = (ans + cnt * x) % MOD;
        acc += y;
    }

    cout << ans;
}
