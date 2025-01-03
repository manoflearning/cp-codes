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

int n, m;
vt<pair<string, string>> a[26 * 26 + 26];

inline int Hash(char x, char y) {
    return (x - 'a') * 26 + (y - 'a');
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        string s, sub;
        cin >> s;
        for (int j = 1; j + 1 < sz(s); j++)
            sub.push_back(s[j]);

        sort(all(sub));
        
        if (sz(s) >= 2) 
            a[Hash(s[0], s.back())].push_back({ sub, s });
    }

    for (int i = 0; i < 26 * 26 + 26; i++) {
        sort(all(a[i]));
    }

    cin >> m;
    vt<string> ans;
    for (int k = 0; k < m; k++) {
        string s; cin >> s;

        string sub;
        for (int i = 1; i + 1 < sz(s); i++) {
            sub.push_back(s[i]);
        }
        
        sort(all(sub));

        if (sz(s) == 1) {
            ans.push_back(s);
        }
        else {
            pair<string, string> du;
            du.fr = sub;
            int num = Hash(s[0], s.back());
            
            int idx = lower_bound(all(a[num]), du) - a[num].begin();
            ans.push_back(a[num][idx].sc);
        }
    }

    for (auto& i : ans)
        cout << i << ' ';

	return 0;
}