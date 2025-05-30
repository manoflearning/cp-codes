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
vector<int> a[2];

void init() {
    a[0].clear();
    a[1].clear();
}

void input() {
    cin >> n;
    
    string s;
    cin >> s;
    for (auto& i : s) {
        a[0].push_back(i == 'B' ? 1 : 0);
    }

    cin >> s;
    for (auto& i : s) {
        a[1].push_back(i == 'B' ? 1 : 0);
    }
}

int f(int v, int len, int prv) {
    if (v == n) return 1;
    //cout << v << ' ' << len << ' ' << prv << '\n';
    if (a[0][v] && a[1][v]) {
        return f(v + 1, len + 1, prv);
    }
    else {
        int now = (a[0][v] ? 0 : 1);
        //cout << now << '\n';
        if ((len & 1) && (prv == -1 || now != prv)) return f(v + 1, 0, now);
        if (!(len & 1) && (prv == -1 || now == prv)) return f(v + 1, 0, now);
        return 0;
    }
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int tc; cin >> tc;
	FOR(tt, 1, tc + 1) {
        init();

        input();    

        int st = -1;
        for (int i = 0; i < n; i++) {
            if (a[0][i] && a[1][i]) continue;
            st = i; break;
        }

        if (st == -1) {
            cout << "YES\n";
            continue;
        }

        cout << (f(st, 0, -1) ? "YES" : "NO") << '\n';
	}

	return 0;
}