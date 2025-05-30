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

int n, q;
pii a[202020 + 1010101];
int flag;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> q;
    flag = q;
    for (int i = q + 1; i <= q + n; i++) {
        a[i] = { i - q, 0 };
    }

    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            char c; cin >> c;
            int d = -1;
            if (c == 'R') d = 0;
            if (c == 'L') d = 1;
            if (c == 'U') d = 2;
            if (c == 'D') d = 3;
            a[flag] = a[flag + 1];
            a[flag].fr += dx[d];
            a[flag].sc += dy[d];
            flag--;
        }
        if (op == 2) {
            int x; cin >> x;
            cout << a[flag + x].fr << ' ' << a[flag + x].sc << '\n';
        }
    }
}