#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const ll INF = 1e18;
const int MAXN = 101010;

int n, m;
ll r[MAXN], d[MAXN];
ll p[MAXN], w[MAXN];

void init() {}

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> r[i] >> d[i];
    cin >> m;
    for (int i = 1; i <= m; i++) cin >> p[i];
    for (int i = 1; i <= m; i++) cin >> w[i];
}

ll naive() {
    ll ret = 0;
    for (int i = 1; i <= n; i++) {
        ret += p[1] * (d[i] - r[i]);

        if (i == n) break;

        ll mn = INF;
        for (int j = 1; j <= m; j++) {
            mn = min(mn, p[j] * (r[i + 1] - d[i]) + (w[j] - w[1]));
        }

        ret += mn;
    }

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << endl;

        init();

        input();

        if (n <= 1'000 && m <= 1'000) cout << naive() << endl;
        else cout << 0 << endl;
    }
}