//#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

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

const int MAX = 3030;

int n, m, k;
int psum[MAX * 3][MAX * 3];
int mny = INF, mnx = INF, mxy = -INF, mxx = -INF;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> m >> k;
    for (int i = 0; i < k; i++) {
        int x, y, len;
        cin >> y >> x >> len;
        y += MAX, x += MAX;
        psum[y - len][x]++;
        psum[y - len + 1][x]++;
        psum[y + 1][x - len - 1]--;
        psum[y + 1][x - len]--;
        mny = min(mny, y - len);
        mnx = min(mnx, x - len - 1);

        psum[y + 1][x + len + 1]--;
        psum[y + 1][x + len]--;
        psum[y + len + 1 + 1][x + 1 - 1]++;
        psum[y + len + 1][x + 1 - 1]++;
        mxy = max(mxy, y + len + 1 + 1);
        mxx = max(mxx, x + len + 1);
    }
    
    for (int i = mny; i <= mxy; i++) {
        for (int j = mxx; j >= mnx; j--) {
            psum[i][j] += psum[i - 1][j + 1];
        }
    }

    for (int i = mny; i <= mxy; i++) {
        for (int j = mnx; j <= mxx; j++) {
            psum[i][j] += psum[i - 1][j - 1];
        }
    }

    int ans = 0;
    for (int i = 1 + MAX; i <= n + MAX; i++) {
        for (int j = 1 + MAX; j <= m + MAX; j++) {
            if (psum[i][j]) ans++;
        }
    }

    cout << ans;

	return 0;
}