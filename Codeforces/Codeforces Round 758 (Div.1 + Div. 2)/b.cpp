#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

bool is_valid(const vector<int>& ans, int n, int a, int b) {
    unordered_set<int> st;
    int ad = 0, bd = 0;
    for (int i = 0; i < n; i++) {
        st.insert(ans[i]);
        if (ans[i] < 1 || n < ans[i]) return 0;
        if (i - 1 >= 0 && i + 1 < n) {
            if (ans[i - 1] < ans[i] && ans[i] > ans[i + 1]) ad++;
            if (ans[i - 1] > ans[i] && ans[i] < ans[i + 1]) bd++;
        } 
    }
    // cout << a << ' ' << ad << ' ' << b << ' ' << bd << ' ' << sz(st) << ' ' << n << '\n';
    return a - ad == 0 && b - bd == 0 && sz(st) == n;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n, a, b;
        cin >> n >> a >> b;

        bool is_swaped = 0;
        if (a < b) {
            is_swaped = 1;
            swap(a, b);
        }

        vector<int> ans(n);
        ans[0] = 1;

        int lb = 2, ub = n, idx = 1;
        int ad = 0, bd = 0;
        while ((a - ad > 0 || b - bd > 0) && idx + 1 < n) {
            if (a - ad > 0) {
                ad++;
                ans[idx++] = ub--;
            }
            if (b - bd > 0) {
                bd++;
                ans[idx++] = lb++;
            }
        }

        if (is_swaped) {
            swap(a, b);
            lb = n - lb + 1;
            ub = n - ub + 1;
            swap(lb, ub);
            for (auto &i : ans) i = n - i + 1;
        }

        if (ans[idx - 1] == lb - 1) {
            while (lb <= ub) {
                ans[idx++] = lb++;
            }
        } else {
            while (lb <= ub) {
                ans[idx++] = ub--;
            }
        }

        // for (auto &i : ans) cout << i << ' ';
        // cout << '\n';

        if (is_valid(ans, n, a, b)) {
            for (auto &i : ans) cout << i << ' ';
            cout << '\n';
        } else {
            cout << -1 << '\n';
        }
    }
}
