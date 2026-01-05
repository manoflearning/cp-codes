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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> a(n);
        int cnt0 = 0, lm0 = -1;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            cnt0 += a[i] == 0;
            if (a[i] == 0 && lm0 == -1) lm0 = i;
        }

        int ans = n - cnt0;
        if (cnt0) {
            multiset<int> stl, str;
            for (int i = 0; i < n; i++) {
                if (a[i]) stl.insert(a[i]);
            }
            stl.insert(a[lm0]);

            bool is_valid = 1;

            int mex = 0;
            for (int i = n - 1; i >= 1; i--) {
                if (a[i] == 0 && i != lm0) continue;

                stl.erase(stl.find(a[i]));
                str.insert(a[i]);
                while (str.count(mex)) mex++;

                if (*stl.begin() < mex) {
                    is_valid = 0;
                    break;
                }
            }

            if (is_valid) ans = n - cnt0 + 1;
        }
        
        cout << ans << '\n';
    }
}
