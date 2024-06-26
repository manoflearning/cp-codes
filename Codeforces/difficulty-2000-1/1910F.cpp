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

int n, k;
vector<int> t[202020];
ll siz[202020];
vector<int> arr;
ll ans = 0;

void init() {
    for (int i = 1; i <= n; i++) {
        t[i].clear();
        siz[i] = 0;
    }
    arr.clear();
    ans = 0;
}

void input() {
    cin >> n >> k;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        t[u].push_back(v);
        t[v].push_back(u);
    }
}

void dfs(int v, int prv) {
    siz[v] = 1;
    for (auto& i : t[v]) {
        if (i == prv) continue;
        dfs(i, v);
        siz[v] += siz[i];
        ans += 2 * siz[i] * (n - siz[i]);
        arr.push_back(siz[i] * (n - siz[i]));
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        input();

        dfs(1, -1);

        sort(arr.rbegin(), arr.rend());

        for (int i = 0; i < k - 1; i++) {
            ans -= arr[i];
        }

        cout << ans << '\n';

        init();
    }
}