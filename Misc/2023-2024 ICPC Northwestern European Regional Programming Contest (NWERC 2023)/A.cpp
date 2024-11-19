#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

int n;
ll s, a[202020];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> s;
    for (int i = 1; i <= n; i++) cin >> a[i];

    sort(a + 1, a + n + 1);

    int ans = 1;

    ll acc = 0;
    vector<ll> mod3cnt(3);
    for (int i = 2; i <= n; i++) {
        if (i >= 3) {
            acc += a[i - 2];
            mod3cnt[a[i - 2] % 3]++;
        }

        ll res = 0;
        res += acc;

        if (mod3cnt[1] == mod3cnt[2]) ;
        else if (mod3cnt[1] < mod3cnt[2]) {
            res += mod3cnt[2] - mod3cnt[1];
        }
        else if (mod3cnt[1] > mod3cnt[2]) {
            int rem = mod3cnt[1] - mod3cnt[2];
            res += rem / 2;
            if (rem & 1) res += 2;
        }

        res += 6;

        if (res <= 3 * s) {
            ans = max(ans, i);
        }
    }

    cout << ans;
}
