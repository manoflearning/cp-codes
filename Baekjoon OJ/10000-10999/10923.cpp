#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second

int n, a[505], m;
pii b[30 * 505];
vector<vector<int>> need;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    cin >> m;
    for (int i = 0; i < m; i++)
        cin >> b[i].fr >> b[i].sc;
    
    need.resize(m + 1, vector<int>(n));
    for (int i = 0; i < n; i++) need[m][i] = i;
    for (int i = m - 1; i >= 0; i--) {
        need[i] = need[i + 1];
        auto [u, v] = b[i];
        swap(need[i][u], need[i][v]);
    }

    /*for (int i = 0; i <= m; i++) {
        for (auto& v : need[i]) cout << v << ' ';
        cout << "\n\n";
    }*/

    cout << m << '\n';
    for (int i = 1; i <= m; i++) {
        auto [u, v] = b[i - 1];
        swap(a[u], a[v]);
        auto& arr = need[i];
        
        vector<int> needIdx(n);
        for (int j = 0; j < n; j++) needIdx[arr[j]] = j;
        
        vector<int> adj(n, -1);
        for (int j = 0; j < n; j++) {
            if (arr[j] != a[j]) 
                adj[j] = needIdx[a[j]];
        }

        pii res = { 0, 0 }; int mx = 0;
        for (int v = 0; v < n; v++) {
            if (adj[v] == -1) continue;
            if (adj[adj[v]] == -1) continue;

            int cnt = 1 + (adj[adj[v]] == i);
            if (mx < cnt) {
                mx = cnt;
                res = { v, adj[v] };
            }
        }

        cout << res.fr << ' ' << res.sc << '\n';
        swap(a[res.fr], a[res.sc]);
    }
}