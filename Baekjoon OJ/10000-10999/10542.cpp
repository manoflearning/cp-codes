#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define pii pair<int, int>
#define fr first
#define sc second

int N;
vector<int> g[505050];
int gin[505050];
vector<int> rg[505050];
int isCycle[505050];

void input() {
    cin >> N;
    for (int v = 1; v <= N; v++) {
        int u; cin >> u;
        g[v].push_back(u);
        gin[u]++;
        rg[u].push_back(v);
    }
}

void findCycle() {
    for (int i = 1; i <= N; i++) isCycle[i] = 1;
    queue<int> q;
    for (int v = 1; v <= N; v++) 
        if (!gin[v]) q.push(v);
    while (sz(q)) {
        int v = q.front();
        q.pop();
        isCycle[v] = 0;
        for (auto& i : g[v]) {
            gin[i]--;
            if (!gin[i]) q.push(i);
        }
    }
}

int ans = 0;
int vi[505050], dp[505050][2];
vector<pii> arr;

int dfs2(int v, int pb) {
    int& ret = dp[v][pb];
    if (ret != -1) return ret;

    ret = 0;

    int res0 = 0, res1 = 1;
    for (auto& i : rg[v])
        res0 += dfs2(i, 0);
    for (auto& i : rg[v])
        res1 += dfs2(i, 1);
    
    if (pb & 1) return ret = res0;
    else return ret = max(res0, res1);
}

void dfs(int v) {
    vi[v] = 1;
    int cnt0 = 1, cnt1 = 0;
    for (auto& i : rg[v]) {
        if (!isCycle[i]) {
            cnt0 += dfs2(i, 1);
            cnt1 += dfs2(i, 0);
        }
    }
    arr.push_back({ cnt0, cnt1 });
    for (auto& i : rg[v]) {
        if (isCycle[i] && !vi[i]) dfs(i);
    }
}

int cal2() {
    vector<vector<int>> dp(sz(arr), vector<int>(2));
    dp[0][1] = arr[0].sc;
    dp[1][0] = arr[1].fr + dp[0][1];
    dp[1][1] = arr[1].sc + dp[0][1];
    for (int i = 2; i < sz(arr); i++) {
        dp[i][0] = arr[i].fr + dp[i - 1][1];
        dp[i][1] = arr[i].sc + max(dp[i - 1][0], dp[i - 1][1]);
    }

    return max(dp[sz(arr) - 1][0], dp[sz(arr) - 1][1]);
}

void cal() {
    int res = cal2();
    reverse(arr.begin(), arr.end());
    res = max(res, cal2());
    ans += res;
}

void solve() {
    for (int i = 0; i < 505050; i++)
        dp[i][0] = dp[i][1] = -1;

    for (int v = 1; v <= N; v++) {
        if (isCycle[v] && !vi[v]) {
            arr.clear();
            dfs(v);
            cal();
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

    findCycle();

    /*for (int v = 1; v <= N; v++)
        if (isCycle[v]) cout << v << ' ';
    cout << '\n';*/

    solve();

    cout << ans;
}