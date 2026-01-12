#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int get_beauty(int n, int m, const vector<vector<int>> &arr) {
    vector<bool> mexs(m + 2);
    for (int x = 0; x < m; x++) {
        int mex = 0;
        vector<bool> vis(m + 1);
        for (int y = 0; y < n; y++) {
            if (arr[y][x] != -1) vis[arr[y][x]] = 1;
            while (vis[mex]) mex++;
        }
        mexs[mex] = 1;   
    }
    int beauty = 0;
    while (mexs[beauty]) beauty++;
    return beauty;
}

void fill_(int n, int m, vector<vector<int>> &arr) {
    for (int i = 0; i < n; i++) {
        int now = max(1, arr[i][m - 1] + 1) % m;

        for (int j = 0; j < m; j++) {
            if (arr[i][j] != -1) break;
            arr[i][j] = now;
            now = (now + 1) % m;
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n, m;
        cin >> n >> m;

        vector<vector<int>> ans(n, vector<int>(m, - 1));
        for (int i = 0; i < n; i++) {
            for (int j = 0; i + j + 1 < m; j++) {
                ans[i][i + j + 1] = j;
            }
        }

        fill_(n, m, ans);
            
        cout << get_beauty(n, m, ans) << '\n';
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << ans[i][j] << ' ';
            }
            cout << '\n';
        }
    }
}
