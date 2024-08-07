//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
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
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

struct Edge {
    ll w; int v;
};

int n;
vector<Edge> adj[101010];

void input() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
    }
}

int st = -1, en = -1, banned = -1;
int vi[101010];
pll dfs(int v, ll d) {
    vi[v] = 1;
    pll ret = { d, v };
    for (auto& i : adj[v]) {
        if (!vi[i.v] && banned != i.v) {
            ret = max(ret, dfs(i.v, i.w + d));
        }
    }
    return ret;
}

ll getAns() {
    ll ret = 0;

    banned = st;
    memset(vi, 0, sizeof(vi));
    int v = dfs((banned == 1 ? 2 : 1), 0).sc;
    memset(vi, 0, sizeof(vi));
    ret = max(ret, dfs(v, 0).fr);

    banned = en;
    memset(vi, 0, sizeof(vi));
    v = dfs((banned == 1 ? 2 : 1), 0).sc;
    memset(vi, 0, sizeof(vi));
    ret = max(ret, dfs(v, 0).fr);

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    st = dfs(1, 0).sc;
    memset(vi, 0, sizeof(vi));
    en = dfs(st, 0).sc;

    cout << getAns();
}