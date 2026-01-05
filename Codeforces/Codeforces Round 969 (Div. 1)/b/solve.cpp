#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<ll>>;
#define fr first
#define sc second
#define pb push_back
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

struct dsu {
    vi p;
    void init(int n) { p.assign(n + 1, - 1); }
    int find(int x) { return p[x] < 0 ? x : p[x] = find(p[x]); }
    int size(int x) { return -p[find(x)]; }
    void join(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return;
        if (p[a] > p[b]) swap(a, b);
        p[a] += p[b];
        p[b] = a;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        ll n, w;
        cin >> n >> w;
        
        vi p(n + 1), mx(n + 1);
        for (int i = 2; i <= n; i++) {
            cin >> p[i];
        }

        iota(all(mx), 0);
        for (int i = n; i >= 2; i--) {
            mx[p[i]] = max(mx[p[i]], mx[i]);
        }

        dsu uf;
        uf.init(n);

        ll acc = 0, sum_y = 0;
        ll n_paths = n;
        for (int v = 2; v <= n; v++) {
            int x; ll y;
            cin >> x >> y;

            acc += 2 * y;
            sum_y += y;

            uf.join(p[x], x);
            {
                int p = mx[x], q = p % n + 1;
                n_paths -= (uf.find(p) == uf.find(q));
            }
            n_paths -= (uf.find(x - 1) == uf.find(x));

            ll res = 0;
            res += acc;
            res += n_paths * (w - sum_y);

            cout << res << ' ';
        }
        cout << '\n';
    }
}
