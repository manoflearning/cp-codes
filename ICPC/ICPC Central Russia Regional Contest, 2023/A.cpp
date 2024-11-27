#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int dy[] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
const int dx[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

int n, m;
vector<string> a;
int cnt;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    a.resize(n);
    for (auto &i : a) cin >> i;

    for (auto &i : a) for (auto &j : i) if (j == '#') cnt++;

    for (int y = 0; y < n; y++) {
        for (int x = 0; x < m; x++) {
            int res = 0, tot = 0;
            for (int d = 0; d < 9; d++) {
                int ny = y + dy[d], nx = x + dx[d];
                if (ny < 0 || n <= ny || nx < 0 || m <= nx) continue;
                tot++;
                if (a[ny][nx] == '#') res++;
            }
            if (res == tot && res == cnt) {
                cout << "Possible\n";
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < m; j++) {
                        if (i == y && j == x) cout << '#';
                        else cout << '.';
                    }
                    cout << '\n';
                }
                exit(0);
            }
        }
    }
    
    cout << "Impossible";
}
