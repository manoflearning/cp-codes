#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

int n, k, f;
int a[55];
int ans = 0;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> k >> f;
    for (int i = 0; i < f; i++) {
        int cnt; cin >> cnt;
        while (cnt--) {
            int x; cin >> x;
            a[x] |= (1 << i);
        }
    }

    for (int bit = 0; bit < (1 << f); bit++) {
        int cnt = n;
        for (int i = 1; i <= n; i++) {
            if (bit & a[i]) cnt--;
        }
        if (cnt >= k) {
            int res = 0;
            for (int j = 0; j < f; j++)
                if (bit & (1 << j)) res++;
            ans = max(ans, res);
        }
    }

    cout << ans;
}
