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
	//freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	//freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
    
	int tc; cin >> tc;
    FOR(tt, 1, tc + 1) {
        cout << "Case #" << tt << endl;
        
        int n, m;
        cin >> n >> m;

        string s1, s2;
        cin >> s1 >> s2;

        vt<int> a, b;
        EACH(i, s1) a.push_back(i == 'a' ? 1 : 2);
        EACH(i, s2) b.push_back(i == 'a' ? 1 : 2);

        int suma1 = 0;
        EACH(i, a) suma1 += (i & 1);

        int suma2 = n - suma1;

        int bit = 0;
        for (int i = 0; i <= suma1; i++) {
            for (int j = 0; j <= suma1 - i; j++) {
                for (int k = 0; k <= suma2; k++) {
                    for (int p = 0; p <= suma2 - k; p++) {
                        int cnt = 0;
                        vt<int> vi(n);

                        for (int ii = 0; cnt < i; ii++) {
                            if (a[ii] == 1) {
                                cnt++;
                                vi[ii] = 1;
                            }
                        }
                        cnt = 0;
                        for (int ii = n - 1; cnt < j; ii--) {
                            if (a[ii] == 1) {
                                cnt++;
                                vi[ii] = 1;
                            }
                        }
                        cnt = 0;
                        for (int ii = 0; cnt < k; ii++) {
                            if (a[ii] == 2) {
                                cnt++;
                                vi[ii] = 1;
                            }
                        }
                        cnt = 0;
                        for (int ii = n - 1; cnt < p; ii--) {
                            if (a[ii] == 2) {
                                cnt++;
                                vi[ii] = 1;
                            }
                        }

                        vt<int> res;
                        for (int ii = 0; ii < n; ii++) {
                            if (!vi[ii]) res.push_back(a[ii]);
                        }

                        if (res == b) bit = 1;
                    }
                }
            }
        }

        if (bit) cout << "YES" << endl;
        else cout << "NO" << endl;
    }

	return 0;
}