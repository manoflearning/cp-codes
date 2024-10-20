#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 505050;

int n, q;
int color[2][MAXN];
int cnt[2];
ll ans = 0;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> q;

    for (int i = 1; i <= n; i++) color[0][i] = color[1][i] = (i & 1);

    ans = (ll)n * n;
    cnt[0] = cnt[1] = n;

    while (q--) {
        string op; int x;
        cin >> op >> x;
        
        int idx = -1;
        if (op == "ROW") idx = 0;
        if (op == "COLUMN") idx = 1;
        
        color[idx][x] = !color[idx][x];
        if (x > 1 && color[idx][x - 1] != color[idx][x]) {
            ans += cnt[idx];
            cnt[!idx]++;
        }
        if (x > 1 && color[idx][x - 1] == color[idx][x]) {
            ans -= cnt[idx];
            cnt[!idx]--;
        }
        if (x < n && color[idx][x] != color[idx][x + 1]) {
            ans += cnt[idx];
            cnt[!idx]++;
        }
        if (x < n && color[idx][x] == color[idx][x + 1]) {
            ans -= cnt[idx];
            cnt[!idx]--;
        }

        cout << ans << '\n';
    }
}