// #pragma GCC optimize ("O3")
// #pragma GCC optimize ("Ofast")
// #pragma GCC optimize ("unroll-loops")
// #pragma GCC target ("avx2")

#include <bits/stdc++.h>
// #include <x86intrin.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 998244353;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int N, M;
struct Edge { int u, v; ll w; };
vector<Edge> e;

vector<int> vis(202020);
vector<int> lteq(202020), eq(202020);

ll ans = 1;

void input() {
    cin >> N >> M;
    e.resize(M);
    for (auto& i : e)
        cin >> i.u >> i.v >> i.w;
}

void solve() {
    sort(all(e), [&](const Edge& p1, const Edge& p2) {
        return p1.w < p2.w;
    });

    for (auto& [u, v, w] : e) {
        if (!vis[u] && !vis[v]) {
            lteq[u] = lteq[v] = w;
            vis[u] = vis[v] = 1;
        }
        else if (vis[v] && lteq[v] != w) { eq[u] = w; vis[u] = 1; }
        else if (!vis[v]) { eq[v] = w; vis[v] = 1; }
    }

    vector<int> ord(N);
    iota(all(ord), 1);
    sort(all(ord), [](int p1, int p2) {
        if (vis[p1] ^ vis[p2]) return vis[p1] > vis[p2];
        return max(lteq[p1], eq[p1]) < max(lteq[p2], eq[p2]);
    });

    set<int> st;
    ll cnt_fixed = 0;
    for (auto& v : ord) {
        if (lteq[v]) {
            if (st.count(lteq[v])) continue;
            st.insert(lteq[v]);

            ans *= 2 * (lteq[v] - cnt_fixed - 1);
            ans %= MOD;
            cnt_fixed += 2;
        }
        else if (eq[v]) cnt_fixed++;
        else break;
    }
    
    for (int i = 1; i <= N - cnt_fixed; i++) {
        ans = ans * i % MOD;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    solve();

    for (int v = 1; v <= N; v++)
        cout << v << ' ' << eq[v] << '\n';

    cout << ans;
}