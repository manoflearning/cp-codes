#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(x) (x).begin(), (x).end()

const ll INF = 1e18;

int n, c;
ll y;
vector<ll> x;
ll x_en;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> c >> y;
    for (int i = 1; i <= n; i++) {
        int w; cin >> w;
        x.push_back(w);
    }

    ll ans1 = 0;
    while (1) {
        ll mn = INF;
        bool is_rem = 0;
        for (int i = 1; i <= n; i++) {
            if (i == c) continue;
            mn = min(mn, x[i]);
            if (x[i] > 0) is_rem = 1;
        }

        if (mn == 0 && is_rem) {
            cout << "impossible";
            exit(0);
        }
        if (mn == 0 && !is_rem) break;

        ans1 += mn;
        for (int i = 1; i <= n; i++) {
            if (i == c) continue;
            x[i] -= mn;
        }
        x[c] += mn * y;
    }

    ll ans2 = 0;
    for (auto& i : x) ans2 += i;

    cout << ans1 << ' ' << ans2;
}