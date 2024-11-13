#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const ll INF = 1e18;

vector<bool> vis(1010101);

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    ll A, B;
    cin >> A >> B;

    ll ans = 0, cnt = 0;
    for (ll n = A; n <= B; n++) {
        vector<ll> arr;

        ll x = n;
        while (!vis[x]) {
            vis[x] = 1;
            arr.push_back(x);
            string s = to_string(x);
            ll y = 0;
            for (auto &c : s) y += (c - '0') * (c - '0');
            x = y;
        }

        ll res = INF;
        for (auto &i : arr) {
            res = min(res, i);
            vis[i] = 0;
        }
        ans += res;
    }

    cout << ans;
}
