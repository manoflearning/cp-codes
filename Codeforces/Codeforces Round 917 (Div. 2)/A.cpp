// if cnt_neg is odd -> 0
// if cnt_neg is even -> 1

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

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        int n; cin >> n;
        vector<int> a(n);

        int cnt_0 = 0, cnt_neg = 0;
        for (auto& i : a) {
            cin >> i;
            if (i < 0) cnt_neg++;
            if (i == 0) cnt_0++;
        }

        if (cnt_0 > 0) {
            cout << 0 << '\n';
            continue;
        }
        else {
            if (cnt_neg & 1) cout << 0 << '\n';
            else {
                cout << 1 << '\n';
                cout << 1 << ' ' << 0 << '\n';
            }
        }
    }
}