#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

const ll INF = 1e18;

int n, m;
int a[1010][1010];

ll solve(int sty, int stx) {
    bool ex1 = 0;
    for (int y = sty; y <= n; y++) {
        for (int x = (y % 2 == sty % 2 ? 1 : 2); x <= m; x += 2) {
            if (a[y][x] == 1) {
                ex1 = 1;
                dfs
            }
        }
    }
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }

    if (n == 1 && m == 1) {
        cout << a[1][1];
        return 0;
    }

    if (n == 1) {
        vector<int> tmp(m + 1);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                tmp[j] = a[i][j];
                cin >> a[i][j];
            }
        }
        swap(n, m);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                a[i][j] = tmp[i];
            }
        }
    }

    ll ans1 = solve(1, 1);
    ll ans2 = solve(2, 1);

    ll ans = ans1 + ans2;
    cout << (ans >= INF ? -1 : ans);
}
