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
        if (lb[z[i]] > min(ub[x[i]], ub[y[i]])) {
            is_valid = 0;
            return;
        }

        if (x[i] == y[i]) {
            if (z[i] == x[i]) {
                continue;
            } else {
                lb[x[i]] = max(lb[z[i]], lb[x[i]]);

                lb[z[i]] = 0;
                ub[z[i]] = INF;
            }
        } else {
            if (z[i] == x[i] || z[i] == y[i]) {
                lb[x[i]] = max(lb[z[i]], lb[x[i]]);
                lb[y[i]] = max(lb[z[i]], lb[y[i]]);

                ub[z[i]] = INF;
            } else {
                lb[x[i]] = max(lb[z[i]], lb[x[i]]);
                lb[y[i]] = max(lb[z[i]], lb[y[i]]);

                lb[z[i]] = 0;
                ub[z[i]] = INF;
            }
        }
    }
}

vector<int> simul(vector<int> c) {
    for (int i = 0; i < q; i++) {
        c[z[i]] = min(c[x[i]], c[y[i]]);
        // for (int j = 0; j < n; j++) cout << c[j] << ' ';
        // cout << '\n';
    }
    return c;
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

        is_valid &= (b == simul(lb));

        if (is_valid) {
            for (int i = 0; i < n; i++) {
                cout << lb[i] << ' ';
            }
            cout << '\n';
            // simul(lb);
        } else cout << -1 << '\n';
    }
}
