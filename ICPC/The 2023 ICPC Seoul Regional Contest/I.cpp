#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

const int MAXN = 1010101;

int n, a[MAXN], b[MAXN];

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
    }
}

int ans = 0;

void solve() {
    int height = -1;
    for (int i = n; i >= 1; i--) {
        if (height < a[i]) {
            ans++;
            height = b[i];
        }
        else height = min(height, b[i]);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    solve();

    cout << ans;
}