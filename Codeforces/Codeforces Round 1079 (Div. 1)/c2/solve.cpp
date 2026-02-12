#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

vector<int> query(int k) {
    cout << "? " << k << '\n';
    cout.flush();

    int q; cin >> q;
    vector<int> ret(q);
    for (auto &i : ret) cin >> i;
    return ret;
}

void answer(const set<pii> &e) {
    cout << "! " << sz(e) << '\n';
    for (const auto [u, v] : e) {
        cout << u << ' ' << v << '\n';
    }
    cout.flush();
}

void update(
    const int n, 
    const vector<int> &path, 
    set<pii> &e, 
    vector<int> &cnt_path, 
    vector<unordered_set<int>> &g
) {
    for (int i = 0; i + 1 < sz(path); i++) {
        const int u = path[i];
        const int v = path[i + 1];

        if (e.count({u, v})) continue;

        e.insert({u, v});
        g[u].insert(v);
    }

    queue<int> qu;
    vector<int> ind(n + 1);
    for (int v = 1; v <= n; v++) {
        for (auto &i : g[v]) ind[i]++;
    }
    for (int v = 1; v <= n; v++) {
        if (!ind[v]) qu.push(v);
    }

    vector<int> ord;
    while (!qu.empty()) {
        const int now = qu.front();
        qu.pop();
        
        ord.push_back(now);

        for (const int nxt : g[now]) {
            ind[nxt]--;
            if (!ind[nxt]) qu.push(nxt);
        }
    }

    reverse(all(ord));
    for (const int now : ord) {
        cnt_path[now] = 1;
        for (const int nxt : g[now]) {
            cnt_path[now] += cnt_path[nxt];
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        set<pii> e;
        vector<int> cnt_path(n + 1);
        vector<unordered_set<int>> g(n + 1);

        // vector<int> prv(1, 1);

        int k = 2;
        while (1) {
            const auto now = query(k);
            if (now.empty()) break;

            update(n, now, e, cnt_path, g);

            // if (sz(prv) < sz(now) && prv == vector<int>{now.begin(), now.begin() + sz(prv)}) {
            //     k++;
            // } else {
                k += cnt_path[now.back()];
            // }

            // prv = now;
        }

        answer(e);
    }

    return 0;
}
