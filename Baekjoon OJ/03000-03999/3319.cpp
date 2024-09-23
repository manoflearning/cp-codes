#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

typedef pair<ll, ll> Line;
const Line e = { 0, 1e18 };
struct LiChaoTree {
    ll f(Line l, ll x) { return l.first * x + l.second; }
    struct Node {
        ll xl, xr; int l, r;
        Line line;
    };
    vector<Node> t;
    vector<vector<tuple<int, Node>>> stk;
    void build(ll xlb, ll xub) {
        t.push_back({ xlb, xub, -1, -1, e });
    }
    void roll_back() {
        assert(!stk.empty());

        for (auto& i : stk.back()) {
            t[get<0>(i)] = get<1>(i);
        }
        stk.pop_back();
    }
    void insert(Line newLine, int n = 0) {
        if (n == 0) stk.push_back(vector<tuple<int, Node>>(0));

        ll xl = t[n].xl, xr = t[n].xr;
        ll xmid = (xl + xr) >> 1;

        Line llow = t[n].line, lhigh = newLine;
        if (f(llow, xl) >= f(lhigh, xl)) swap(llow, lhigh);

        Node tmp = t[n];
        if (f(llow, xr) <= f(lhigh, xr)) {
            t[n].line = llow;
            stk.back().push_back({ n, tmp });
            return;
        }
        else if (f(llow, xmid) < f(lhigh, xmid)) {
            t[n].line = llow;
            if (t[n].r == -1) {
                t[n].r = sz(t);
                t.push_back({ xmid + 1, xr, -1, -1, e });
            }
            stk.back().push_back({ n, tmp });
            insert(lhigh, t[n].r);
        }
        else if (f(llow, xmid) >= f(lhigh, xmid)) {
            t[n].line = lhigh;
            if (t[n].l == -1) {
                t[n].l = sz(t);
                t.push_back({ xl, xmid, -1, -1, e });
            }
            stk.back().push_back({ n, tmp });
            insert(llow, t[n].l);
        }
    }
    ll query(ll x, int n = 0) {
        if (n == -1) return e.second;
        ll xl = t[n].xl, xr = t[n].xr;
        ll xmid = (xl + xr) >> 1;

        ll ret = f(t[n].line, x);
        if (x <= xmid) ret = min(ret, query(x, t[n].l));
        else ret = min(ret, query(x, t[n].r));
        return ret;
    }
}lct;

const int MAXN = 101010;

int n;
struct Edge { ll w; int v; };
vector<vector<Edge>> adj(MAXN);

vector<ll> a(MAXN), b(MAXN);
vector<ll> dp(MAXN);
vector<ll> psum(MAXN);

void input() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v; ll w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
    }
    for (int i = 2; i <= n; i++) cin >> b[i] >> a[i];
}

void dfs(int v, int prv) {
    if (v != 1) {
        dp[v] += lct.query(a[v]);
        dp[v] += psum[v] * a[v];
        dp[v] += b[v];
    }

    lct.insert({ -psum[v], dp[v] });

    for (auto& i : adj[v]) {
        if (i.v == prv) continue;
        psum[i.v] = i.w + psum[v];
        dfs(i.v, v);
    }

    lct.roll_back();
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    lct.build(0, (ll)1e9);

    dfs(1, 0);

    for (int i = 2; i <= n; i++)
        cout << dp[i] << ' ';
}
