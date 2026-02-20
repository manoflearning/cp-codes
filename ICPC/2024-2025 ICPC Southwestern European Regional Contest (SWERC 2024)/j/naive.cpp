#pragma GCC optimize ("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int INF = 1e9 + 7;
constexpr int M = 16;
constexpr int N = 16;

int m, n, s;
vector<vector<int>> a;
vector<int> tgt_h, tgt_v;
vector<int> out_h, out_v;
vector<int> ind_h, ind_v;

int _hash(int x, int y) { return x + y * m; }

int ans = INF;
void bt(int x, int y, int acc) {
    if (ans <= acc) return;

    if (x == m) { ans = min(ans, acc); return; }
    if (y == n) bt(x + 1, 0, acc);

    if (!a[x][y]) bt(x, y + 1, acc);

    const int now = _hash(x, y);
    
    auto f = [](int i, int ind, int val) -> bool {
        bool yes = 1;
        yes &= ((ind - 1) * 1 <= val - i);
        yes &= (val - i <= (ind - 1) * 9);
        return yes;
    };

    const int lb = max({1, 
        tgt_h[out_h[now]] - (ind_h[out_h[now]] - 1) * 9, 
        tgt_v[out_v[now]] - (ind_v[out_v[now]] - 1) * 9});
    const int ub = min({9, 
        tgt_h[out_h[now]] - (ind_h[out_h[now]] - 1) * 1, 
        tgt_v[out_v[now]] - (ind_v[out_v[now]] - 1) * 1});

    for (int i = lb; i <= ub; i++) {
        ind_h[out_h[now]]--, ind_v[out_v[now]]--;
        tgt_h[out_h[now]] -= i, tgt_v[out_v[now]] -= i;

        bt(x, y + 1, acc + abs(a[x][y] - i));

        ind_h[out_h[now]]++, ind_v[out_v[now]]++;
        tgt_h[out_h[now]] += i, tgt_v[out_v[now]] += i;
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    cin >> m >> n >> s;

    a.assign(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        string s; cin >> s;
        for (int j = 0; j < n; j++) {
            a[i][j] = s[j] - '0';
        }
    }

    tgt_h.assign(n * m, 0), tgt_v.assign(n * m, 0);
    out_h.assign(n * m, 0), out_v.assign(n * m, 0);
    ind_h.assign(n * m, 0), ind_v.assign(n * m, 0);
    for (int i = 0; i < s; i++) {
        char op; int x, y, val;
        cin >> op >> x >> y >> val;
        x--, y--;
        
        const int now = _hash(x, y);
        tgt_h[now] = tgt_v[now] = val;
        if (op == 'H') {
            for (int j = y + 1; j < n && a[x][j] > 0; j++) {
                out_h[_hash(x, j)] = now;
                ind_h[now]++;
            }
        } else {
            for (int j = x + 1; j < m && a[j][y] > 0; j++) {
                out_v[_hash(j, y)] = now;
                ind_v[now]++;
            }
        }
    }

    bt(0, 0, 0);
    if (ans == INF) {
        cout << "IMPOSSIBLE\n";
    } else {
        cout << ans << '\n';
    }
}
