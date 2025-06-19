#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

string solve(int n, const vector<int> &a, const vector<int> &b) {
    vector<int> ord(n);
    iota(all(ord), 0);
    sort(all(ord), [&](int p1, int p2) {
        return a[p1] < a[p2];
    });

    vector<int> pmax(n);
    pmax[0] = b[ord[0]];
    for (int i = 1; i < n; i++) {
        pmax[i] = max(b[ord[i]], pmax[i - 1]);
    }

    vector<int> smin(n);
    smin[n - 1] = b[ord[n - 1]];
    
    int opt = b[ord[n - 1]];
    for (int i = n - 2; i >= 0; i--) {
        int res = 1e9 + 7;
        if (b[ord[i]] > smin[i + 1]) {
            res = opt;
        } else {
            opt = min(opt, b[ord[i]]);
        }
        smin[i] = min(res, smin[i + 1]);
    }

    string ret(n, '0');
    for (int i = 0; i < n; i++) {
        if (i + 1 < n) {
            if (pmax[i] > smin[i + 1]) ret[ord[i]] = '1';
        } else {
            ret[ord[i]] = '1';
        }
    }

    return ret;
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
        int n; cin >> n;

        vector<int> a(n), b(n);
        for (auto &i : a) cin >> i;
        for (auto &i : b) cin >> i;

        string ans1 = solve(n, a, b);
        string ans2 = solve(n, b, a);

        string ans(n, '0');
        for (int i = 0; i < n; i++) {
            if (ans1[i] == '1' || ans2[i] == '1') ans[i] = '1';
        }

        // if (ans1 != ans2) {
        //     cout << n << '\n';
        //     for (auto &i : a) cout << i << ' ';
        //     cout << '\n';
        //     for (auto &i : b) cout << i << ' ';
        //     cout << '\n';
        //     cout << ans1 << '\n' << ans2 << '\n';
        //     exit(0);
        // }

        assert(ans1 == ans2);

        cout << ans << '\n';
    }
}