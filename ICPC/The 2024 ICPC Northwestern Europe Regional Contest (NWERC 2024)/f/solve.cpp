#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr ll INF = 4e18;

int fill_f(int l, ll x, const vector<int> &g, vector<int> &mov, const vector<ll> &c, vector<ll> &f) {
    auto &loc = mov[l];
    
    const ll both = min(x, c[loc] - f[loc]);
    x -= both, f[loc] += both;

    if (x == 0) return loc;
    else return loc = fill_f(g[loc], x, g, mov, c, f);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n, q;
    cin >> n >> q;

    vector<ll> c(n), f(n + 1);
    for (auto &i : c) cin >> i;
    c.push_back(INF);

    vector<int> mov(n + 1);
    iota(all(mov), 0);
    
    vector<int> g(n + 1, -1), stk;
    for (int i = 0; i <= n; i++) {
        while (!stk.empty() && c[stk.back()] < c[i]) {
            g[stk.back()] = i;
            stk.pop_back();
        }
        stk.push_back(i);
    }

    while (q--) {
        char op; cin >> op;
        if (op == '+') {
            int l; ll x;
            cin >> l >> x;
            l--;
            
            fill_f(l, x, g, mov, c, f);
        } else {
            int l; cin >> l;
            l--;

            cout << f[l] << '\n';
        }
    }
}
