#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

void dfs1(int now, int prv, const vector<vi> &t, vector<int> &dep, vector<int> &par) {
    par[now] = prv;
    for (const int nxt : t[now]) {
        if (nxt == prv) continue;
        dep[nxt] = dep[now] + 1;
        dfs1(nxt, now, t, dep, par);
    }
}

void dfs2(int now, int prv, const vector<vi> &t, const set<pii> &e, string &s) {
    for (const int nxt : t[now]) {
        if (nxt == prv) continue;

        if (e.count({now, nxt})) s[nxt] = s[now];
        else s[nxt] = (s[now] == '1' ? '0' : '1');
        dfs2(nxt, now, t, e, s);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    string op; cin >> op;

    if (op == "prepare") {
        int n; cin >> n;

        vector<vi> t(n);
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            t[u].push_back(v);
            t[v].push_back(u);
        }

        vector<int> dep(n), par(n);
        dfs1(0, -1, t, dep, par);

        vector<int> ord(n);
        iota(all(ord), 0);
        sort(all(ord), [&](int i, int j) {
            return dep[i] > dep[j];
        });

        vector<bool> used(n);
        set<pii> e;
        for (const int now : ord) {
            if (used[now]) continue;

            if (par[now] != -1 && !used[par[now]]) {
                e.insert({par[now], now});
                used[now] = used[par[now]] = 1;
            }
        }

        string s(n, '.');
        s[0] = '0';
        dfs2(0, -1, t, e, s);

        cout << s.substr(1, sz(s) - 1) << '\n';
    } else {
        int n;
        string s;
        cin >> n >> s;

        s = '0' + s;

        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;

            if (s[u] == s[v]) cout << "take\n";
            else cout << "ignore\n";
            cout.flush();
        }
    }
}
