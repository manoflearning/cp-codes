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
int a[101010], b[101010], c[101010];
vector<int> isInC, isInC2;
ll ans = 0;

void init() {
    isInC.clear();
    isInC2.clear();
    ans = 0;
}

void input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    for (int i = 1; i <= m; i++) cin >> c[i];
    isInC.resize(n + 1);
    isInC2.resize(n + 1);
    for (int i = 2; i <= m; i++) {
        isInC[c[i]] = 1;
        if (a[c[i - 1]] < a[c[i]]) isInC2[c[i]] = 1;
    }
}

void solve() {
    vector<int> arr;
    for (int i = 1; i <= n; i++) {
        arr.push_back(i);
        ans += b[i];
    }

    sort(all(arr), [&](int p1, int p2) {
        return a[p1] ^ a[p2] ? a[p1] > a[p2] : b[p1] < b[p2];
    });

    priority_queue<ll, vector<ll>, greater<ll>> pq;
    
    int isMaxSkipped = 0;

    for (int i = 0; i < sz(arr); i++) {
        int v = arr[i];
        if (isInC2[v]) {
            if (!pq.empty() && pq.top() <= b[v]) { ans -= pq.top(); pq.pop(); pq.push(b[v]); }
            else ans -= b[v];
            if (a[v] == a[arr[0]]) isMaxSkipped = 1;
        }
        else if (!isInC[v]) pq.push(b[v]);
    }
    if (!isMaxSkipped) ans -= b[arr[0]];
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        init();

        input();

        solve();

        cout << ans << '\n';
    }
}