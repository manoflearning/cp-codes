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

struct lmid {
    int l, mid;
    bool operator<(const lmid& rhs) const {
        return mid > rhs.mid;
    }
};

int n;
string s;
vt<int> p;

void init() {
    p.clear();
}

void manacher() {
    n = sz(s);
    s.resize(n << 1 | 1);
    p.resize(n << 1 | 1);

    for (int i = n - 1; i >= 0; i--) {
        s[i << 1 | 1] = s[i];
        s[i << 1] = '#';
    }
    n <<= 1;
    s[n++] = '#';

    int r = -1, c = -1;
    for (int i = 0; i < n; i++) {
        if (i <= r) p[i] = min(r - i, p[2 * c - i]);
        else p[i] = 0;

        while (1) {
            if (i - p[i] - 1 < 0 || i + p[i] + 1 >= n) break;
            if (s[i - p[i] - 1] != s[i + p[i] + 1]) break;
            p[i]++;
        }

        if (r < i + p[i]) {
            r = i + p[i], c = i;
        }
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

		cin >> s;

        manacher();

        int ans = 0;
        set<lmid> st;
        for (int i = n - 1; i >= 0; i--) {
            if (s[i] == '#' && p[i] >= 4) {
                int c = i, r = i + p[i];
                int mid = (c + r) >> 1;

                while (sz(st)) {
                    auto it = st.lower_bound({ 0, mid });
                    if (it == st.end()) break;
                    if (it->l <= c) break;
                    st.erase(it); 
                }

                if (sz(st)) {
                    auto it = st.lower_bound({ 0, mid });
                    if (it != st.end()) {
                        int r2 = 2 * it->mid - c;
                        ans = max(ans, min(r, r2) - c);
                    }
                }
            }

            if (s[i] == '#' && p[i] >= 2) 
                st.insert({ i - p[i] / 2 * 2, i });
        }

        cout << ans << '\n';
	}

	return 0;
}