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

int n, q;
ll a[202020], pxor[202020];
ll psum[202020];
vt<ll> c;
vt<vt<int>> even, odd;

void cc() {
    for (int i = 0; i <= n; i++) {
        c.push_back(pxor[i]);
    }

    sort(c.begin(), c.end());
    c.erase(unique(all(c)), c.end());

    for (int i = 0; i <= n; i++) {
        pxor[i] = lower_bound(all(c), pxor[i]) - c.begin();
    }
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> q;
    FOR(n) cin >> a[i + 1];

    FOR(i, 1, n + 1) {
        pxor[i] = (a[i] ^ pxor[i - 1]);
        psum[i] = (a[i] + psum[i - 1]);
    }

    /*for (int i = 1; i <= n; i++) {
        cout << pxor[i] << ' ';
    }
    cout << '\n';*/

    cc();

    even.resize(sz(c));
    odd.resize(sz(c));

    for (int i = 0; i <= n; i++) {
        if (i & 1) odd[pxor[i]].push_back(i);
        else even[pxor[i]].push_back(i);
    }

    while (q--) {
        int l, r;
        cin >> l >> r;

        int len = (r - l + 1);

        if (len == 1 || len == 2) {
            if (psum[r] - psum[l - 1] == 0) cout << 0 << '\n';
            else cout << -1 << '\n';
        }
        else if (len == 3) {
            if (psum[r] - psum[l - 1] == 0) cout << 0 << '\n';
            else if (pxor[r] == pxor[l - 1]) cout << 1 << '\n';
            else cout << -1 << '\n';
        }
        else if (len >= 4) {
            if (psum[r] - psum[l - 1] == 0) cout << 0 << '\n';
            else if (pxor[r] == pxor[l - 1]) {
                if ((len & 1) || (a[l] == 0 || a[r] == 0)) cout << 1 << '\n';
                else {
                    int ans = 1;

                    if (l & 1) {
                        auto it = upper_bound(all(odd[pxor[l - 1]]), l);
                        if (it == odd[pxor[l - 1]].end()) ans = 0;
                        else if (*it > r) ans = 0;
                    }
                    else {
                        auto it = upper_bound(all(even[pxor[l - 1]]), l);
                        if (it == even[pxor[l - 1]].end()) ans = 0;
                        else if (*it > r) ans = 0;
                    }
                    
                    cout << (ans ? 2 : -1) << '\n';
                }
            }
            else cout << -1 << '\n';
        }
    }

	return 0;
}