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
        ll n, m;
        cin >> n >> m;

        vt<ll> a(n);
        EACH(i, a) cin >> i;

        ll k; cin >> k;
        vt<ll> b(k);
        EACH(i, b) cin >> i;

        ll suma = 0, sumb = 0;
        EACH(i, a) suma += i;
        EACH(i, b) sumb += i;

        if (suma ^ sumb) {
            cout << "No\n";
            continue;
        }

        // now the sum of a and b are equal

        vt<pll> c;
        EACH(i, a) {
            ll x = i, cnt = 1;
            while (x % m == 0) x /= m, cnt *= m;

            if (sz(c) && c.back().fr == x) c.back().sc += cnt;
            else c.push_back({ x, cnt });
        }
        
        vt<ll> pm(1, 1);
        while (1) {
            pm.push_back(pm.back() * m);
            if (pm.back() > INF) break;
        }

        int idx = 0, ans = 1;
        EACH(i, b) {
            if (idx >= sz(c)) { ans = 0; break; }
            
            if (c[idx].fr * c[idx].sc < i) { ans = 0; break; }
            if (i % c[idx].fr) { ans = 0; break; }
            
            int x = lower_bound(all(pm), i / c[idx].fr) - pm.begin();
            if (x < sz(pm) && pm[x] == i / c[idx].fr) {
                c[idx].sc -= i / c[idx].fr;
                if (c[idx].sc == 0) idx++;
            }
            else { ans = 0; break; }
        }

        if (ans) cout << "Yes\n";
        else cout << "No\n";
    }

	return 0;
}