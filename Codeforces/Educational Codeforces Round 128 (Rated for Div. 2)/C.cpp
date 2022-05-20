#define _USE_MATH_DEFINES
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

int main() {
	#ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	int tc; cin >> tc;

    while (tc--) {
        string s; cin >> s;
        
        int n = sz(s);
        vt<int> a(1, -1);

        FOR(i, n) a.push_back(s[i] - '0');

        vt<int> p0(n + 1), p1(n + 1);

        FOR(i, 1, n + 1) {
            p0[i] = p0[i - 1];
            p1[i] = p1[i - 1];
            if (a[i] == 0) p0[i]++;
            if (a[i] == 1) p1[i]++;
        }

        int ans = INF;

        FOR(i, 1, n + 2) {
            int res0 = 0, res1 = 0;

            int l = 1, r = i - 1;
            while (l < r) {
                int mid = (l + r) / 2;
                
                int cnt0 = p0[i - 1] - p0[mid];
                int cnt1 = p1[mid - 1];

                if (cnt0 <= cnt1) r = mid;
                else l = mid + 1;
            }

            if (i > 1) {
                res0 += p0[i - 1] - p0[l];
                res1 += p1[l - 1];
            }

            l = i, r = n;
            while (l < r) {
                int mid = (l + r) / 2;
                
                int cnt0 = p0[mid - 1] - p0[i - 1];
                int cnt1 = p1[n] - p1[mid - 1];

                if (cnt0 < cnt1) l = mid + 1;
                else r = mid;
            }

            if (i <= n) {
                res0 += p0[l - 1] - p0[i - 1];
                res1 += p1[n] - p1[l - 1];
            }

            ans = min(ans, max(res0, res1));
        }

        cout << ans << '\n';
    }

	return 0;
}