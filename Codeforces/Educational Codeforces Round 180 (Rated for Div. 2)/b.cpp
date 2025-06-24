#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int INF = 1e9 + 7;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<ll> a(n);
        for (auto &i : a) cin >> i;

        int ans = INF;
        for (int i = 0; i + 1 < n; i++) {
            if (abs(a[i] - a[i + 1]) <= 1) {
                ans = 0;
                break;
            }
        }

        for (int i = 0; i + 2 < n; i++) {
            bool x1 = (a[i] < a[i + 1]);
            bool x2 = (a[i + 2] < a[i + 1]);
            if (x1 == x2) ans = min(ans, 1);
        }

        cout << (ans == INF ? -1 : ans) << '\n';
    }
}
