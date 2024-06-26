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

ll a, p, x;
ll b, q, y;
ll c, r, z;
ll stB, enB;
ll stC, enC;

ll ans = 0, isInf = 0;
vt<pair<ll, pll>> facA;
vt<pll> facC, fac;

void init() {
    a = p = x = 0;
    b = q = y = 0;
    c = r = z = 0;
    stB = enB = 0;
    stC = enC = 0;

    ans = 0, isInf = 0;
    facA.clear();
    facC.clear();
    fac.clear();
}

void FacC(ll x) {
    for (ll i = 2; i * i <= x; i++) {
        int cnt = 0;
        while (x % i == 0) x /= i, cnt++;
        facC.push_back({ i, cnt });
    }
    if (x > 1) facC.push_back({ x, 1 });
}

void FacA() {
    for (int i = 0; i < sz(facC); i++) {
        ll xx = facC[i].fr, yy = facC[i].sc;

        ll qq = q, cnt = 0;
        while (qq % xx == 0) qq /= xx, cnt++;

        if (cnt == yy) {
            facA.push_back({ xx, { 0, yy } });
        }
        else facA.push_back({ xx, { yy, yy } });
    }
}

void cal() {
    ll cnt1 = min(r, stC - stB) / p + (min(r, stC - stB) % p ? 1 : 0);
    ll cnt2 = min(r, enB - enC) / p + (min(r, enB - enC) % p ? 1 : 0);

    cnt1 %= MOD, cnt2 %= MOD;
    ans = (ans + (cnt1 * cnt2) % MOD) % MOD;
}

void simul(int idx) {
    if (idx == sz(facA)) {
        p = 1;
        EACH(i, fac) {
            FOR(j, i.sc) p *= i.fr;
        }
        
        cal();
        return;
    }

    FOR(i, facA[idx].sc.fr, facA[idx].sc.sc + 1) {
        fac.push_back({ facA[idx].fr, i });
        simul(idx + 1);
        fac.pop_back();
    }
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
        init();

        cin >> b >> q >> y;
        cin >> c >> r >> z;

        if (r % q) {
            cout << 0 << '\n';
            continue;
        }

        stB = b, enB = b + q * (y - 1);
        stC = c, enC = c + r * (z - 1);

        if (stC < stB || enB < enC) {
            cout << 0 << '\n';
            continue;
        }

        // now stB <= stC AND enC <= enB
        if ((stC - stB) % q > 0) {
            cout << 0 << '\n';
            continue;
        }

        if (stC - r < stB || enB < enC + r) {
            cout << -1 << '\n';
            continue;
        }

        // lcm(p, q) = r 이어야 함.
        // 우리는 q, r을 알고 있으므로 가능한 p를 모두 구할 수 있음.
        // sqrt(x) 소인수분해로 구함.
        FacC(r);

        FacA();

        simul(0);

        if (isInf) cout << -1 << '\n';
        else cout << ans << '\n';
    }

	return 0;
}