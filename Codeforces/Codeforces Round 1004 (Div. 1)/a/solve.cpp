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

int query(int i, int j) {
    cout << "? " << i << ' ' << j << '\n';
    cout.flush();
    int ret; cin >> ret;
    return ret;
}

void answer(char c) {
    cout << "! " << c << '\n';
    cout.flush();
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> x(n + 1);
        for (int i = 1; i <= n; i++) cin >> x[i];

        map<int, int> vis;
        for (int i = 1; i <= n; i++) {
            vis[x[i]] = i;
        }

        if (sz(vis) < n) {
            int miss = -1;
            for (int i = 1; i <= n; i++) {
                if (!vis.count(i)) {
                    miss = i;
                    break;
                }
            }

            int res = query(miss, miss == 1 ? 2 : 1);
            answer(res == 0 ? 'A' : 'B');
        } else {
            int i = vis[1], j = vis[n];

            int res = query(i, j);
            if (res < n - 1) {
                answer('A');
            } else {
                res = query(j, i);
                answer(res < n - 1 ? 'A' : 'B');
            }
        }
    }
}
