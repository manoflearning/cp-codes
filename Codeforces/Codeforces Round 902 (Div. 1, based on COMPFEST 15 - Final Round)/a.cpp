#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n;
        ll p;
        cin >> n >> p;

        vector<ll> a(n), b(n);
        for (auto &i : a) cin >> i;
        for (auto &i : b) cin >> i;

        vector<int> ord(n);
        iota(all(ord), 0);
        sort(all(ord), [&](int i, int j) {
            return b[i] < b[j];
        });

        ll ans = p;
        queue<int> qu;
        qu.push(ord[0]);
        for (int i = 1; i < n; i++) {
            if (a[qu.front()] == 0) qu.pop();

            ans += min(p, b[qu.front()]);
            a[qu.front()]--;
            qu.push(ord[i]);
        }

        cout << ans << '\n';
    }
}
