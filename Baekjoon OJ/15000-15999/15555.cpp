#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n, m;
vector<string> a;
vector<vector<int>> adj;
int numr[3030][3030], numc[3030][3030], cnt;

void addEdge(int v, int u) {
    adj[v].push_back(u);
    adj[u].push_back(v);
}

vector<int> vi;
int all, now;
void dfs(int v, int bit) {
    vi[v] = 1;
    all++, now += bit;
    for (auto& i : adj[v]) {
        if (!vi[i]) dfs(i, !bit);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    a.resize(n);
    for (auto& i : a) cin >> i;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i + 2 < n && a[i][j] == 'R' && a[i + 1][j] == 'G' && a[i + 2][j] == 'W') numc[i][j] = ++cnt;
            if (j + 2 < m && a[i][j] == 'R' && a[i][j + 1] == 'G' && a[i][j + 2] == 'W') numr[i][j] = ++cnt;
        }
    }

    adj.resize(cnt + 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (numr[i][j]) {
                if (numc[i][j]) 
                    addEdge(numr[i][j], numc[i][j]);
                if (0 <= i - 1 && j + 1 < m && numc[i - 1][j + 1])
                    addEdge(numr[i][j], numc[i - 1][j + 1]);
                if (0 <= i - 2 && j + 2 < m && numc[i - 2][j + 2])
                    addEdge(numr[i][j], numc[i - 2][j + 2]);
            }
        }
    }

    vi.resize(cnt + 1);
    int ans = 0;
    for (int v = 1; v <= cnt; v++) {
        if (!vi[v]) {
            all = now = 0;
            dfs(v, 1);
            ans += max(now, all - now);
        }
    }

    cout << ans;
}