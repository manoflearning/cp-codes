// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const int MAXN = 101010;

int n;
vector<int> par;
vector<vector<int>> t;
vector<ll> w, sum, siz;
int q;
vector<int> qu;

void init() {
    par.clear();
    t.clear();
    w.clear();
    sum.clear();
    siz.clear();
    qu.clear();
}

void input() {
    cin >> n;
    par.resize(n + 1);
    t.resize(n + 1);
    w.resize(n + 1);
    sum.resize(n + 1);
    siz.resize(n + 1);
    for (int v = 2; v <= n; v++) {
        cin >> par[v];
        t[par[v]].push_back(v);
    }
    for (int v = 1; v <= n; v++) cin >> w[v];
    cin >> q;
    qu.resize(q);
    for (auto& i : qu) cin >> i;
}

void dfs(int v) {
    sum[v] = w[v];
    siz[v] = 1;
    for (auto& i : t[v]) {
        dfs(i);
        sum[v] += sum[i];
        siz[v] += siz[i];
    }
}

struct State {
    int v;
    bool operator<(const State& rhs) const {
        return sum[v] * siz[rhs.v] > sum[rhs.v] * siz[v];
    }
};

void solve() {
    for (auto st : qu) {
        ll res = 0;

        int time = siz[st];
        priority_queue<State> pq;
        pq.push({ st });
        while (!pq.empty()) {
            int v = pq.top().v;
            pq.pop();

            res += w[v] * time--;

            for (auto& i : t[v]) pq.push({ i });
        }

        cout << res << ' ';
    }
    cout << '\n';
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << '\n';

        init();

        input();

        dfs(1);

        solve();

        cout << flush;
    }
}