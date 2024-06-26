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

struct Query {
    int idx; ll x;
};

int n, q;
vt<ll> a;

vt<Query> query;
vt<pll> cc;
vt<ll> cc2;
vt<int> cnt, cnt2, prv, prv2;

void naive() {
    while (q--) {
        int idx; ll x;
        cin >> idx >> x;

        a[idx] = x;

        bool isD = (a[2] > a[1]), isR = (a[2] % a[1] == 0);

        FOR(i, 3, n + 1) {
            if (a[i] - a[i - 1] != a[i - 1] - a[i - 2]) isD = 0;
            if (a[i] % a[i - 1] || (a[i] / a[i - 1] != a[i - 1] / a[i - 2])) isR = 0;
        }

        if (isD) cout << "+\n";
        else if (isR) cout << "*\n";
        else cout << "?\n";
    }
}

void pre() {
    vt<ll> b = a;
    EACH(i, query) {
        b[i.idx] = i.x;

        if (b[2] > b[1])
            cc.push_back({ b[1], b[2] - b[1] });
        cc2.push_back(b[1]);
    }

    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());

    sort(all(cc2));
    cc2.erase(unique(all(cc2)), cc2.end());

    cnt.resize(sz(cc));
    cnt2.resize(sz(cc2));

    prv.resize(n + 1, -1);
    prv2.resize(n + 1, -1);
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    cin >> n >> q;

    a.resize(n + 1);
    FOR(n) cin >> a[i + 1];

    if (n <= 100) {
        naive();
        return 0;
    }

    // offline query
    query.resize(q);
    EACH(i, query) 
        cin >> i.idx >> i.x;

    pre();

    EACH(i, query) {
        if (prv[i.idx] != -1) {
            cnt[prv[i.idx]]--;
        }
        if (prv2[i.idx] != -1) {
            cnt2[prv[i.idx]]--;
        }

        if (i.idx == 1) {

        }
        else {
            if ((i.x - a[1]) % (i.idx - 1)) {
                a[i.idx] = i.x;
                prv[i.idx] = -1;
                cout << "?\n";
                continue;
            }

            ll d = (i.x - a[1]) / (i.idx - 1);

            int idx = lower_bound(all(cc), pll(a[1], d)) - cc.begin();
            if (idx == sz(cc) || cc[idx] != pll(a[1], d)) {
                a[i.idx] = i.x;
                prv[i.idx] = -1;
                cout << "?\n";
                continue;
            }

            a[i.idx] = i.x;
            prv[i.idx] = idx;
            cnt[idx]++;            
        
            if (cnt[idx] == n - 1) {
                cout << "+\n";
                continue;
            }
        }

        
    }

	return 0;
}