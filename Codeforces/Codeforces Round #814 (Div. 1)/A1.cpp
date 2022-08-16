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

int n;
ll a[101010], pxor[101010], dp[101010];

ll query(int l, int r) {
    return pxor[r] ^ pxor[l - 1];
}

ll f(int idx) {
    ll& ret = dp[idx];
    if (ret != -1) return ret;
    if (idx == n + 1) return ret = 0;
    if (a[idx] == 0) return ret = f(idx + 1);

    ret = f(idx + 1) + 1;
    FOR(i, idx + 1, n + 1) {
        if (a[i] == query(idx, i - 1)) {
            ret = min(ret, f(i + 1) + i - idx);
        }
    }
    return ret;
}

void init() {
    FOR(i, 1, n + 2) dp[i] = -1;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    FOR(101010) dp[i] = -1;

	int tc; cin >> tc;
	FOR(tt, 1, tc + 1) {
		cin >> n;
        
        FOR(i, 1, n + 1) cin >> a[i];

        FOR(i, 1, n + 1)
            pxor[i] = a[i] ^ pxor[i - 1];

        cout << f(1) << '\n';

        init();

        // 오직 길이 1 또는 2의 연산만을 사용해서 최적해를 구할 수 있다.
        // dp?

        /*vt<ll> arr(n), a;
        EACH(i, arr) cin >> i;

        ll len = 0, ans = 0;
        FOR(i, n) {
            if (arr[i] > 0 && i > 0 && arr[i] == arr[i - 1]) { len++; continue; }
            if (arr[i] > 0 && i + 1 < n && arr[i] == arr[i + 1]) { len++; continue; }

            if (len) { 
                ans += len / 2; len = 0; 
                if (len & 1) a.push_back(0);
            }

            a.push_back(arr[i]);
        }
        if (len) { 
            ans += len / 2; len = 0; 
            if (len & 1) a.push_back(0);
        }

        FOR(i, sz(a)) {
            if (a[i] == 0) continue;
            
            ans++;
            if (i + 1 < sz(a) && a[i + 1] > 0) {
                a[i + 1] ^= a[i];
            }
            a[i] = 0;
        }*/

        //cout << ans << '\n';
	}

	return 0;
}