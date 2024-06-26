#include <bits/stdc++.h>
using namespace std;

int n, a[404040];
vector<int> g[404040];

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int cnt;
        cin >> a[i] >> cnt;
        while (cnt--) {
            int x; cin >> x;
            g[i].push_back(x);
        }
    }
}

int vi[404040], add = 0;
int ans = 0;

void dfs(int v) {
    vi[v] = 1;
    for (auto& i : g[v]) {
        if (!vi[i]) dfs(i);
    }
    ans = max(ans, add++ + a[v]);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    vector<int> arr;
    for (int i = 1; i <= n; i++) arr.push_back(i);
    sort(arr.begin(), arr.end(), [&](const int& p1, const int& p2) {
        return a[p1] > a[p2];
    });

    for (auto& v : arr) {
        if (!vi[v]) dfs(v);
    }

    cout << ans;
}