// #pragma gcc optimize("O3")
// #pragma gcc optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long

const ll INF = 1e18;

const vector<int> adj[4] = { { 0, 1 }, { 1, 3 }, { 2, 3 }, { 0, 2 } };

int n, mid;
ll a[505][505];
ll mn[4], mn2[4];
ll ans;

void init() {
    for (int i = 0; i < 4; i++) 
        mn[i] = mn2[i] = INF;
    ans = INF;
}

void input() {
    cin >> n;
    mid = n / 2;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
}

void solve() {
    for (int i = 0; i < n; i++) {
        if (i == mid) continue;
        for (int j = 0; j < n; j++) {
            if (j == mid) continue;
            int idx = (i < mid ? 0 : 2) + (j < mid ? 0 : 1);
            mn[idx] = min(mn[idx], a[i][j]);
        }
    }
    // cout << mn[0] << ' ' << mn[1] << ' ' << mn[2] << ' ' << mn[3] << '\n';

    for (int i = 0; i < mid; i++) {
        mn2[0] = min(mn2[0], a[i][mid]);
        mn2[3] = min(mn2[3], a[mid][i]);
    }
    for (int i = mid + 1; i < n; i++) {
        mn2[1] = min(mn2[1], a[mid][i]);
        mn2[2] = min(mn2[2], a[i][mid]);
    }
    // cout << mn2[0] << ' ' << mn2[1] << ' ' << mn2[2] << ' ' << mn2[3] << '\n';

    // case 1
    // ans = min(ans, mn[0] + mn[1] + mn[2] + mn[3]);

    // case 1~16
    for (int bit = 0; bit < (1 << 4); bit++) {
        ll res = mn[0] + mn[1] + mn[2] + mn[3];

        set<int> st;
        for (int i = 0; i < 4; i++) {
            if (bit & (1 << i)) {
                for (auto& j : adj[i]) st.insert(j);
                res += mn2[i];
            }
        }

        for (auto& j : st) res -= mn[j];

        ans = min(ans, res);
    }

    // case 17
    ans = min(ans, a[mid][mid]);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        solve();

        cout << ans << '\n';
    }
}