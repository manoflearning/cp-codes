#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

void query1(int x) {
    cout << "+ " << x << '\n';
    cout.flush();
    int ret; cin >> ret;
    if (ret == -2) exit(0);
}

int query2(int i, int j) {
    cout << "? " << i << ' ' << j << '\n';
    cout.flush();
    int ret; cin >> ret;
    if (ret == -2) exit(0);
    return ret;
}

void output(const vector<int> &p1, const vector<int> &p2) {
    cout << "! ";
    for (auto &i : p1) cout << i << ' ';
    for (auto &i : p2) cout << i << ' ';
    cout << '\n';
    cout.flush();
    int ret; cin >> ret;
    if (ret == -2) exit(0);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        query1(n);
        query1(n + 1);

        int mx = -1, opt = -1;
        for (int j = 2; j <= n; j++) {
            int dist = query2(1, j);
            if (mx < dist) { mx = dist, opt = j; }
        }

        vector<int> ord1(n), ord2(n);
        int i = 0, j = n - 1;
        int lb = 0, ub = n - 1;
        while (lb <= ub) {
            ord1[i++] = ord2[j--] = ub--;
            if (lb <= ub) ord1[i++] = ord2[j--] = lb++;
        }

        vector<int> p1(n), p2(n);
        p1[opt - 1] = ord1[0] + 1;
        p2[opt - 1] = ord2[0] + 1;
        for (int j = 1; j <= n; j++) {
            if (j == opt) continue;
            const int dist = query2(opt, j);
            p1[j - 1] = ord1[dist] + 1;
            p2[j - 1] = ord2[dist] + 1;
        }

        // sort(all(p1), [&](int i, int j) {
        //     return ord[i] < ord[j];
        // });

        output(p1, p2);
    }
}
