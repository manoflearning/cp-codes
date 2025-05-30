// wlog, n <= m

// if n = 1, m = 1
// 1
// if n = 1, m = 2
// 1 2
// if n = 1, m = x
// 1 2 4 ... x(x-1)/2+1

// if n = 2, m = 2
// 1 2
// 3 6
// 1 5
// 4 3

#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n, m;
vector<vector<ll>> ans;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    if (n > m) swap(n, m); // wlog, n <= m

    ans.resize(n, vector<ll>(m));

    ll add = 1;
    ans[0][0] = 1;
    for (int i = 1; i < n + m - 1; i++) {
        int r = (i & 1 ? i : 0), c = (i & 1 ? 0 : i);
        while (i & 1 ? r >= 0 : r < n) {
            if (0 <= r && r < n && 0 <= c && c < m) {
                if (0 < r && 0 < c) {
                    ans[r][c] = add + 1 + min(ans[r - 1][c], ans[r][c - 1]);
                    add += 2;
                }
                else if (0 < r) {
                    ans[r][c] = add++ + ans[r - 1][c];
                }
                else if (0 < c) {
                    ans[r][c] = add++ + ans[r][c - 1];
                }
            }

            r += (i & 1 ? -1 : 1);
            c += (i & 1 ? 1 : -1);
        }
    }

    // print ans

    for (auto& i : ans) {
        for (auto& j : i) 
            cout << j << ' ';
        cout << '\n';
    }
}