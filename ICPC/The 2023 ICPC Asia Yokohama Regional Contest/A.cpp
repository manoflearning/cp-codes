#include <bits/stdc++.h>
using namespace std;

const string S = "YOKOHAMA";

const int dy[] = { 1, -1, 0, 0 };
const int dx[] = { 0, 0, 1, -1 };

int n, m;
vector<string> a;
int ans = 0;

void dfs(int y, int x, int len) {
    if (len == 8) { ans++; return; }

    for (int d = 0; d < 4; d++) {
        int ny = y + dy[d], nx = x + dx[d];
        if (ny < 0 || n <= ny || nx < 0 || m <= nx) continue;
        if (a[ny][nx] == S[len]) dfs(ny, nx, len + 1);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    a.resize(n);
    for (auto& i : a) cin >> i;

    for (int y = 0; y < n; y++) {
        for (int x = 0; x < m; x++) {
            if (a[y][x] == S[0]) dfs(y, x, 1);
        }
    }

    cout << ans;
}