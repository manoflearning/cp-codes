#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

// int f(int idx, int bit, const int n, const vector<int> &a, vector<vector<int>> &dp) {
//     int &ret = dp[idx][bit];
//     if (ret != -1) return ret;
//     if (idx == n) return ret = 0;

//     ret = 0;
//     bool yes = 0;
//     for (int i = 0; i < 3; i++) {
//         if (~bit & (1 << i)) continue;
//         const int nbit = bit - (1 << i);
//         if ((nbit & 5) != 5 && (nbit & 2) != 2) continue;
//         yes = 1;
//         ret |= !f(idx, nbit, n, a, dp);
//     }
//     if (!yes) ret |= !f(idx + 1, a[idx + 1], n, a, dp);

//     return ret;
// }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
  
        int ans = 0;
        for (int i = 0; i < n; i++) {
            string s; cin >> s;

            int bit = 0;
            if (s[0] == '=') {
                bit |= (s[3] == 'x') << 0;
                bit |= (s[4] == 'x') << 1;
                bit |= (s[5] == 'x') << 2;
            } else {
                bit |= (s[0] == 'x') << 0;
                bit |= (s[1] == 'x') << 1;
                bit |= (s[2] == 'x') << 2;
            }

            if (bit == 7) {
                ans ^= 2;
            } else if (bit == 2 || bit == 5) {
                ans ^= 0;
            } else {
                ans ^= 1;
            }
        }

        cout << (ans ? "Monocarp" : "Polycarp") << '\n';
    }
}