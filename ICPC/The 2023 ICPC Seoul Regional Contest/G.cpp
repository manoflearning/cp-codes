#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int MAXN = 505050;
const int MAXK = 111;

int n, k, m, f;
int a[MAXK][MAXN];
map<string, vector<int>> mp;

void input() {
    cin >> n >> k >> m >> f;
    for (int i = 1; i <= k; i++) {
        for (int j = 0; j < m; j++) {
            int x; cin >> x;
            a[i][x] = 1;
        }
    }
}

void solve() {
    for (int x = 1; x <= n; x++) {
        string s;
        for (int i = 1; i <= k; i++) {
            if (a[i][x]) s.push_back('Y');
            else s.push_back('N');
        }
        mp[s].push_back(x);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    solve();

    while (f--) {
        string s; cin >> s;
        if (sz(mp[s]) == 1) cout << mp[s][0] << '\n';
        else cout << 0 << '\n';
    }
}
