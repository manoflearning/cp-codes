// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int m;
vector<int> cnt(33);

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> m;
    for (int i = 0; i < m; i++) {
        int op, x;
        cin >> op >> x;
        if (op == 1) {
            cnt[x]++;
        }
        if (op == 2) {
            bool YES = true;

            vector<int> tmp = cnt;
            for (int bit = 29; bit >= 0; bit--) {
                if (x & (1 << bit)) {
                    if (tmp[bit]) continue;

                    bool isValid = false;
                    for (int j = bit - 1; j >= 0; j--) {
                        if (tmp[j] == 0) break;
                        else if (tmp[j] == 1) {
                            tmp[j] = 0;
                        }
                        else if (tmp[j] == 2) {
                            isValid = true;
                            tmp[j] = 0; break;
                        }
                    }

                    YES &= isValid;
                }
            }

            cout << (YES ? "YES" : "NO") << '\n';
        }

        for (int bit = 0; bit < 30; bit++) {
            if (3 == cnt[bit]) {
                cnt[bit + 1]++;
                cnt[bit] = 1;
            }
        }
    }
}