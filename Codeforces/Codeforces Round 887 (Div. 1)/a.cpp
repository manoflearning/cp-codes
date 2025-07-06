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

        vector<ll> a(n);
        for (auto &i : a) cin >> i;

        ll now = 1;
        for (int i = 0; i < k; i++) {
            int l = 0, r = n;
            while (l < r) {
                int mid = (l + r) >> 1;
                if (a[mid] <= now) l = mid + 1;
                else r = mid;
            }

            ll nxt = now + l;
            // cout << nxt << ' ';
            for (int j = l; j < n; j++) {
                if (nxt >= a[j]) nxt++;
                else break;
            }
            // cout << nxt << ' ';

            now = nxt;
        }

        cout << now << '\n';
    }
}
