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

const int MAX = 1 << 19;

struct MergeSortTree {
    vt<int> t[MAX << 1];
    
    void build(const vt<int>& arr) {
        for (int i = 0; i < sz(arr); i++)
            t[i + MAX + 1].push_back(arr[i]);

        for (int i = MAX - 1; i >= 1; i--) {
            t[i].resize(sz(t[i << 1]) + sz(t[i << 1 | 1]));
            merge(all(t[i << 1]), all(t[i << 1 | 1]), t[i].begin());
        }
    }

    vt<int> query(int l, int r, int n = 1, int nl = 0, int nr = MAX - 1) {
        if (r < nl || nr < l) return { };
        if (l <= nl && nr <= r) {
            if (nl == nr) return { t[n][0] };
            else {
                int mid = (nr - nl + 1) >> 1;
                if (t[n][mid - 1] == t[n][mid]) return { t[n][mid] };
                else return { };
            }
        }

        int mid = (nl + nr) >> 1;
        vt<int> res1 = query(l, r, n << 1, nl, mid);
        vt<int> res2 = query(l, r, n << 1 | 1, mid + 1, nr);
        
        vt<int> ret;
        EACH(i, res1) ret.push_back(i);
        EACH(i, res2) ret.push_back(i);
        return ret;
    }
}mstree;

int n, c;
vt<int> arr, arr2[10101];

int main() {
	#ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> c;
    vt<int> arr(n);
    EACH(i, arr) cin >> i;

    mstree.build(arr);
    FOR(n) {
        arr2[arr[i]].push_back(i + 1);
    }

    int q; cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;

        vt<int> res = mstree.query(l, r);
        int ans = -1;
        EACH(i, res) {
            int cnt = upper_bound(all(arr2[i]), r) - lower_bound(all(arr2[i]), l);
            if (cnt > (r - l + 1) / 2) {
                ans = i;
                break;
            }
        }

        if (ans == -1) cout << "no\n";
        else cout << "yes " << ans << '\n';
    }

	return 0;
}