#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int MAXN = 101010;

int W, a[MAXN], idx;
vector<int> t[MAXN];

int recursiveInput() {
    int v = ++idx;
    cin >> a[v];
    int cnt; cin >> cnt;
    t[v].resize(cnt);
    for (int i = 0; i < cnt; i++) {
        int u = recursiveInput();
        t[v].push_back(u);
    }
    return v;
}

ll dp[MAXN];
ll ans = 1;

void dfs(int v) {
    dp[v] += a[v];
    priority_queue<ll> pq;
    ll sum = 0;
    for (auto& i : t[v]) {
        dfs(i);
        sum += dp[i];
        pq.push(dp[i]);
    }
    while (!pq.empty() && sum > W) {
        ll x = pq.top();
        pq.pop();
        sum -= x;
        ans++;
    }
    dp[v] += sum;
    while (dp[v] > W) { dp[v] -= W; ans++; }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> W;
    recursiveInput();

    dfs(1);

    cout << ans;
}