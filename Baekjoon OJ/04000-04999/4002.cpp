#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second

int flag;
struct Seg {
    vector<pll> t;
    
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
    }
    void modify(int p, ll x) {
        for (t[p += flag - 1] = { x, p }; p > 1; p >>= 1)
            t[p >> 1] = max(t[p], t[p ^ 1]);
    }
    pll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return { 0, 0 };
        if (l <= nl && nr <= r) return t[n];

        int mid = (nl + nr) >> 1;
        return max(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
}seg;

int n, par[101010], r, in[101010], out[101010], cnt;
ll m, w[101010], l[101010];
vector<int> chd[101010], dep[101010];
pll dp[101010];

void input() {
    cin >> n >> m;
    for (int v = 1; v <= n; v++) {
        int p;
        cin >> p >> w[v] >> l[v];
        if (p == 0) r = v;
        else chd[p].push_back(v);
    }
}

void dfs(int v, int d) {
    in[v] = ++cnt;
    dep[d].push_back(v);

    for (auto& i : chd[v]) dfs(i, d + 1);
    
    out[v] = cnt;
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();

    dfs(r, 1);

    seg.build(n);
    for (int v = 1; v <= n; v++) {
        seg.modify(in[v], w[v]);
    }

    ll ans = 0;

    for (int d = n; d >= 1; d--) {
        for (int v : dep[d]) {
            auto& res = dp[v];
            res.fr += w[v], res.sc++;

            for (auto& i : chd[v]) {
                res.fr += dp[i].fr, res.sc += dp[i].sc;
            }
            
            while (res.fr > m) {
                pll mx = seg.query(in[v], out[v]);
                assert(0 < mx.fr);
                res.fr -= mx.fr, res.sc--;
                assert(1 <= mx.sc && mx.sc <= n);
                seg.modify(mx.sc, 0);
            }
            
            ans = max(ans, res.sc * l[v]);
        }
    }

    cout << ans;

	return 0;
}