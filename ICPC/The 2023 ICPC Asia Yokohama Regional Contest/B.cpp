// Suppose we have the same rank before starting [e-2c+1, e]-th quiz.
// If ratio(e-2c+1, e) >= p/q, then ratio(e-c+1, e) >= p/q (because ratio(e-2c+1, e-c) < p/q).
// So we can always start from e-2c+2!

#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 505050;

int n, c, bef[MAXN], aft[MAXN], psum[MAXN];
ll p, q;
string S;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> c >> p >> q >> S;

    psum[0] = (S[0] == 'Y');
    for (int i = 1; i < n; i++) {
        psum[i] = (S[i] == 'Y') + psum[i - 1];
    }

    bef[0] = 0;
    aft[0] = (c == 1 ? S[0] == 'Y' : 0);

    for (int i = 1; i < n; i++) {
        aft[i] = bef[i] = aft[i - 1];
        for (int j = max(0, i - 2 * c + 2); j <= i - c + 1; j++) {
            if (bef[j] != bef[i]) continue;

            ll n = psum[i] - (j > 0 ? psum[j - 1] : 0);
            ll d = i - j + 1;
            
            if (p * d <= n * q) { aft[i] = bef[i] + 1; break; }
        }
    }

    cout << aft[n - 1];
}