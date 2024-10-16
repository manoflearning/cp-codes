#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const ll INF = 1e18;

struct wv { ll w; int v; };

int n, m;
vector<wv> adj[101010];

void input() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; ll w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
    }
}

// op * x + co
struct opc { int op; ll co; };
vector<opc> arr[101010];

int vi[101010];
void dfs(int v, int op, ll co) {
    vi[v] = 1;
    arr[v].push_back({ op, co });

    for (auto& i : adj[v]) {
        if (vi[i.v]) {
            arr[i.v].push_back({ -1 * op, i.w - co });
        }
        else {
            dfs(i.v, -1 * op, i.w - co);
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    dfs(1, 1, 0);

    ll x = INF;

    int imp = 0;
    for (int v = 1; v <= n; v++) {
        if (sz(arr[v]) == 1) continue;

        ll pco = INF, nco = INF;
        for (auto& i : arr[v]) {
            if (i.op == 1) {
                if (pco == INF) pco = i.co;
                else if (pco != i.co) imp = 1;
            }
            else {
                if (nco == INF) nco = i.co;
                else if (nco != i.co) imp = 1;
            }
        }

        if (pco != INF && nco != INF) {
            // x + pco = -x + nco
            // 2x = nco - pco
            if ((nco - pco) % 2 == 0) {
                if (x == INF) x = (nco - pco) / 2;
                else if (x != (nco - pco) / 2) imp = 1;
            }
            else imp = 1;
        }
        else if (pco != INF) {
            arr[v].clear();
            arr[v].push_back({ 1, pco });
        }
        else if (nco != INF) {
            arr[v].clear();
            arr[v].push_back({ -1, nco });
        }
    }

    if (imp) {
        cout << "No\n";
        return 0;
    }

    cout << "Yes\n";

    if (x != INF) {
        for (int v = 1; v <= n; v++) {
            cout << arr[v][0].op * x + arr[v][0].co << ' ';
        }
    }
    else {
        // given a n linear function x + c_i,
        // find a minimum sum of |x + c_1| + |x + c_2| + ... + |x + c_n|.

        vector<ll> b(1, -INF), ps(n + 2), rps(n + 2);
        for (int v = 1; v <= n; v++) {
            b.push_back(arr[v][0].op * arr[v][0].co);
        }

        sort(b.begin(), b.end());

        for (int v = 1; v <= n; v++)
            ps[v] = -b[v] + ps[v - 1];
        for (int v = n; v >= 1; v--)
            rps[v] = b[v] + rps[v + 1];

        ll ans = INF, mnx = 0;
        for (int v = 1; v <= n; v++) {
            x = -b[v];
            ll res = ps[v - 1] + rps[v + 1];
            res += x * (n - v) + -x * (v - 1);
            if (res < ans) {
                ans = res, mnx = x;
            }
        }
        
        for (int v = 1; v <= n; v++) {
            //cout << arr[v][0].op << ' ' << arr[v][0].co << '\n';
            cout << arr[v][0].op * mnx + arr[v][0].co << ' ';
        }
    }
}