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

int cal(vt<int>& cnt1, vt<int>& cnt3, int k) {
    int cnt = 0, prv = 0;
    FOR(i, 0, 26) {
        if (cnt == k || (prv && cnt > 0)) break;
        if (cnt1[i]) {
            cout << (char)(i + 'a');
            cnt1[i]--, cnt3[i]--;
            cnt++, i--;
        }
        else if (cnt3[i]) prv = 1;
    }
            
    int bit = 1;
    FOR(26) if (cnt1[i]) bit = 0;
    return bit;
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
        int n, m, k;
        cin >> n >> m >> k;

        string s1, s2;
        cin >> s1 >> s2;

        vt<int> cnt1(26), cnt2(26), cnt3(26);
        EACH(i, s1) cnt1[i - 'a']++, cnt3[i - 'a']++;
        EACH(i, s2) cnt2[i - 'a']++, cnt3[i - 'a']++;

        if (cnt1 < cnt2) swap(cnt1, cnt2);

        while (1) {
            if (cal(cnt1, cnt3, k)) break;
            if (cal(cnt2, cnt3, k)) break;
        }
        cout << '\n';
    }

	return 0;
}