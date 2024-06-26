// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

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


int n, m;
struct Edge { ll w; int v; };
vector<Edge> adj[2020];

void input() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int l, r; string s;
        int w;
        cin >> l >> r >> s >> w;
        if (s == "<=") adj[l - 1].push_back({ w, r });
        if (s == ">=") adj[r].push_back({ -w, l - 1 });
    }
}

vector<ll> upper(2020, 1e18);

int bellmanFord() {
    upper[1] = 0;
    int update = 0;
    for (int i = 0; i < n + 2; i++) {
        update = 0;
        for (int v = 0; v <= n; v++) {
            for (auto& i : adj[v]) {
                if (upper[i.v] > i.w + upper[v]) {
                    upper[i.v] = i.w + upper[v];
                    update = 1;
                }
            }
        }
        if (!update) break;
    }
    return !update;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    if (bellmanFord()) cout << "YES";
    else cout << "NO";
}