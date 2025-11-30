#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) (x).begin(), (x).end()

constexpr int N = 101010;

int n;
ll l;
ll a[N], b[N];
int k;
ll p;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> l;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    cin >> k >> p;

    ll rem = 0;
    rem += a[1];
    for (int i = 1; i + 1 <= n; i++) {
        rem += max(0ll, (a[i + 1] - a[i]) - b[i]);
    }
    rem += (l - a[n] - b[n]);

    ll lsum = 0, rsum = 0;
    if (rem < b[k]) {
        for (int i = 1; i <= n; i++) {
            if (b[i] <= rem) continue;
        
            if (i < k) lsum += b[i];
            if (k < i) rsum += b[i];
        }
    } else {
        bool ladd = 1;
        for (int i = 1; i <= n; i++) {
            if (b[i] <= rem) continue;

            if (lsum + b[i] > p) ladd = 0;

            if (ladd) lsum += b[i];
            else rsum += b[i];
        }
    }

    // cout << "rem = " << rem << '\n';
    // cout << "lsum = " << lsum << ", rsum = " << rsum << '\n';

    if (lsum <= p && p + b[k] + rsum <= l) cout << "YES";
    else cout << "NO";   
}