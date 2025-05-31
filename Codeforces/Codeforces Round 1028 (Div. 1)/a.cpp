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

int gcd(int x, int y) {
    if (!y) return x;
    return gcd(y, x % y);
}

int n;
vector<int> a;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        cin >> n;
        a.resize(n);
        for (auto &i : a) cin >> i;

        sort(all(a));

        int g = a[0];
        for (int i = 1; i < n; i++)
            g = gcd(g, a[i]);

        int ans = 0;
        while (1) {
            bool g_exists = 0;
            for (auto &i : a)
                if (i == g) g_exists = 1;
            if (g_exists) break;

            int opt = INF, opt_i = -1;
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    int gij = gcd(a[i], a[j]);
                    if (gij < opt) {
                        opt = gij;
                        opt_i = i;
                    }
                }
            }
            a[opt_i] = opt;

            ans++;
        }

        for (auto &i : a) {
            if (i != g) ans++;
        }
        cout << ans << '\n';
    }
}
