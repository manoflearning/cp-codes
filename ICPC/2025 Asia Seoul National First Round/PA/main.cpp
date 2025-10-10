#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int N = 1010;
const int M = 1010101;

int n, m;
ll a[N][N], b[N][N];
int p[M];
ll mx[N];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> b[i][j];
        }
    }
    for (int i = 0; i < m; i++) cin >> p[i];

    for (int beta = 0; beta < n; beta++) {
        for (int alpha = 0; alpha < n; alpha++) {
            mx[beta] = max(mx[beta], abs(a[alpha][beta] - b[alpha][beta]));
        }
    }

    ll ans = 0;
    for (int i = 0; i < m; i++) ans += mx[p[i] - 1];

    cout << ans;
}