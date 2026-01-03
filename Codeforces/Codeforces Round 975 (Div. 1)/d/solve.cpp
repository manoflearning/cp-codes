#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

vector<ll> po, pe;

// what: maintain dynamic connectivity with union-find and size queries.
// time: init O(n), join/find amortized a(n); memory: O(n)
// constraint: 1-indexed [1, n].
// usage: dsu d; d.init(n); d.join(a, b); int r = d.find(x); int s = d.size(x);
struct dsu {
    vector<int> p, mn, mx;
    int cnt_q;

    void init(int n) { // goal: reset to n singletons.
        p.assign(n + 1, -1);
        
        mn.resize(n + 1);
        iota(all(mn), 0);
        mx.resize(n + 1);
        iota(all(mx), 0);

        cnt_q = po[n] + pe[n];
    }
    int find(int x) { return p[x] < 0 ? x : p[x] = find(p[x]); } // result: root of x.
    int size(int x) { return -p[find(x)]; }
    void add(int l, int r) {
        ll cnto = po[r] - po[l - 1], cnte = pe[r] - pe[l - 1];
        if (cnto + cnte) {
            int len = r - l + 1;
            if (len & 1) {
                if (l & 1) cnt_q += (cnto >= 1);
                else cnt_q += (cnte >= 1);
            } else cnt_q++;
        }
    }
    void del(int l, int r) {
        ll cnto = po[r] - po[l - 1], cnte = pe[r] - pe[l - 1];
        if (cnto + cnte) {
            int len = r - l + 1;
            if (len & 1) {
                if (l & 1) cnt_q -= (cnto >= 1);
                else cnt_q -= (cnte >= 1);
            } else cnt_q--;
        }
    }
    void join(int a, int b) {
        // goal: merge the two components.
        a = find(a), b = find(b);
        if (a == b) return;
        if (p[a] > p[b]) swap(a, b); // a has larger size (more negative)
        
        del(mn[a], mx[a]);
        del(mn[b], mx[b]);

        p[a] += p[b];
        mn[a] = min(mn[a], mn[b]);
        mx[a] = max(mx[a], mx[b]);
        p[b] = a;

        add(mn[a], mx[a]);
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<ll> a(n + 1);
        for (int i = 1; i <= n; i++) cin >> a[i];

        vector<ll> cc;
        map<ll, vector<int>> ra;
        for (int i = 1; i <= n; i++) {
            cc.push_back(a[i]);
            ra[a[i]].push_back(i);
        }
        sort(all(cc));
        cc.erase(unique(all(cc)), cc.end());

        sort(rall(cc));

        ll ans = 0;

        ll q = cc[0];
        po.resize(n + 1), pe.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            po[i] = (a[i] == q && (i & 1)) + po[i - 1];
            pe[i] = (a[i] == q && !(i & 1)) + pe[i - 1];
        }

        ll acc = 0;
        dsu uf;
        uf.init(n);
        for (ll p : cc) {
            for (auto &i : ra[p]) {
                acc += (uf.size(i) + 1) / 2;
                
                if (1 < i && p <= a[i - 1]) {
                    acc -= (uf.size(i - 1) + 1) / 2;
                    acc -= (uf.size(i) + 1) / 2;
                    uf.join(i - 1, i);
                    acc += (uf.size(i) + 1) / 2;
                }
                if (i < n && p < a[i + 1]) {
                    acc -= (uf.size(i) + 1) / 2;
                    acc -= (uf.size(i + 1) + 1) / 2;
                    uf.join(i, i + 1);
                    acc += (uf.size(i) + 1) / 2;
                }
            }

            ll res = p + q + acc + (uf.cnt_q ? 0 : -1);
            if (ans < res) {
                ans = res;
                // cout << p << ' ' << q << ' ' << acc << '\n';
            }
        }

        cout << ans << '\n';
    }
}
