#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

const int MOD = 998244353;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n; cin >> n;

    ll ans = 0;
    ll add = 2;
    for (int i = 0; i < n - 1; i++) {
        ans = (ans + (add + MOD - 1)) % MOD;
        add = add * 2 % MOD;
    }

    cout << ans;
}
