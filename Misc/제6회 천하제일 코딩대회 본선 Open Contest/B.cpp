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

int n, k, cnt[10];
vt<int> a;

void init() {

}

void input() {
    string s;
    cin >> s >> k;
    EACH(i, s) a.push_back(i - '0');
    n = sz(a);
}

int check() {
    int mn = INF, mx = -1;
    FOR(10) if (cnt[i]) {
        mn = min(mn, cnt[i]);
        mx = max(mx, cnt[i]);
    }
    return mx - mn <= k;
}

int check2(int len) {
    vt<int> res;
    int mx = 0;
    FOR(10) if (cnt[i]) {
        res.push_back(cnt[i]);
        mx = max(mx, cnt[i]);
    }
    
    int sum = 0;
    EACH(i, res) {
        sum += max(0, mx - i + k);
    }

    return sum <= len;
}

void print() {
    vt<pii> res;
    int mx = 0;
    FOR(10) if (cnt[i]) {
        res.push_back(cnt[i]);
        mx = max(mx, cnt[i]);
    }
    
    int sum = 0;
    EACH(i, res) {
        sum += max(0, mx - i + k);
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

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        EACH(i, a) cnt[i]++;

        if (check()) {
            EACH(i, a) cout << i;
            continue;
        }

        FOR(i, n - 1, -1, -1) {
            cnt[a[i]]--;
            
            if (check2(n - i)) {
                FOR(j, 0, i + 1) cout << a[i];
                print();
            }
        }
    }

	return 0;
}