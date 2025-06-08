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
        ll k;
        cin >> n >> k;

        vector<ll> a(n), b(n);
        for (auto &i : a) cin >> i;
        for (auto &i : b) cin >> i;

        for (int i = 0; i < n; i++) {
            a.push_back(a[i]);
            b.push_back(b[i]);
        }

        vector<ll> psum(2 * n);
        psum[0] = a[0] - b[0];
        for (int i = 1; i < 2 * n; i++) {
            psum[i] = a[i] - b[i] + psum[i - 1];
        }

        int ans = 1;
        stack<int> stk;
        for (int i = 2 * n - 1; i >= 0; i--) {
            ll now = (i == 0 ? 0 : psum[i - 1]);
            while (!stk.empty() && now < psum[stk.top()]) {
                stk.pop();
            }

            if (a[i] > b[i] && i < n) {
                ans = max(ans, stk.top() - i + 1);
            }
            
            stk.push(i);            
        }

        cout << ans << '\n';
    }
}
