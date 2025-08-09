// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(c) (c).begin(), (c).end()

const int N = 101010;
const int M = 202020;
const ll INF = 1e18;

int flag;
struct Seg {
    vector<ll> t;
    void build(int n) {
        t.clear();
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
    }
    void add(int p, int val) {
        for (t[p += flag - 1] += val; p > 1; p >>= 1) {
            t[p >> 1] = t[p] + t[p ^ 1];
        }
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
} seg;

int n, m, mx_y;
ll r1[N], r2[N];
ll y[M], c1[M], c2[M];
vector<pii> by_y[2 * N + M];
vector<int> by_y_in[2 * N + M], by_y_out[2 * N + M];
vector<int> by_x_in[N], by_x_out[N];

void init() {
    for (int i = 0; i < 2 * N + M; i++) {
        by_y[i].clear();
        by_y_in[i].clear();
        by_y_out[i].clear();
    }
    for (int i = 0; i < N; i++) {
        by_x_in[i].clear();
        by_x_out[i].clear();
    }
}

void input() {
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> r1[i] >> r2[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> y[i] >> c1[i] >> c2[i];
    }
}

void coor_comp() {
    vector<ll> cc(1, -INF);
    for (int i = 1; i <= n; i++) {
        cc.push_back(r1[i]);
        cc.push_back(r2[i]);
    }
    for (int i = 1; i <= m; i++) {
        cc.push_back(y[i]);
    }
    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());
    for (int i = 1; i <= n; i++) {
        r1[i] = lower_bound(all(cc), r1[i]) - cc.begin();
        r2[i] = lower_bound(all(cc), r2[i]) - cc.begin();
        by_y_in[r1[i]].push_back(i);
        by_y_out[r2[i]].push_back(i);
    }
    for (int i = 1; i <= m; i++) {
        y[i] = lower_bound(all(cc), y[i]) - cc.begin();
    }
    mx_y = sz(cc) - 1;
}

void concat_brush() {
    for (int i = 1; i <= m; i++) {
        by_y[y[i]].push_back({c1[i], c2[i]});
    }
    for (int i = 1; i <= mx_y; i++) {
        sort(all(by_y[i]));

        vector<pii> tmp;
        for (int j = 0; j < sz(by_y[i]); j++) {
            if (!tmp.empty() && by_y[i][j].fr <= tmp.back().sc + 1) {
                tmp.back().sc = max(tmp.back().sc, by_y[i][j].sc);
            } else {
                tmp.push_back(by_y[i][j]);
            }
        }
        by_y[i] = tmp;

        for (auto &j : by_y[i]) {
            by_x_in[j.fr].push_back(i);
            by_x_out[j.sc].push_back(i);
        }
    }
}

ll solve1() {
    ll ret = 0;

    seg.build(mx_y);

    for (int i = 1; i <= n; i++) {
        for (auto &j : by_x_in[i]) {
            seg.add(j, 1);
        }

        ret += seg.query(r1[i], r2[i]);

        for (auto &j : by_x_out[i]) {
            seg.add(j, -1);
        }
    }

    return ret;
}

int solve2() {
    int ret = 0;

    seg.build(n);
    for (int i = 1; i <= mx_y; i++) {
        for (auto &j : by_y_in[i]) {
            seg.add(j, 1);
        }

        int prv_x = 0;
        for (auto &j : by_y[i]) {
            int tmp = seg.query(j.fr, j.sc);
            if ((prv_x == 0 || seg.query(prv_x + 1, j.fr - 1) > 0) && tmp > 0) {
                ret++;
            }
            if (tmp > 0) prv_x = j.sc;
        }

        for (auto &j : by_y_out[i]) {
            seg.add(j, -1);
        }
    }

    return ret;
}

int main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << '\n';

        init();

        input();

        coor_comp();

        concat_brush();

        cout << solve1() << ' ' << solve2() << '\n';

        cout << flush;
    }
}