#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const ll MOD = 1e9 + 7;
ll exp(ll x, ll e) {
    ll ret = 1;
    while(e) {
        if(e & 1) ret = ret * x % MOD;
        x = x * x % MOD; e >>= 1;
    }
    return ret;
}
int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    ll p, q, n; cin >> p >> q >> n;
    ll x = 1, y = 1, z = 0;
    vector<ll> ans;
    ans.push_back(0);
    ans.push_back(1);

    ll inv_q = exp(q, MOD - 2);
    ll v = 1;
    for(int i = 2; i < n; i++) {
        if(p * x <= q * (x + 2) && (y + 2) * x <= y * (x + 2)) {
            v = v * ((x + 2) * exp(x, MOD - 2) % MOD) % MOD;
            x++;
        }
        else if(p * y <= q * (y + 2) && (x + 2) * y <= x * (y + 2)) {
            v = v * ((y + 2) * exp(y, MOD - 2) % MOD) % MOD;
            y++;
        }
        else {
            v = v * (p * inv_q % MOD) % MOD;
        }
        ans.push_back(v);
    }

    for(int i = 0; i < n; i++) cout << ans[i] << ' ';
}
