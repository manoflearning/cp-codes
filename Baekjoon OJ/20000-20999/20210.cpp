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

int isN(char x) {
    return '0' <= x && x <= '9';
}

void split(string a, vt<string>& aa) {
    string s;
    FOR(sz(a)) {
        if (!isN(a[i])) {
            if (sz(s)) aa.push_back(s);
            s.clear();
            s.push_back(a[i]);
            aa.push_back(s);
            s.clear();
        }
        else s.push_back(a[i]);
    }
    if (sz(s)) aa.push_back(s);
}

bool cmp(string a, string b) {
    vt<string> aa, bb;

    split(a, aa);
    split(b, bb);

    FOR(min(sz(aa), sz(bb))) {
        string s1 = aa[i], s2 = bb[i];
        int bit1 = isN(s1[0]);
        int bit2 = isN(s2[0]);
        
        if (bit1 != bit2) {
            if (bit1) return 1;
            else return 0;
        }

        if (bit1) {
            int s1Small = (sz(s1) < sz(s2)), s2Small = (sz(s1) > sz(s2));
            if (sz(s1) < sz(s2)) {
                string s3;
                FOR(sz(s2) - sz(s1)) s3.push_back('0');
                s3 += s1;
                s1 = s3;
            }
            if (sz(s1) > sz(s2)) {
                string s3;
                FOR(sz(s1) - sz(s2)) s3.push_back('0');
                s3 += s2;
                s2 = s3;
            }
            if (s1 == s2) {
                if (s1Small) return 1;
                if (s2Small) return 0;
                continue;
            }
            return s1 < s2;
        }
        else {
            int v1 = 0, v2 = 0;
            if ('a' <= s1[0] && s1[0] <= 'z') v1 = (s1[0] - 'a') * 2 + 1;
            else v1 = (s1[0] - 'A') * 2;
            if ('a' <= s2[0] && s2[0] <= 'z') v2 = (s2[0] - 'a') * 2 + 1;
            else v2 = (s2[0] - 'A') * 2;
            if (v1 == v2) continue;
            return v1 < v2;
        }
    }
    return sz(aa) < sz(bb);
}

int n;
vt<string> a;

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
    a.resize(n);
    EACH(i, a) cin >> i;

    sort(all(a), cmp);

    EACH(i, a) cout << i << '\n';

	return 0;
}