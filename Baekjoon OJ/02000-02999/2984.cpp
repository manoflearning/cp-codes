#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const ll INF = 1e18;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n; cin >> n;
    vector<int> a, b;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        a.push_back(x);
        b.push_back(y);
    }

    sort(all(a));
    sort(all(b));

    ll ans = 0;

    bool case_1 = 1;
    for (int i = 0; i < n; i++) {
        if (a[i] == b[i]) case_1 = 0;
    }

    if (case_1) {
        ll ans = 0;
        for (int i = 0; i < n; i++) {
            ans += abs(a[i] - b[i]);
        }
        cout << ans;
    } else {
        vector<pll> rg;
        int prv = -100;
        for (int i = 0; i < n; i++) {
            if (a[i] == b[i]) {
                if (prv == -100) prv = i;
            } else {
                if (prv != -100) {
                    rg.push_back({prv, i - 1});
                    prv = -100;
                }
            }
        }
        if (prv != -100) rg.push_back({prv, n - 1});

        for (auto [l, r] : rg) {
            if (l == r) {
                ll res1 = 0;
                ll res2 = (l == n - 1 ? INF : abs(a[l] - b[l + 1]) + abs(a[l + 1] - b[l]));

                if (l == 0 || (l > 0 && a[l - 1] == b[l])) res1 = INF;
                else res1 = abs(a[l] - b[l - 1]) + abs(a[l - 1] - b[l]);

                if (l == n - 1 || (l > 0 && a[l - 1] == b[l])) res1 = INF;
                else res1 = abs(a[l] - b[l - 1]) + abs(a[l - 1] - b[l]);

                if (res1 <= res2) {
                    swap(a[l], a[l - 1]);
                } else {

                }
            } else {

            }
        }
    }
}
