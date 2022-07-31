// solution 1: top down dp
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

struct Query {
    int op1, x1, op2, x2;
};

int n;
ll dp[101010][2];
vt<Query> q;

int Hash(char x) {
    int ret = 0;
    if (x == '+') ret = 0;
    if (x == '-') ret = 1;
    if (x == '*') ret = 2;
    if (x == '/') ret = 3;
    return ret;
}

ll cal(ll x, ll op, ll y) {
    if (op == 0) return x + y;
    if (op == 1) return x - y;
    if (op == 2) return x * y;
    if (op == 3) return x / y;
}

ll f(int idx, int bit) {
    if (idx == -1) return 1;
    ll& ret = dp[idx][bit];
    if (ret != -1) return ret;
    
    ret = 0;

    if (bit) ret = max(ret, f(idx - 1, !bit));

    ll val = f(idx - 1, bit);
    if (val > 0) {
        ret = max(ret, cal(val, q[idx].op1, q[idx].x1));
        ret = max(ret, cal(val, q[idx].op2, q[idx].x2));
    }

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

    FOR(101010) FOR(j, 2) dp[i][j] = -1;

	cin >> n;
    q.resize(n);
    EACH(i, q) {
        string s1, s2;
        cin >> s1 >> s2;
        i.op1 = Hash(s1[0]);
        i.x1 = s1[1] - '0';
        i.op2 = Hash(s2[0]);
        i.x2 = s2[1] - '0';
    }
    
    if (f(n - 1, 0) <= 0 && f(n - 1, 1) <= 0) cout << "ddong game";
    else cout << max(f(n - 1, 0), f(n - 1, 1));

	return 0;
}

// solution 2: bottom up dp
/*#define _USE_MATH_DEFINES
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
const ll INF = 1e15 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

struct Query {
    int op1, x1, op2, x2;
};

int n;
ll dp[101010][2];
vt<Query> q;

int Hash(char x) {
    int ret = 0;
    if (x == '+') ret = 0;
    if (x == '-') ret = 1;
    if (x == '*') ret = 2;
    if (x == '/') ret = 3;
    return ret;
}

ll cal(ll x, ll op, ll y) {
    ll ret = 0;
    if (op == 0) return ret = x + y;
    if (op == 1) return ret = x - y;
    if (op == 2) return ret = x * y;
    if (op == 3) return ret = x / y;
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

	cin >> n;
    q.resize(n);
    EACH(i, q) {
        string s1, s2;
        cin >> s1 >> s2;
        i.op1 = Hash(s1[0]);
        i.x1 = s1[1] - '0';
        i.op2 = Hash(s2[0]);
        i.x2 = s2[1] - '0';
    }

    dp[0][0] = max(cal(1, q[0].op1, q[0].x1), cal(1, q[0].op2, q[0].x2));
    dp[0][1] = 1;
    FOR(i, 1, n) {
        auto& Q = q[i];

        if (dp[i - 1][0] > 0) {
            dp[i][0] = max(dp[i][0], cal(dp[i - 1][0], Q.op1, Q.x1));
            dp[i][0] = max(dp[i][0], cal(dp[i - 1][0], Q.op2, Q.x2));
            dp[i][1] = max(dp[i][1], dp[i - 1][0]);
            dp[i][1] = max(dp[i][1], dp[i - 1][0]);
        }
        if (dp[i - 1][1] > 0) {
            dp[i][1] = max(dp[i][1], cal(dp[i - 1][1], Q.op1, Q.x1));
            dp[i][1] = max(dp[i][1], cal(dp[i - 1][1], Q.op2, Q.x2));
        }
        
        //cout << dp[i][0] << ' ' << dp[i][1] << '\n';
        //if (dp[i][0] <= 0 && dp[i][1] <= 0) bit = 1;
    }

    if (dp[n - 1][0] <= 0 && dp[n - 1][1] <= 0) cout << "ddong game";
    else cout << max(dp[n - 1][0], dp[n - 1][1]);

	return 0;
}*/