// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        int n; cin >> n;
        
        int lb = -INF, ub = INF;
        set<int> s;
        for (int i = 0; i < n; i++) {
            int op, x;
            cin >> op >> x;
            if (op == 1) lb = max(lb, x);
            if (op == 2) ub = min(ub, x);
            if (op == 3) s.insert(x);
        }

        if (ub < lb) cout << 0 << '\n';
        else {
            int ans = ub - lb + 1;
            for (auto& i : s) {
                if (lb <= i && i <= ub) ans--;
            }
            cout << ans << '\n';
        }
    }
}