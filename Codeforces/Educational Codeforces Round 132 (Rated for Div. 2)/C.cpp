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

int RBS(const string& s) {
    int stk = 0;
    EACH(i, s) {
        if (i == '(') stk++;
        else {
            if (stk > 0) stk--;
            else return 0;
        }
    }
    return stk == 0;
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
    FOR(tt, 1, tc + 1) {
        string s; cin >> s;
        
        if (sz(s) & 1) {
            cout << "NO\n";
            continue;
        }

        int cntq = 0;
        EACH(i, s) if (i == '?') cntq++;

        if (cntq == 0 && RBS(s)) {
            cout << "YES\n";
            continue;
        }
        if (cntq == 1) {
            int cntl = 0, cntr = 0;
            EACH(i, s) {
                if (i == '(') cntl++;
                else if (i == ')') cntr++;
            }
            EACH(i, s) {
                if (i == '?') {
                    if (cntl < cntr) i = '(';
                    else i = ')';
                }
            }

            if (RBS(s)) cout << "YES\n";
            else cout << "NO\n";

            continue;
        }

        int n = sz(s);
        string s1 = s, s2 = s;

        int cntl = 0, cntr = 0;
        EACH(i, s1) {
            if (i == '(') cntl++;
            else if (i == ')') cntr++;
        }

        EACH(i, s1) {
            if (i == '?') {
                if (cntl < n / 2) i = '(', cntl++;
                else i = ')', cntr++;
            }
        }

        cntl = 0, cntr = 0;
        EACH(i, s2) {
            if (i == '(') cntl++;
            else if (i == ')') cntr++;
        } 

        int bit = 1;
        EACH(i, s2) {
            if (i == '?') {
                if (cntl < n / 2 - 1) i = '(', cntl++;
                else if (cntl == n / 2 - 1 && bit) i = ')', cntr++, bit = 0;
                else if (cntl == n / 2 - 1 && !bit) i = '(', cntl++;
                else i = ')', cntr++;
            }
        }

        if (s1 == s2 && RBS(s1)) cout << "YES\n";
        else if (RBS(s1) && !RBS(s2)) cout << "YES\n";
        else cout << "NO\n";
    }

	return 0;
}

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
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

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
    FOR(tt, 1, tc + 1) {
        string s; cin >> s;

        // 만약 문자열의 길이가 홀수라면 언제나 RBS를 만들 수 없다.
        if (sz(s) & 1) {
            cout << "NO\n";
            continue;
        }

        int n = sz(s);

        string s2 = s;
        int cnt1 = 0, cnt0 = 0;
        EACH(i, s2) {
            if (i == '(') cnt1++;
            else if (i == ')') cnt0++;
        }

        // 만약 '('나 ')'의 개수가 n / 2 이상이라면 언제나 RBS를 만들 수 없다.
        if (cnt1 > n / 2 || cnt0 > n / 2) {
            cout << "NO\n";
            continue;
        }

        EACH(i, s2) {
            if (i == '?') {
                if (cnt1 < n / 2) i = '(', cnt1++;
                else i = ')';
            }
        }

        int stk = 0;
        int bit = 1;
        EACH(i, s2) {
            if (i == '(') stk++;
            else if (i == ')') {
                if (stk > 0) stk--;
                else { bit = 0; break; }
            }
        }

        // 최적으로 배치한 상태가 RBS가 아니다.
        if (!bit) {
            cout << "NO\n";
            continue;
        }

        // 이제 언제나 RBS를 만들 수 있음이 보장된다
        // 가능한 RBS가 하나인지만 살피면 됨.
        cnt1 = 0, cnt0 = 0;
        EACH(i, s) {
            if (i == '(') cnt1++;
            else if (i == ')') cnt0++;
        }

        int bit2 = 0;
        EACH(i, s) {
            if (i == '?') {
                if (cnt1 < n / 2 - 1) i = '(', cnt1++;
                else if (cnt1 == n / 2 - 1 && !bit2) i = ')', bit2 = 1;
                else if (cnt1 == n / 2 - 1 && bit2) i = '(', cnt1++;
                else i = ')';
            }
        }

        bit = 1;
        EACH(i, s) {
            if (i == '(') stk++;
            else if (i == ')') {
                if (stk > 0) stk--;
                else { bit = 0; break; }
            }
        }

        if (bit) cout << "YES\n";
        else cout << "NO\n";
    }

	return 0;
}*/