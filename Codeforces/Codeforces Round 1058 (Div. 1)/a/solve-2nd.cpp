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

int query(const vector<int> &a) {
    cout << "? " << sz(a) << ' ';
    for (auto &i : a) cout << i << ' ';
    cout << '\n';
    cout.flush();

    int ret; cin >> ret;
    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> ans(2 * n + 1);

        vector<int> a;
        a.push_back(1);
        for (int i = 2; i <= 2 * n; i++) {
            a.push_back(i);
            int res = query(a);
            if (res) {
                a.pop_back();
                ans[i] = res;
            }
        }

        assert(sz(a) == n);

        vector<int> b;
        for (int i = 1; i <= 2 * n; i++) {
            if (ans[i]) b.push_back(i);
        }

        for (int i = 1; i <= 2 * n; i++) {
            if (ans[i]) continue;
            b.push_back(i);
            int res = query(b);
            b.pop_back();

            ans[i] = res;
        }

        cout << "! ";
        for (int i = 1; i <= 2 * n; i++) {
            cout << ans[i] << ' ';
        }
        cout << '\n';
        cout.flush();
    }
}