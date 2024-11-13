#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define rep(i, n) for(int i = 0; i < (n); i++)

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    ll X; cin >> X;

    vector<ll> ans;
    for (ll p = 1; p <= X; p++) {
        ll l = 1, r = p - 1;
        while (l < r) {
            ll mid = (l + r) >> 1;
            if (p * p - mid * mid > X) l = mid + 1;
            else r = mid;
        }
        if (p * p - l * l == X) {
            ans.push_back(p);
        }
    }

    cout << sz(ans) << '\n';
    for (int i = 0; i < sz(ans); i++) {
        cout << ans[i];
        if (i + 1 < sz(ans)) cout << ' ';
    }
}
