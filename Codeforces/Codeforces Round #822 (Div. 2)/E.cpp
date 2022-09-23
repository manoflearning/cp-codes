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

#define EXPAND( x ) x // Use this if MS Visual Studio doesn't expand __VA_ARGS__ correctly
#define F_OR(i, a, b, s) for (int i = (a); (s) > 0 ? i < (b) : i > (b); i += (s))
#define F_OR1(e) F_OR(i, 0, e, 1)
#define F_OR2(i, e) F_OR(i, 0, e, 1)
#define F_OR3(i, b, e) F_OR(i, b, e, 1)
#define F_OR4(i, b, e, s) F_OR(i, b, e, s)
#define GET5(a, b, c, d, e, ...) e
#define F_ORC(...) EXPAND( GET5(__VA_ARGS__, F_OR4, F_OR3, F_OR2, F_OR1) )
#define FOR(...) EXPAND( F_ORC(__VA_ARGS__ )(__VA_ARGS__) )
#define EACH(x, a) for (auto& x : a)

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n;
vt<vt<int>> ans;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n;
    ans.resize(n + 1, vt<int>(n + 1, -1));
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        ans[i][i] = x;
    }

    int rem = (ans[1][1] + ans[2][2]) % n;
    ans[1][2] = 0, ans[2][1] = (rem + 1) % n;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (ans[i][j] != -1) continue;

            vt<int> vi(n);
            for (int k = -n; k <= n; k++) {
                if (k == 0) continue;
                
                if (i + k < 1 || n < i + k) continue;
                if (j + k < 1 || n < j + k) continue;

                if (ans[i][j + k] == -1) continue;
                if (ans[i + k][j] == -1) continue;
                if (ans[i + k][j + k] == -1) continue;

                rem = (ans[i][j + k] + ans[i + k][j]) % n;

                int x = (rem - ans[i + k][j + k]) % n;
                x = (x + n) % n;

                vi[x] = 1;
            }

            for (int k = -n; k <= n; k++) {
                if (k == 0) continue;
                
                if (i + k < 1 || n < i + k) continue;
                if (j - k < 1 || n < j - k) continue;

                if (ans[i][j - k] == -1) continue;
                if (ans[i + k][j] == -1) continue;
                if (ans[i + k][j - k] == -1) continue;

                rem = (ans[i][j - k] + ans[i + k][j]) % n;

                int x = (rem - ans[i + k][j - k]) % n;
                x = (x + n) % n;

                vi[x] = 1;
            }

            int x = -1;
            for (int k = 0; k < n; k++) {
                if (!vi[k]) { x = k; break; }
            }

            assert(x != -1);

            ans[i][j] = x;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << ans[i][j] << ' ';
        }
        cout << '\n';
    }

	return 0;
}