#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int MOD = 998'244'353;

int main() {
    freopen("substantial_losses_input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << ": ";
        
        ll w, g, l;
        cin >> w >> g >> l;

        ll ans = (w - g) % MOD * (2 * (l % MOD) + 1) % MOD;
        cout << ans << '\n';
    }
}
