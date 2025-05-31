#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int INF = 1e9 + 7;

int n, q;
vector<int> b;
vector<int> x, y, z;
vector<int> lb, ub;
bool is_valid = 1;

void init() {
    is_valid = 1;
}

void input() {
    cin >> n >> q;
    b.resize(n);
    for (auto &i : b) cin >> i;
    x.resize(q);
    y.resize(q);
    z.resize(q);
    for (int i = 0; i < q; i++) {
        cin >> x[i] >> y[i] >> z[i];
        x[i]--, y[i]--, z[i]--;
    }
}

void solve() {
    lb.resize(n);
    ub.resize(n);
    for (int i = 0; i < n; i++)
        lb[i] = ub[i] = b[i];

    for (int i = q - 1; i >= 0; i--) {
        if (x[i] == y[i]) {
            if (z[i] == x[i]) {
                continue;
            } else {
                if (lb[z[i]] > ub[x[i]]) {
                    is_valid = 0;
                    return;
                }

                lb[x[i]] = max(lb[z[i]], lb[x[i]]);

                lb[z[i]] = -INF;
                ub[z[i]] = INF;
            }
        } else {
            if (z[i] == x[i] || z[i] == y[i]) {
                if (lb[z[i]] > min(ub[x[i]], ub[y[i]])) {
                    is_valid = 0;
                    return;
                }

                lb[x[i]] = max(lb[z[i]], lb[x[i]]);
                lb[y[i]] = max(lb[z[i]], lb[y[i]]);

                ub[z[i]] = INF;
            } else {
                if (lb[z[i]] > min(ub[x[i]], ub[y[i]])) {
                    is_valid = 0;
                    return;
                }

                lb[x[i]] = max(lb[z[i]], lb[x[i]]);
                lb[y[i]] = max(lb[z[i]], lb[y[i]]);

                lb[z[i]] = -INF;
                ub[z[i]] = INF;
            }
        }
    }
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
        init();

        input();

        solve();

        if (is_valid) {
            for (int i = 0; i < n; i++) {
                cout << (lb[i] == -INF ? 0 : lb[i]) << ' ';
            }
            cout << '\n';
        } else cout << -1 << '\n';
    }
}
