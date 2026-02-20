#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; cin >> n;

    vi ind(n);
    vector<vi> g(n);
    for (int i = 0; i < n; i++) {
        int cnt; cin >> cnt;
        while (cnt--) {
            int x; cin >> x; x--;
            g[i].push_back(x);
            ind[x]++;
        }
    }

    queue<int> qu;
    for (int i = 0; i < n; i++) {
        if (!ind[i]) qu.push(i);
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

    bool yes = 1;
    yes &= sz(ord) == n;
    for (int i = 0; i + 1 < n; i++) {
        bool res = 0;
        const int now = ord[i], nxt = ord[i + 1];
        for (const int j : g[now]) res |= j == nxt;
        yes &= res;
    }

    cout << (yes ? 1 : 0) << '\n';
}
