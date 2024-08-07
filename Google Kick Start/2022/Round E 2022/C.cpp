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
const int MOD1 = 1e9 + 7, MOD2 = 1e9 + 9;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

const ll d = 26;

int n;
string s;
vt<ll> a, b;
vt<ll> pa1, pa2, sa1, sa2, ra1, ra2, pb1, pb2;
ll dexp1[101010], dexp2[101010];

void init() {
    a.clear();
    b.clear();
    pa1.clear();
    pa2.clear();
    sa1.clear();
    sa2.clear();
    ra1.clear();
    ra2.clear();
    pb1.clear();
    pb2.clear();
}

void input() {
    cin >> n >> s;
    a.resize(n);
    b.resize(n);
    for (int i = 0; i < sz(s); i++) {
        a[i] = s[i] - 'a';
        b[sz(s) - i - 1] = s[i] - 'a';
    }
}

void hashing() {
    pa1.resize(n);
    pa2.resize(n);
    pa1[0] = pa2[0] = a[0];
    for (int i = 1; i < n; i++) {
        pa1[i] = (d * pa1[i - 1] + a[i]) % MOD1;
        pa2[i] = (d * pa2[i - 1] + a[i]) % MOD2;
    }

    sa1.resize(n);
    sa2.resize(n);
    sa1[n - 1] = sa2[n - 1] = a[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        sa1[i] = (sa1[i + 1] + dexp1[n - i - 1] * a[i]) % MOD1;
        sa2[i] = (sa2[i + 1] + dexp2[n - i - 1] * a[i]) % MOD2;
    }

    ra1.resize(n);
    ra2.resize(n);
    ra1[0] = ra2[0] = a[0];
    for (int i = 1; i < n; i++) {
        ra1[i] = (ra1[i - 1] + dexp1[i] * a[i]) % MOD1;
        ra2[i] = (ra2[i - 1] + dexp2[i] * a[i]) % MOD2;
    }

    pb1.resize(n);
    pb2.resize(n);
    pb1[0] = pb2[0] = b[0];
    for (int i = 1; i < n; i++) {
        pb1[i] = (d * pb1[i - 1] + b[i]) % MOD1;
        pb2[i] = (d * pb2[i - 1] + b[i]) % MOD2;
    }
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    dexp1[0] = dexp2[0] = 1;
    FOR(i, 1, 101010) {
        dexp1[i] = d * dexp1[i - 1] % MOD1;
        dexp2[i] = d * dexp2[i - 1] % MOD2;
    }

	int tc; cin >> tc;
	FOR(tt, 1, tc + 1) {
        init();

		cout << "Case #" << tt << ": ";

        input();

        hashing();

        int ans = sz(s);
        for (int st = 1; st < sz(s); st++) {
            /*bool res = 1;
            for (int i = 0; i + st < sz(s); i++) {
                if (s[i + st] != p[i]) { res = 0; break; }
            }*/

            if (sa1[st] != pa1[n - st - 1] || sa2[st] != pa2[n - st - 1]) continue;

            /*for (int i = 0; i < st; i++) {
                if (s[i] != s[st - i - 1]) { res = 0; break; }
            }*/

            if (pa1[st - 1] != ra1[st - 1] || pa2[st - 1] != ra2[st - 1]) continue;
            
            ans = st;
            break;
        }

        for (int i = 0; i < ans; i++) {
            cout << s[i];
        }
        cout << '\n';
	}

	return 0;
}