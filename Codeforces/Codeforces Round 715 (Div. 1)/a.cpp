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
        int n; cin >> n;

        vector<string> a(3);
        for (auto &i : a) cin >> i;

        vector<int> cnt0(3), cnt1(3);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 2 * n; j++) {
                if (a[i][j] == '0') cnt0[i]++;
                if (a[i][j] == '1') cnt1[i]++;
            }
        }

        int pick0 = 0;
        for (int i = 0; i < 3; i++) {
            if (cnt0[i] >= cnt1[i]) pick0++;
        }

        vector<string> b;
        if (pick0 >= 2) {
            for (int i = 0; i < 3; i++) {
                if (cnt0[i] >= cnt1[i]) b.push_back(a[i]);
            }
        } else {
            for (int i = 0; i < 3; i++) {
                if (cnt0[i] <= cnt1[i]) b.push_back(a[i]);
            }
        }

        if (sz(b) == 3) b.pop_back();

        string ans;

        int idx0 = 0, idx1 = 0;
        while (idx0 < 2 * n || idx1 < 2 * n) {
            if (idx0 == 2 * n) {
                ans.push_back(b[1][idx1++]);
            } else if (idx1 == 2 * n) {
                ans.push_back(b[0][idx0++]);
            } else if (b[0][idx0] == b[1][idx1]) {
                ans.push_back(b[0][idx0]);
                idx0++, idx1++;
            } else if (b[1][idx1] == (pick0 >= 2 ? '0' : '1')) {
                ans.push_back(b[0][idx0++]);
            } else {
                ans.push_back(b[1][idx1++]);
            }
        }

        while (sz(ans) < 3 * n) ans.push_back('0');

        assert(sz(ans) == 3 * n);
        cout << ans << '\n';
    }
}