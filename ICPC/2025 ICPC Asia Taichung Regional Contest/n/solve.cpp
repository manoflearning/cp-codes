#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;

#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int N = 101010;

int n, k, b;

int cnt_edge = 0;
int cnt_odd = 0, deg[N];
set<pii> ans;

void init() {
    cnt_edge = cnt_odd = 0;
    for (int i = 1; i <= n; i++)
        deg[i] = 0;
    ans.clear();
}

void add_edge(int u, int v) {
    if (u > v) swap(u, v);
    // cout << "DEBUG: " << u << ' ' << v << endl;
    assert(u != v);
    assert(!ans.count({u, v}));

    cnt_edge++;
    deg[u]++, deg[v]++;
    if (deg[u] & 1) cnt_odd++;
    else cnt_odd--;
    if (deg[v] & 1) cnt_odd++;
    else cnt_odd--;
    ans.insert({u, v});
}
bool is_valid(int u, int v) {
    if (u > v) swap(u, v);
    return !ans.count({u, v}) && (1 <= u && v <= n) && (u != v);
}

void yes() { cout << "Yes\n"; }
void no() { cout << "No\n"; }

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        cin >> n >> k >> b;

        if (n == 1) {
            if (k == 0 && b == 0) {
                yes();
                cout << 0 << '\n';
            } else no();
            continue;
        }
        if (n == 2) {
            if (k == 2 && b == 1) {
                yes();
                cout << 1 << '\n';
                cout << 1 << ' ' << 2 << '\n';
            } else no();
            continue;
        }
        if (n == 3 && b == 0) {
            if (k == 0) {
                yes();
                cout << 3 << '\n';
                cout << "1 2\n2 3\n3 1\n";
            } else no();
            continue;
        }

        if (k & 1) {
            no();
            continue;
        }

        if (b > 0 && k == 0) {
            no();
            continue;
        }

        if (b == n - 2) {
            no();
            continue;
        }

        if (1 != n - b) {
            for (int i = 1; i <= n - b; i++) {
                add_edge(i, (i < n - b ? i + 1 : 1));
            }
        }
        
        int u = 1;
        for (int i = n - b + 1; i <= n; i++) {
            if (cnt_odd < k) {
                add_edge(min(n - b, u), i);
                u += 2;
                if (n - b < u) u = 2;
            } else {
                add_edge(i - 1, i);
            }
        }

        vector<int> es;
        for (int i = 1; i <= n - b; i++) {
            if (!(deg[i] & 1))
                es.push_back(i);
        }
        
        for (int i = 0; i < sz(es) / 2; i++) {
            if (cnt_odd == k) break;
            if (is_valid(es[i], es[i + (sz(es) + 1) / 2]))
                add_edge(es[i], es[i + (sz(es) + 1) / 2]);
        }

        if (cnt_odd != k) {
            no();
            continue;
        }

        yes();
        cout << cnt_edge << '\n';
        for (auto &[u, v] : ans) {
            cout << u << ' ' << v << '\n';
        }
        assert(cnt_odd == k);
    }
}

// 1. if (k % 2 == 0)

// 1.1. if (b == 0) => Yes (simple cycle + {{1, n/2+1}, {2, n/2+2}, ..., {n/2, n}})

// 1.2. if (b == n - 1)
// 1.2.1. if (2 <= k <= n) => Yes (고슴도치 + 일자형)
// 1.2.2. otherwise => No

// 1.3. if (1 <= b <= n - 2)
// 1.3.1. if (2 <= k <= n) => Yes?
// 1.3.2. otherwise => No

// 2. if (k % 2 == 1) => No