#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

// int n;
// vector<ll> b;
// set<ll> st;
// bool is_done = 0;

// void init() {
//     st.clear();
//     is_done = 0;
// }

// void bt(int i, ll sum, int cnt_c, int cnt_d) {
//     if (2 * n == i) {
//         cout << "fuck " << sum << ' ' << cnt_c << ' ' << cnt_d << '\n';
//         if (sum > 0 && !st.count(sum)) {
//             is_done = 1;
//         }
//         return;
//     }

//     if (!is_done && cnt_c < n) {
//         b[i] = abs(b[i]);
//         bt(i + 1, sum + b[i], cnt_c + 1, cnt_d);
//     }
//     if (!is_done && cnt_d < n) {
//         b[i] = -abs(b[i]);
//         bt(i + 1, sum + b[i], cnt_c, cnt_d + 1);
//     }
// }

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

        vector<ll> b(2 * n);
        for (auto &i : b) {
            cin >> i;
        }
        
        sort(b.rbegin(), b.rend());

        cout << b[0] << ' ';
        ll x = b[0];
        for (int i = 1; i < 2 * n; i++) {
            if (i <= n) {
                x += b[i];
            } else {
                x -= b[i];
            }
        }

        cout << x << ' ' << b[1] << ' ';
        for (int i = 2; i <= n; i++) {
            cout << b[2 * n - i + 1] << ' ' << b[i] << ' ';
        }
        cout << '\n';
    }
}
