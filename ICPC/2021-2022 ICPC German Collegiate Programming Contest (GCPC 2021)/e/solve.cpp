#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int C = 1010101;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n, m;
    cin >> n >> m;

    vector<vector<pii>> a(C);
    for (int i = 0; i < m; i++) {
        int now, d, c;
        cin >> now >> d >> c;
        now--;
        a[c].push_back({now, d});
    }

    int q; cin >> q;
    vector<int> w(q);
    for (auto &i : w) cin >> i;

    vector<int> ord(q);
    iota(all(ord), 0);
    sort(all(ord), [&](int i, int j) {
        return w[i] > w[j];
    });

    vector<int> ans(q);

    int j = C - 1;
    vector<int> x(n - 1, -1);
    int sum_x = 0, block_cnt = n - 1;
    for (const int i : ord) {
        while (w[i] <= j) {
            for (const auto [now, d] : a[j]) {
                if (x[now] == -1) {
                    sum_x += d;
                    x[now] = d;
                    block_cnt--;
                } else if (d < x[now]) {
                    sum_x -= x[now];
                    sum_x += d;
                    x[now] = d;
                }
            }
            j--;
        }

        ans[i] = (block_cnt > 0 ? -1 : sum_x);
    }

    for (int i = 0; i < q; i++) {
        if (ans[i] == -1) {
            cout << "impossible\n";
        } else {
            cout << ans[i] << '\n';
        }
    }
}
