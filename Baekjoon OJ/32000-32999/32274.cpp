#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int MAXN = 50505;
const ll INF = 1e18;

int n;
ll a[MAXN], mn, mx;
vector<int> mn_idxs, mx_idxs;
int mn_cnt = 0, mx_cnt = 0;

void init() {
    mn = INF, mx = -INF;
    mn_idxs.clear();
    mx_idxs.clear();
    mn_cnt = mx_cnt = 0;
}

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << '\n';

        init();

        input();

        for (int i = 1; i <= n; i++) {
            mn = min(mn, a[i]);
            mx = max(mx, a[i]);
        }

        if (mn == mx) {
            cout << 0 << '\n';
            continue;
        }

        for (int i = 1; i <= n; i++) {
            if (a[i] == mn) { mn_idxs.push_back(i); mn_cnt++; }
            if (a[i] == mx) { mx_idxs.push_back(i); mx_cnt++; }
        }

        if (mn_cnt + mx_cnt == n) {
            if (abs(mn_cnt - mx_cnt) <= 1) {
                cout << 0 << '\n';
            } else {
                cout << 1 << '\n';
                // TODO
            }
        } else {
            
        }
    }
}
