#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n, q;
        cin >> n >> q;

        vector<int> b(n);
        for (auto &i : b) cin >> i;

        vector<int> x(q), y(q), z(q);
        for (int i = 0; i < q; i++) {
            cin >> x[i] >> y[i] >> z[i];
            x[i]--, y[i]--, z[i]--;
        }

        vector<int> lb = b;
        for (int i = q - 1; i >= 0; i--) {
            int tmp = lb[z[i]];
            lb[z[i]] = 0;
            lb[x[i]] = max(lb[x[i]], tmp);
            lb[y[i]] = max(lb[y[i]], tmp);
        }

        vector<int> c = lb;
        for (int i = 0; i < q; i++) {
            c[z[i]] = min(c[x[i]], c[y[i]]);
        }

        if (c == b) {
            for (auto &i : lb) cout << i << ' ';
            cout << '\n';
        } else cout << -1 << '\n';
    }
}