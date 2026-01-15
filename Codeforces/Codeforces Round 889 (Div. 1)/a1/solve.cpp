#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

bool yes(vector<ll> a, const vector<pii> &ans) {
    if (sz(ans) > 50) return 0;
    for (auto [i, j] : ans) {
        a[i] += a[j];
    }
    for (int i = 1; i + 1 < sz(a); i++) {
        if (a[i] > a[i + 1]) return 0;
    }
    return 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        int pos = -1, neg = -1;
        vector<ll> a(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            if (a[i] > 0) {
                if (pos == -1 || a[pos] < a[i]) pos = i;
            }
            if (a[i] < 0) {
                if (neg == -1 || a[neg] > a[i]) neg = i;
            }
        }

        vector<pii> ans;

        auto b = a;
        if (pos != -1) {
            for (int i = 0; i < 5; i++) {
                ans.push_back({pos, pos});
                b[pos] += b[pos];
            }
            
            ans.push_back({1, pos});
            b[1] += b[pos];

            for (int i = 1; i + 1 <= n; i++) {
                while (b[i] > b[i + 1]) {
                    ans.push_back({i + 1, i});
                    b[i + 1] += b[i];
                }
            }
        } else {
            if (neg != -1) {
                for (int i = 0; i < 5; i++) {
                    ans.push_back({neg, neg});
                    b[neg] += b[neg];
                }

                ans.push_back({n, neg});
                b[n] += b[neg];
            }
            
            for (int i = n; i - 1 >= 1; i--) {
                while (b[i - 1] > b[i]) {
                    ans.push_back({i - 1, i});
                    b[i - 1] += b[i];
                }
            }
        }

        cout << sz(ans) << '\n';
        for (const auto &[i, j] : ans) {
            cout << i << ' ' << j << '\n';
        }

        // cout.flush();
        assert(yes(a, ans));
    }
}
