#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int INF = 1e9 + 7;

int n, a[55];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> rev(n);
    vector<int> nxt(n);
    for (int i = 0; i < n; i++) rev[a[i]] = i;
    for (int i = 0; i < n; i++) nxt[a[i]] = rev[a[i] + 1];

    int k = -1;
    for (int i = 0; i < n; i++) {
        if (a[i] == n - 1) k = i;
    }

    int ans = 1;
    for (int i = 0; i + 1 < n; i++) {
        if (i + 1 == k) ans++;
        else if (i == k) continue;
        else if (nxt[a[i]] > nxt[a[i + 1]]) ans++;
    }

    cout << ans;
}