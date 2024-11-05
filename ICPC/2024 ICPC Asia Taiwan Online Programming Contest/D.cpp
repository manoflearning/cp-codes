#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int MOD = 1e9 + 7;
const int dy[] = {0, 0, 1, 0, -1, 1, 1, -1, -1};
const int dx[] = {0, 1, 0, -1, 0, 1, -1, 1, -1};

int n, m;
ll w0, w1, w2;
vector<string> a;

ll p2[20];

ll power(ll x, ll y) {
    if (y == 0) return 1;
    if (y == 1) return x;
    ll res = power(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    p2[0] = 1;
    for (int i = 1; i < 20; i++)
        p2[i] = 2 * p2[i - 1] % MOD;

    cin >> n >> m >> w0 >> w1 >> w2;
    a.resize(n);
    for (auto &i : a) cin >> i;

    ll ans = 0;

    for (int y = 0; y < n; y++) {
        for (int x = 0; x < m; x++) {
            int v0 = 0, v1 = 0, v2 = 0;
            int q0 = 0, q1 = 0, q2 = 0;
            for (int d = 0; d < 9; d++) {
                int ny = y + dy[d], nx = x + dx[d];
                if (ny < 0 || n <= ny || nx < 0 || m <= nx) continue;
                if (a[ny][nx] == 'V') {
                    if (d == 0) v0++;
                    else if (d <= 4) v1++;
                    else if (d <= 8) v2++;
                }
                if (a[ny][nx] == '?') {
                    if (d == 0) q0++;
                    else if (d <= 4) q1++;
                    else if (d <= 8) q2++;
                }
            }

            // cout << y << ' ' << x << ' ' << v0 << ' ' << v1 << ' ' << v2 << '\n';
            // cout << y << ' ' << x << ' ' << q0 << ' ' << q1 << ' ' << q2 << '\n';

            ll res = 0;
            if (v0) res = w0;
            else if (v1) {
                if (q0) {
                    res = (res + w0 * power(2, MOD - 2) % MOD) % MOD;
                    res = (res + w1 * power(2, MOD - 2) % MOD) % MOD;
                } else {
                    res = (res + w1) % MOD;
                }
            } else if (v2) {
                res = (res 
                    + w0 
                    * (p2[q0] - 1) % MOD
                    * power(p2[q0], MOD - 2) % MOD
                ) % MOD;
                res = (res 
                    + w1
                    * power(p2[q0], MOD - 2) % MOD
                    * (p2[q1] - 1) % MOD
                    * power(p2[q1], MOD - 2) % MOD
                ) % MOD;
                res = (res
                    + w2
                    * power(p2[q0], MOD - 2) % MOD
                    * power(p2[q1], MOD - 2) % MOD
                );
            } else {
                res = (res 
                    + w0 
                    * (p2[q0] - 1) % MOD
                    * power(p2[q0], MOD - 2) % MOD
                ) % MOD;
                res = (res 
                    + w1
                    * power(p2[q0], MOD - 2) % MOD
                    * (p2[q1] - 1) % MOD
                    * power(p2[q1], MOD - 2) % MOD
                ) % MOD;
                res = (res 
                    + w2
                    * power(p2[q0], MOD - 2) % MOD
                    * power(p2[q1], MOD - 2) % MOD
                    * (p2[q2] - 1) % MOD
                    * power(p2[q2], MOD - 2) % MOD
                ) % MOD;
            }

            ans = (ans + res) % MOD;
        }
        // cout << '\n';
    }

    cout << ans;
}
