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

int mex(const vector<int> &a) {
    set<int> st;
    for (auto &i : a) st.insert(i);

    int ret = 0;
    while (st.count(ret)) ret++;
    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> a(n);
        for (auto &i : a) cin >> i;

        const int m = mex(a);
        
        if (m == n) {
            cout << "No\n";
            continue;
        }

        int l = -1, r = -1;
        for (int i = 0; i < n; i++) {
            if (a[i] == m + 1) {
                if (l == -1) l = i;
                r = i;
            }
        }

        if (l == -1) {
            cout << "Yes\n";
        } else {
            for (int i = l; i <= r; i++) a[i] = m;
            const int k = mex(a);
            if (m + 1 == k) cout << "Yes\n";
            else cout << "No\n";
        }
    }
}