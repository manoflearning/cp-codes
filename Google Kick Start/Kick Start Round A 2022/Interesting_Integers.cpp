#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
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

const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

const int MAX = 10;

vector<int> prime;

string A, B;
ll a, b, p10[15];

vt<int> p;
int d[15];

ll f(ll x, string s) {
    ll ret = 0;

    FOR(j, sz(s) + 1) {
        FOR(i, 1, 9 * j + 1) {
            ll ii = i;
            p.clear();
            EACH(k, prime) {
                while (ii % k == 0) {
                    ii /= k;
                    p.push_back(k);
                }
            }

            if (ii > 1) continue;

            ret += f2(x, s);
        }
    }
    
    return ret;
}

ll f2(ll x, string s) {
    if (p.empty()) {
        ll sum = 0;
        int mul = 9;
        FOR(i, sz(s)) {
            sum += p10[sz(s) - i - 1] * d[i];
            if (d[i] >= 10) return 0;

            if (d[i] >= 2) mul = min(mul, 4);
            if (d[i] >= 3) mul = min(mul, 3);
            if (d[i] >= 4) mul = min(mul, 2);
            if (d[i] >= 5) mul = min(mul, 1);
        }
        
        if (sum > x) return 0;

        ll ret = 0;
        FOR(i, 1, mul + 1) {
            if (sum * i <= x) ret = i;
            else return ret;
        } 
        return ret;
    }

    FOR(i, sz(s)) {
        int pp = p.back();
        d[i] *= pp;
        p.pop_back();
        f2(x, s);
        d[i] /= pp;
        p.push_back(pp);
    }
}

void init() {
    prime.push_back(2);
    prime.push_back(3);
    prime.push_back(5);
    prime.push_back(7);

    p10[0] = 1;
    FOR(i, 1, 15) p10[i] = 10 * p10[i - 1];

    FOR(i, 15) d[i] = 1;
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
    
    init();

	int tc; cin >> tc;

    FOR(tc) {
        cin >> A >> B;
        
        FOR(i, sz(A)) {
            a += p10[sz(A) - i - 1] * (A[i] - '0');
        }
        FOR(i, sz(B)) {
            b += p10[sz(B) - i - 1] * (B[i] - '0');
        }

        cout << "Case #" << i + 1 << ": ";
        cout << f(b, B) - (a > 1 ? f(a - 1, to_string(a - 1)) : 0);
        cout << '\n';
    }

	return 0;
}