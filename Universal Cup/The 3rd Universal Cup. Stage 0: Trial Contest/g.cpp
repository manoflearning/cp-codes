#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int r, c;
ll p;

double p2[2020], fac[2020];
double ans = 0.0;

void init() {
    p2[0] = 1;
    for (int i = 1; i < 2020; i++)
        p2[i] = 2 * p2[i - 1];

    fac[0] = 1;
    for (int i = 1; i < 2020; i++)
        fac[i] = i * fac[i - 1];
}

void input() { cin >> r >> c >> p; }

inline double C(int n, int r) { return fac[n] / (fac[r] * fac[n - r]); }

void solve() {
    // rth row
    double tmp = 0;
    for (int i = 0; i < c - 1; i++) {
        double prob = C(r + i, i) / p2[r - 1 + i] - tmp;
        double expected_time = (double)p / 4 * (c - 1 - i);
        ans += prob * expected_time;
        cout << i << ' ' << prob << ' ' << expected_time << '\n';
        tmp = prob;
    }
    // cth column
    for (int i = 0; i < r - 1; i++) {
        double prob = C(c + i, i) / p2[c + i];
        double expected_time = (double)p / 4 * (r - 1 - i);
        ans += prob * expected_time;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    init();

    input();

    solve();

    cout << fixed;
    cout.precision(8);

    cout << ans;
}