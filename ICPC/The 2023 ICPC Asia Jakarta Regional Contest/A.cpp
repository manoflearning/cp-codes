#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

const int dy[] = { 1, 1, -1, -1, 0, 0, 1, -1 };
const int dx[] = { 1, -1, 1, -1, 1, -1, 0, 0 };

vector<string> a(3);
vector<vector<int>> vis(3, vector<int>(3));

string ans = "ZZZ";
string now;

string dfs(int i, int j) {
    if (sz(now) == 3) return now;

    string ret = "ZZZ";

    now.push_back(a[i][j]);
    vis[i][j] = 1;
    for (int d = 0; d < 8; d++) {
        int ni = i + dy[d], nj = j + dx[d];
        if (ni < 0 || 3 <= ni || nj < 0 || 3 <= nj) continue;
        if (vis[ni][nj]) continue;
        ret = min(ret, dfs(ni, nj));
    }
    now.pop_back();
    vis[i][j] = 0;

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    
    for (auto& i : a) cin >> i;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            ans = min(ans, dfs(i, j));
        }
    }

    cout << ans;
}