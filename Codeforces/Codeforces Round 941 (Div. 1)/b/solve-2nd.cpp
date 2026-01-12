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
        int n, k;
        cin >> n >> k;

        vector<int> a;

        int t = 0;
        while ((1 << t) <= k) t++;
        t--;

        if (k != (1 << t)) {
            a.push_back(k - (1 << t));
        }
        a.push_back(k + 1);
        a.push_back(k + 2);

        for (int i = 0; i < 20; i++) {
            if (i != t) a.push_back(1 << i);
        }

        cout << sz(a) << '\n';
        for (auto &i : a) cout << i << ' ';
        cout << '\n';
    }
}
