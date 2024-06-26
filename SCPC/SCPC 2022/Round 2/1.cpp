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

struct xidx {
    ll x; int idx;
    bool operator<(const xidx& rhs) const {
        return x > rhs.x;
    }
};

int main() {
	#ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
	//freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	//freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int tc; cin >> tc;
    FOR(tt, 1, tc + 1) {
        cout << "Case #" << tt << '\n';

        int n; ll k;
        cin >> n >> k;

        priority_queue<xidx> pq;
        ll minCnt = 0;
        
        FOR(i, n) {
            ll x; cin >> x;
            if (x < k) {
                pq.push({ x, i });
                minCnt = max(minCnt, k - x);
            }
        }

        if (sz(pq) == 0) {
            cout << "0 0\n";
            continue;
        }
        if (sz(pq) == 1) {
            cout << minCnt << ' ' << minCnt << '\n';
            continue;
        }

        ll minCost = 0;
        while (1) {
            xidx p = pq.top();
            pq.pop();

            if (p.x == pq.top().x) {
                xidx q = pq.top();
                pq.pop();

                if (sz(pq)) {
                    minCost += (pq.top().x - p.x) * (abs(p.idx - q.idx) + 1);

                    xidx r = pq.top();
                    pq.pop();

                    pq.push({ r.x, min({ p.idx, q.idx, r.idx })});
                    pq.push({ r.x, max({ p.idx, q.idx, r.idx })});
                }
                else {
                    minCost += (k - p.x) * (abs(p.idx - q.idx) + 1);
                    break;
                }
            }
            else {
                minCost += pq.top().x - p.x;
                pq.push({ pq.top().x, p.idx });
            }
        }

        cout << minCnt << ' ' << minCost << '\n';
    }

	return 0;
}