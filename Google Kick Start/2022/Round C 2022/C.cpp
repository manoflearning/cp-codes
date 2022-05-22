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

struct ant {
    ll d, p;
    int num;
    bool operator<(const ant& rhs) const {
        return p < rhs.p;
    }
};

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

    FOR(t, 1, tc + 1) {
        cout << "Case #" << t << ": ";

        ll n, l;
        cin >> n >> l;

        vt<ant> a(n);
        FOR(i, n) cin >> a[i].p >> a[i].d;
        FOR(i, n) a[i].num = i + 1;

        sort(all(a));

        vt<int> p1, p0;

        p1.push_back(0);
        FOR(i, n) {
            if (a[i].d == 1) p1.push_back(a[i].p);
            if (a[i].d == 0) p0.push_back(a[i].p);
        }
        p0.push_back(l);

        priority_queue<pii> pq;

        FOR(i, n) {
            int l = lower_bound(all(p1), a[i].p) - p1.begin();
            //if (p1[l] == a[i].p) l--;
            int r = p0.end() - upper_bound(all(p0), a[i].p);

            int idx1 = lower_bound(all(p1), a[i].p) - p1.begin() - 1;
            //if (p1[idx1 + 1] == a[i].p) idx1--;
            int idx0 = upper_bound(all(p0), a[i].p) - p0.begin();
            
            int xl = min(l, r), xr = min(l, r);
            if (a[i].d == 0 && l <= r) xr--;
            if (a[i].d == 1 && l >= r) xl--;
            
            ll w = (xr > 0 ? p0[idx0 + xr - 1] : a[i].p) - (xl > 0 ? p1[idx1 - xl + 1] : a[i].p);
            /*if (a[i].num == 2) {
                cout << "XXX\n";
                cout << l << ' ' << r << '\n';
                cout << xl << ' ' << xr << '\n';
                cout << idx1 << ' ' << idx0 << '\n';
                cout << p0[idx0 + xr - 1] << ' ' << p1[idx1 - xl + 1] << '\n';
                cout << "YYY\n";
            }*/
            pq.push({ -w, -a[i].num });
        }

        while (sz(pq)) {
            cout << -pq.top().sc << ' ';
            //cout << -pq.top().fr << ' ' << -pq.top().sc << '\n';
            pq.pop();
        }
        cout << '\n';
    }

	return 0;
}