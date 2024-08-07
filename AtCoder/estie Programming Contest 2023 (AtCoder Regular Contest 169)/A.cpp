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

const int MAXN = 252525;

int n;
ll a[MAXN];
int p[MAXN];
vector<int> t[MAXN];

int dep[MAXN];
vector<int> byDep[MAXN];

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 2; i <= n; i++) {
        cin >> p[i];
        t[p[i]].push_back(i);
    }
}

void dfs(int v) {
    byDep[dep[v]].push_back(v);
    for (auto& i : t[v]) {
        dep[i] = dep[v] + 1;
        dfs(i);
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

    dep[1] = 1;
    dfs(1);

    for (int d = n; d >= 1; d--) {
        ll sum = 0;
        for (auto& v : byDep[d]) sum += a[v];
        
        if (sum > 0) { cout << '+'; exit(0); }
        else if (sum < 0) { cout << '-'; exit(0); }
    }

    cout << 0;
}