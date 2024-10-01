#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 1010101;
const int INF = 1e9 + 7;

int n;
ll l[MAXN], m[MAXN];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> l[i] >> m[i];

    int ans = 1, prv = INF;
    for (int i = n; i >= 1; i--) {
        if (m[i] <= prv) {
            prv = m[i];
        } else if (l[i] <= prv && prv < m[i]) {
            continue;
        } else if (prv < l[i]) {
            ans++;
            prv = m[i];
        } else assert(0);
    }

    cout << ans;
}
