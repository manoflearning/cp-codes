#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

const int N = 101;

set<int> ans[N];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    // test cases
    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        
        int opt = 0, opt_len = 0;
        for (int i = 0; (1 << i) <= n; i++) {
            int lb = (1 << i), ub = (1 << (i + 1)) + (1 << i) - 1;
            ub = min(ub, n);

            int len = ub - lb + 1;
            if (opt_len < len) opt = i, opt_len = len;
        }

        int lb = (1 << opt), ub = (1 << (opt + 1)) + (1 << opt) - 1;
        ub = min(ub, n);
        
        cout << ub - lb + 1 << '\n';
        for (int i = lb; i <= ub; i++)
            cout << i << ' ';
        cout << '\n';
    }
}