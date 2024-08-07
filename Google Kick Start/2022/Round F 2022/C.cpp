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

struct qv {
    ll q, l, v;
    bool operator<(const qv& rhs) const {
        return v < rhs.v;
    }
};

ll d, n, x;
vt<qv> a, arr[202020];
vt<ll> c;

void init() {
    a.clear(); c.clear();
    FOR(202020) arr[i].clear();
}

void input() {
    cin >> d >> n >> x;
    a.resize(n);
    EACH(i, a)
        cin >> i.q >> i.l >> i.v;
}

void cc() {
    c.push_back(-INF);
    EACH(i, a) {
        c.push_back(i.l);
        c.push_back(i.l + 1);
    }

    sort(all(c));
    c.erase(unique(all(c)), c.end());

    EACH(i, a) {
        i.l = lower_bound(all(c), i.l) - c.begin();
        arr[i.l].push_back(i);
    }
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

        cc();

        priority_queue<qv> pq;

        ll ans = 0;
        for (int i = 1; i < sz(c); i++) {
            ll rem = -1;
            if (i == sz(c) - 1) rem = x * (d - c[i] + 1);
            else rem = x * (c[i + 1] - c[i]);

            while (sz(pq) && rem > 0) {
                ll q = pq.top().q, v = pq.top().v;
                pq.pop();
                //cout << c[i] << ' ' << q << ' ' << v << '\n';
                if (q <= rem) {
                    ans += q * v;
                    rem -= q;
                }
                else {
                    ans += rem * v;
                    pq.push({ q - rem, 0, v });
                    rem = 0;
                }
            }

            EACH(j, arr[i]) pq.push(j);

            //cout << c[i] << ' ' << ans << '\n';
        }

        cout << ans << '\n';
	}

	return 0;
}