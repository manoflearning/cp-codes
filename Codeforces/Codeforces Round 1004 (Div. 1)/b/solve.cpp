#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int try_include_0(const vector<int> &a) {
    int ret = 0;

    const int n = sz(a);

    map<int, int> cnt;
    for (auto &i : a) cnt[i]++;

    set<int> vis;

    int mex = 0;
    for (int i = n - 1; i >= 0; i--) {
        cnt[a[i]]--;

        if (mex > a[i] && a[i] > 0) {
            assert(vis.count(a[i]));
            vis.erase(0);
            mex = 0;
        } else if (mex == a[i]) {
            if ((a[i] == 0 && cnt[a[i]] == 0) || a[i] > 0) {
                vis.insert(a[i]);
                while (vis.count(mex)) mex++;
                ret++;
            }
        } else if (mex < a[i]) {
            vis.insert(a[i]);
            ret++;
        }
    }
    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> a(n);
        for (auto &i : a) cin >> i;

        int ans = try_include_0(a);
        cout << ans << '\n';
    }
}
