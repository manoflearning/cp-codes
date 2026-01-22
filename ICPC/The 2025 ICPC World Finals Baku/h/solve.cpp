#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr ll INF = 4e18;
constexpr ll L = 1e6;
constexpr int D = 9;

array<ll, 19> p10;

ll m;
int n;
vector<int> p;
int p_min = 1000;

vector<ll> dist;
array<int, D> ans{};

array<array<array<array<array<array<ll, 10>, 1000>, 20>, 2>, 2>, 2> dp;
array<array<array<array<array<array<bool, 10>, 1000>, 20>, 2>, 2>, 2> vis;

void input() {
    cin >> m >> n;
    p.assign(n, 0);
    for (auto &i : p) {
        cin >> i;
        p_min = min(p_min, i);
    }
}

void dijkstra() {
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    dist.assign(p_min, INF);

    dist[0] = 0;
    pq.push({dist[0], 0});
    while (!pq.empty()) {
        auto [w, now] = pq.top();
        pq.pop();
        
        if (dist[now] < w) continue;

        for (int i : p) {
            const int nxt = (now + i) % p_min;
            if (dist[nxt] <= w + i) continue;
            dist[nxt] = w + i;
            pq.push({dist[nxt], nxt});
        }
    }
}

void update_naive(ll x) {
    assert(x > 0);
    array<int, D> cnt{};
    while (x) {
        const int y = x % 10 == 9 ? 6 : x % 10;
        cnt[y]++;
        x /= 10;
    }
    for (int i = 0; i < D; i++) {
        ans[i] = max(ans[i], cnt[i]);
    }
}

ll f(bool tl, bool tu, bool st, int x, int rem, const int d) {
    ll &ret = dp[tl][tu][st][x][rem][d];
    if (vis[tl][tu][st][x][rem][d]) return ret;

    vis[tl][tu][st][x][rem][d] = 1;
    if (x == 0) return ret = (dist[rem] == INF ? -INF : 0);    

    ret = -INF;

    const int lb = L / p10[x - 1] % 10;
    const int ub = m / p10[x - 1] % 10;

    for (int i = (!tl ? lb : 0); i <= (!tu ? ub : 9); i++) {
        const bool n_tl = tl || lb < i;
        const bool n_tu = tu || i < ub;
        const bool n_st = st || 0 < i;
        const int n_p = x - 1;
        const int n_rem = (10 * rem + i) % p_min;

        int add = 0;
        if (d == 6) add = i == 6 || i == 9;
        else if (d == 0) add = i == 0 && st;
        else add = i == d;

        ret = max(ret, add + f(n_tl, n_tu, n_st, n_p, n_rem, d));
    }

    return ret;
}

void output() {
    for (int i = 0; i < D; i++) {
        if (ans[i]) cout << i << ' ' << ans[i] << '\n';
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    p10[0] = 1;
    for (int i = 1; i < 19; i++) {
        p10[i] = 10 * p10[i - 1];
    }

    input();

    dijkstra();

    ans[0] = 1; // corner case with leading zero (when x = 0)
    for (int i = 1; i < min(m, L); i++) {
        if (dist[i % p_min] <= i) update_naive(i);
    }

    update_naive(m);

    if (m <= L) {
        output();
        return 0;
    }

    for (int d = 0; d < D; d++) {
        int res = f(0, 0, 0, 19, 0, d);
        ans[d] = max(ans[d], res);
    }

    output();

    return 0;
}
