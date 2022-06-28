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

int vi[10];

int bt(int idx, ll sum, const vt<ll>& b) {
    if (idx == 3) {
        int idx2 = lower_bound(all(b), sum) - b.begin();
        if (idx2 < sz(b) && b[idx2] == sum) return 1;
        else return 0;
    }

    int ret = 1;
    FOR(sz(b)) {
        if (vi[i]) continue;
        vi[i] = 1;
        ret &= bt(idx + 1, sum + b[i], b);
        vi[i] = 0;
    }
    //ret &= bt(idx + 1, sum, b);

    return ret;
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
        int n; cin >> n;
        vt<ll> a(n);
        EACH(i, a) cin >> i;

        int pCnt = 0, nCnt = 0, cnt0 = 0;
        vt<ll> b;
        EACH(i, a) {
            if (i > 0) {
                pCnt++;
                b.push_back(i);
            }
            if (i < 0) {
                nCnt++;
                b.push_back(i);
            }
            if (i == 0) cnt0++;
        }

        if (pCnt >= 3 || nCnt >= 3) {
            cout << "NO\n";
            continue;
        }

        // now pCnt <= 2 AND nCnt <= 2
        FOR(min(2, cnt0)) b.push_back(0);
        sort(all(b));
        if (bt(0, 0, b)) cout << "YES\n";
        else cout << "NO\n";

        /*if (pCnt < nCnt) {
            swap(pCnt, nCnt);
            swap(pa, na);
        }

        if (pCnt == 0 && nCnt == 0) {
            cout << "YES\n";
            continue;
        }
        if (pCnt == 1 && nCnt == 0) {
            cout << "YES\n";
            continue;
        }
        if (pCnt == 2 && nCnt == 0) {
            cout << "NO\n";
            continue;
        }

        if (pCnt == 1 && nCnt == 1) {
            if (pa[0] == na[0]) cout << "YES\n";
            else cout << "NO\n"; 
            continue;
        }
        if (pCnt == 2 && nCnt == 1) {
            
        }*/
    }

	return 0;
}