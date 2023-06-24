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
const ll INF = 1e18 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

const int MAX = 111;

int n, m;
struct wv { ll w; int v; };
vector<wv> adj[MAX];

void input() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
    }
}

int vi[MAX];
int isInf(int v) {
    if (v == n) return 0;
    int ret = 1;
    vi[v] = 1;
    for (auto& i : adj[v]) {
        if (!vi[i.v]) ret &= isInf(i.v);
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    // 1과 n이 같은 컴포넌트가 아니면 답은 "inf".
    if (isInf(1)) {
        cout << "inf";
        return 0;
    }
    memset(vi, 0, sizeof(vi));

    // solve
    ll total = 0;
    vector<pair<string, ll>> ans;

    vector<int> cur(1, 1);
    vi[1] = 1;

    while (1) {
        string s(n, '0');
        for (auto& i : cur) s[i - 1] = '1';

        ll res = INF;
        for (auto& v : cur) {
            for (auto& i : adj[v]) {
                if (vi[i.v]) continue;
                res = min(res, i.w);
            }
        }

        if (res == INF) break;

        if (res > 0) {
            total += res;
            ans.push_back({ s, res });
        }

        vector<int> ncur;
        for (auto& v : cur) {
            for (auto& i : adj[v]) {
                if (vi[i.v]) continue;
                i.w -= res;
                if (i.w == 0) ncur.push_back(i.v);
            }
        }

        for (auto& v : ncur) {
            cur.push_back(v);
            vi[v] = 1;
        }

        if (vi[n]) break;
    }

    cout << total << ' ' << sz(ans) << '\n';
    for (auto& i : ans) {
        cout << i.fr << ' ' << i.sc << '\n';
    }
}