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

struct INFO {
    int gcd;
    int s;
    int t;
};
vector<int> s, t, r, q;
INFO xGCD(int a, int b) {
    s = { 1,0 };
    t = { 0,1 };
    r = { a,b };
 
    while (1)
    {
        int r2 = r[r.size() - 2];
        int r1 = r[r.size() - 1];
        q.push_back(r2 / r1);
        r.push_back(r2 % r1);
        
        if (r[r.size() - 1] == 0)
            break;
 
        int s2 = s[s.size() - 2];
        int s1 = s[s.size() - 1];
 
        int t2 = t[t.size() - 2];
        int t1 = t[t.size() - 1];
        
        int q1 = q[q.size() - 1];
        s.push_back(s2 - s1 * q1);
        t.push_back(t2 - t1 * q1);
    }
 
    // return gcd, s, t
    INFO ret = { r[r.size() - 2], s[s.size() - 1], t[t.size() - 1] };
 
    s.clear(), t.clear(), r.clear(), q.clear();
 
    return ret;
}

int n;
string S;
vt<int> vi(11);
ll pac[11], ans = 0;

void f(int idx) {
    if (idx > 0) {
        string t;
        FOR(n) {
            if (!vi[i]) t.push_back(S[i]);
        }

        int isP = 1;
        FOR(sz(t) / 2 + 1) {
            if (t[i] != t[sz(t) - i - 1]) isP = 0;
        }

        ans += isP * pac[n - idx];
        //cout << t << ' ' << isP << ' ' << pac[n - idx] << '\n';
        ans %= MOD;
    }
    
    if (idx == n) return;

    FOR(n) {
        if (!vi[i]) {
            vi[i] = 1;
            f(idx + 1);
            vi[i] = 0;
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
    
    pac[0] = 1;
    FOR(i, 1, 11) pac[i] = i * pac[i - 1] % MOD;

	int tc; cin >> tc;

    FOR(t, 1, tc + 1) {
        cout << "Case #" << t << ": ";

        cin >> n >> S;

        f(0);

        INFO x = xGCD(MOD, pac[n]);
        x.t = (x.t + MOD) % MOD;

        //cout << ans << '\n';
        cout << (ans * x.t) % MOD << '\n';
        //cout << x.t << '\n';
        ans = 0;
    }

	return 0;
}