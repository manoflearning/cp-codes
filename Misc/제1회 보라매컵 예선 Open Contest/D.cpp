//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")

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
#define vt vector
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int n, m;
    cin >> n >> m;

    int ans = 1;
    int prv = 1;
    for (int i = 1; i < n; i++) {
        int cnt; cin >> cnt;
        if (cnt == 0) continue;
        if (cnt == 1) {
            int v; char d;
            cin >> v >> d;
            if (d == 'R' && v <= prv) ans = 0;
            if (d == 'L') prv = max(prv, v + 1);
        }
        if (cnt == 2) {
            int v1, v2; char d1, d2;
            cin >> v1 >> d1;
            cin >> v2 >> d2;
            if (d1 == 'R' && d2 == 'L') {
                if (v1 <= prv && prv <= v2) prv = v2 + 1;
            }
            if (d1 == 'L' && d2 == 'L') {
                prv = max(prv, v2 + 1);
            }
            if (d1 == 'R' && d2 == 'R') {
                if (v1 <= prv) ans = 0;
            }
            if (d1 == 'L' && d2 == 'R') {
                if (prv < v2) {
                    prv = max(prv, v1 + 1);
                    if (v2 <= prv) ans = 0;
                }
                else ans = 0;
            }
        }
    }
    if (prv == m + 1) ans = 0;

    cout << (ans ? "YES" : "NO");

	return 0;
}