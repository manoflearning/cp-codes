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

int n, k;
vt<int> a, b;

void input() {
    cin >> n >> k;
    a.resize(n);
    b.resize(n);
    EACH(i, a) cin >> i;
    EACH(i, b) cin >> i;
}

vector<int> getpi(const vt<int>& P) {
	vector<int> pi(sz(P));
	for (int i = 1, j = 0; i < sz(P); i++) {
		while (j > 0 && P[i] != P[j]) j = pi[j - 1];

		if (P[i] == P[j]) pi[i] = ++j;
	}
	return pi;
}

vector<int> kmp(const vt<int>& T, const vt<int>& P) {
	vector<int> ret;

	vector<int> pi = getpi(P);

	for (int i = 0, j = 0; i < sz(T); i++) {
		while (j > 0 && T[i] != P[j]) j = pi[j-1];
		if (T[i] == P[j]) {
			if (j == sz(P) - 1) {
				ret.push_back(i - (sz(P) - 1));
				j = pi[j];
			}
			else ++j;
		}
	}

	return ret;
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
		cout << "Case #" << tt << ": ";

        input();

        FOR(n - 1) a.push_back(a[i]);

        vector<int> ans = kmp(a, b);

        if (ans.empty()) {
            cout << "NO\n";
            continue;
        }

        if (k == 0) {
            if (ans[0] == 0) cout << "YES\n";
            else cout << "NO\n";
            continue;
        }

        if (sz(ans) >= 2) {
            cout << "YES\n";
            continue;
        }

        if (n == 2) {
            if (ans[0] == 0) {
                if (k & 1) cout << "NO\n";
                else cout << "YES\n";
            }
            else {
                if (k & 1) cout << "YES\n";
                else cout << "NO\n";
            }
            continue;
        }

        if (k == 1) {
            if (ans[0] == 0) cout << "NO\n";
            else cout << "YES\n";
            continue;
        }

        cout << "YES\n";
	}

	return 0;
}