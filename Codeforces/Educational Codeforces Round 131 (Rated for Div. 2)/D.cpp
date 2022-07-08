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

struct lridx {
    int l, r, idx;
    bool operator<(const lridx& rhs) const {
        if (r ^ rhs.r) return r < rhs.r;
        return l < rhs.l;
    }
};

int n;

int lb(int x, int idx) {
    int l = 1, r = n;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (idx / mid <= x) r = mid;
        else l = mid + 1;
    }
    return l;
}

int rb(int x, int idx) {
    int l = 1, r = n;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (idx / mid < x) r = mid - 1;
        else l = mid;
    }
    return l;
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
        cin >> n;

        vt<int> a(n + 1);
        FOR(i, 1, n + 1) cin >> a[i]; 

        //cout << '\n';
        //vt<lridx> res(n);
        vt<vt<pii>> b(n + 1);
        FOR(i, 1, n + 1) {
            b[lb(a[i], i)].push_back({ rb(a[i], i), i });
            //res[i - 1].l = lb(a[i], i);
            //res[i - 1].r = rb(a[i], i);
            //res[i - 1].idx = i;
            //cout << res[i - 1].l << ' ' << res[i - 1].r << ' ' << res[i - 1].idx << '\n';
        }
        //cout << '\n';

        //sort(all(res));

        priority_queue<pii> pq;

        vt<int> ans(n + 1);
        FOR(i, 1, n + 1) {
            EACH(j, b[i]) pq.push({ -j.fr, j.sc });

            ans[pq.top().sc] = i;
            pq.pop();
        }
        /*EACH(i, res) {
            ans[i.idx] = ++cnt;
            assert(i.l <= cnt && cnt <= i.r);
        }*/
        
        FOR(i, 1, n + 1) cout << ans[i] << ' ';
        cout << '\n';
    }

	return 0;
}