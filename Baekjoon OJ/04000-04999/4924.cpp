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

ll a[1010101], psum[1010101];

vector<int> spf(1010101);
vector<int> prime_set;

void linearSieve(int n) {
    for (ll i = 2; i <= n; ++i)
    {
        if (!spf[i]) {
            prime_set.push_back(i);
            spf[i] = i;
        }

        for (int j = 0; i * prime_set[j] <= n; ++j) {
            spf[i * prime_set[j]] = prime_set[j];
            if (i % prime_set[j] == 0) break;
        }
    }
}

int main() {
	#ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    linearSieve(1010100);
    
    a[1] = 0;
    FOR(i, 2, 1010101) {
        ll cnt = 0, x = i;
        while (x != 1) x /= spf[x], cnt++;
        
        if (cnt == 1) a[i] = -1;
        else a[i] = cnt;
    }
    
    FOR(i, 1, 1010101)
        psum[i] = a[i] + psum[i - 1];
    
    for (int tt = 1; ; tt++) {
        int l, r;
        cin >> l >> r;

        if (l == -1 && r == -1) break;

        ll ans = -INF, pmn = psum[l - 1], pen = 1;
        FOR(i, l, r + 1) {
            ans = max(ans, psum[i] - pmn - pen);
            if (pmn + pen > psum[i]) {
                pmn = psum[i];
                pen = 0;
            }
            pen++;
        }

        cout << tt << ". " << ans << '\n';
    }

	return 0;
}