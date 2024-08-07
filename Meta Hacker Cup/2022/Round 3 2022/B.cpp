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

struct Node {
    vector<int> nxt;
};

int n;
ll m[101], dp[101][101];
vector<Node> trie[101];

void init() {
    for (int i = 0; i < 101; i++) {
        trie[i].clear();
        memset(dp[i], -1, sizeof(dp[i]));
    }
}

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> m[i];
        trie[i].resize(m[i] + 1);

        for (int j = 1; j <= m[i]; j++) 
            trie[i][j].nxt.resize(26);

        for (int j = 2; j <= m[i]; j++) {
            int p; char c;
            cin >> p >> c;
            trie[i][p].nxt[c - 'a'] = j;
        }
    }
}

ll f(const vector<Node>& t1, int v1, const vector<Node>& t2, int v2) {
    ll ret = 1;
    for (int i = 0; i < 26; i++) {
        if (t1[v1].nxt[i] > 0 && t2[v2].nxt[i] > 0) {
            ret += f(t1, t1[v1].nxt[i], t2, t2[v2].nxt[i]);
        }
    }
    return ret;
}

ll ff(int i, int j) {
    ll& ret = dp[i][j];
    if (ret != -1) return ret;
    else return ret = f(trie[i], 1, trie[j], 1);
}

ll f2(const vector<Node>& t1, int v1, const vector<Node>& t2, int v2, const vector<Node>& t3, int v3) {
    ll ret = 1;
    for (int i = 0; i < 26; i++) {
        if (t1[v1].nxt[i] > 0 && t2[v2].nxt[i] > 0 && t3[v3].nxt[i] > 0) {
            ret += f2(t1, t1[v1].nxt[i], t2, t2[v2].nxt[i], t3, t3[v3].nxt[i]);
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

        init();

        input();

        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                for (int k = j + 1; k <= n; k++) {
                    ans += m[i] + m[j] + m[k];
                    ans -= ff(i, j);
                    ans -= ff(i, k);
                    ans -= ff(j, k);
                    ans += f2(trie[i], 1, trie[j], 1, trie[k], 1);
                }
            }
        }

        cout << ans << '\n';
	}

	return 0;
}