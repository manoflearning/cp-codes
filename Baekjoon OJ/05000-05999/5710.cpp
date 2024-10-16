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

ll cal(ll x) { // 사용량 -> 요금
    ll ret = 0;

    ret += 2 * min(100ll, x);
    x -= 100;
    if (x <= 0) return ret;

    ret += 3 * min(10000ll - 100, x);
    x -= 10000ll - 100;
    if (x <= 0) return ret;

    ret += 5 * min(1000000ll - 10000, x);
    x -= 1000000ll - 10000;
    if (x <= 0) return ret;

    ret += 7 * x;

    return ret;
}

ll rcal(ll x) { // 요금 -> 사용량
    ll ret = 0;

    ret += min(2ll * 100, x) / 2;
    x -= 200;
    if (x <= 0) return ret;
    
    ret += min(3ll * (10000 - 100), x) / 3;
    x -= 3ll * (10000 - 100);
    if (x <= 0) return ret;

    ret += min(5ll * (1000000 - 10000), x) / 5;
    x -= 5ll * (1000000 - 10000);
    if (x <= 0) return ret;

    ret += x / 7;

    return ret;
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
	
    while (1) {
        ll a, b;
        cin >> a >> b;

        if (a == 0 && b == 0) break;

        ll c = rcal(a);
        
        ll l = 0, r = c;
        while (l < r) {
            ll mid = (l + r) / 2;

            if (cal(c - mid) - cal(mid) > b) l = mid + 1;
            else r = mid; 
        }
        
        cout << cal(l) << '\n';
    }

	return 0;
}