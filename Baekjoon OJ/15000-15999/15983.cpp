#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

const ll INF = 1e18;
const int MAXN = 121;
const int MAXX = 1010101;

int n, en;
vector<int> a[MAXN];
vector<pll> b[MAXX];
struct Node {
    ll x, mod; int v;
};
vector<Node> adj[MAXN];

void input() {
    cin >> n >> en;
    for (int i = 1; i <= n; i++) {
        int cnt; cin >> cnt;
        while (cnt--) {
            int x; cin >> x;
            b[x].push_back({ i, sz(a[i]) });
            a[i].push_back(x);
        }
    }
}

ll gcd(ll x, ll y) {
    if (!y) return x;
    return gcd(y, x % y);
}
ll minv(ll x, ll y) {
    if (x == 0 && y == 1) return 0;
    if (x == 1) return 1;
    return y - minv(y % x, x) * y / x;
}

pll crt(pll U, pll V) {
    if (U.sc == -1 || V.sc == -1) return { -1, -1 };
    if (U.sc == 1) return V;
    if (V.sc == 1) return U;
    ll g = gcd(U.sc, V.sc), l = U.sc * V.sc / g;
    if ((V.fr - U.fr) % g) return { -1, -1 };

    ll u = U.sc / g, v = V.sc / g;
    ll mul = (V.fr - U.fr) / g;
    mul = mul * minv(u % v, v) % v;

    pll ret = { mul * U.sc + U.fr, l };
    ret.fr %= ret.sc, ret.fr = (ret.fr + ret.sc) % ret.sc;
    return ret;
}

void graphModeling() {
    for (int i = 0; i < MAXX; i++) {
        if (sz(b[i]) != 2) continue;

        int u = b[i][0].fr, ut = b[i][0].sc;
        int v = b[i][1].fr, vt = b[i][1].sc;
        pll res = crt({ ut, sz(a[u]) }, { vt, sz(a[v]) });
        if (res.fr != -1) {
            adj[u].push_back({ res.fr, res.sc, v });
            adj[v].push_back({ res.fr, res.sc, u });
        }
    }
}

vector<ll> dist(MAXN, INF);
void dijkstra() {
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    dist[1] = 0;
    pq.push({ dist[1], 1 });

    while (sz(pq)) {
        ll w = pq.top().fr;
        int v = pq.top().sc;
        pq.pop();
        for (auto& i : adj[v]) {
            ll nw = -1;
            if (w % i.mod <= i.x) nw = w / i.mod * i.mod + i.x;
            else nw = (w + i.mod - 1) / i.mod * i.mod + i.x;
            if (nw < dist[i.v]) {
                dist[i.v] = nw;
                pq.push({ dist[i.v], i.v });
            }
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    if (b[en].empty()) {
        cout << -1;
        return 0;
    }

    graphModeling();

    dijkstra();

    ll ans = dist[b[en][0].fr];
    if (ans == INF) {
        cout << -1; return 0;
    }

    ll mod = sz(a[b[en][0].fr]), x = b[en][0].sc;
    if (ans % mod <= x) ans = ans / mod * mod + x;
    else ans = (ans + mod - 1) / mod * mod + x;
    cout << ans;
}