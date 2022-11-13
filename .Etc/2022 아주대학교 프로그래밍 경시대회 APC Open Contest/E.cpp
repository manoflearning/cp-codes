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

int n;
ll a[111];

map<pair<pii, ll>, int> dp;

int f(int v, int h, int sum) {
    auto it = dp.find({ { v, h }, sum });
    if (it != dp.end()) return it->sc;
    if (v == n + 1) return (sum == 0 ? 0 : INF);

    dp.insert({ { { v, h }, sum }, 0 });
    int& ret = dp.find({ { v, h }, sum })->sc;
    
    ret = INF;
    int nsum = sum - h;
    if (nsum >= 0) {
        if (h >= 2) ret = min(ret, f(v + 1, h - 1, nsum));
        ret = min(ret, f(v + 1, h, nsum));
        ret = min(ret, f(v + 1, h + 1, nsum));
    }
    ret += abs(h - a[v]);
    
    return ret;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n;
    FOR(n) cin >> a[i + 1];

    if (n == 1) {
        cout << 0;
        return 0;
    }

    int sum = 0;
    FOR(i, 1, n + 1) sum += a[i];

    int ans = INF;
    for (int i = 1; i <= min(1000000, sum); i++) {
        ans = min(ans, f(1, i, sum));
    }

    cout << ans / 2;

	return 0;
}

/*#include <bits/stdc++.h>
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
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int n; cin >> n;
    vt<ll> a(n);
    EACH(i, a) cin >> i;

    int sum = 0, ans = 0;
    for (int i = 0; i + 1 < n; i++) {
        if (abs(a[i] - a[i + 1]) <= 1) continue;

        if (abs(a[i] - a[i + 1]) & 1) {
            if (a[i] > a[i + 1]) {
                int diff = (a[i] - a[i + 1]) / 2;
                a[i] -= diff, a[i + 1] += diff;
                ans += diff;
            }
            else {
                int diff = (a[i + 1] - a[i]) / 2;
                a[i] += diff, a[i + 1] -= diff;
                ans += diff;
            }
        } 
        else {
            if (a[i] > a[i + 1]) {
                int diff = (a[i] - a[i + 1]) / 2;
                a[i] -= diff, a[i + 1] += diff;
                ans += diff;
            }
            else {
                int diff = (a[i + 1] - a[i]) / 2;
                a[i] += diff, a[i + 1] -= diff;
                ans += diff;
            }

            for (int j = i + 1; j < n; j++) {
                if (j + 1 < n && a[j + 1] - a[j] >= 2) { a[j]++; break; }
                if (a[j - 1] - a[j] >= 2) { a[j]++; break; }
            }
        }
    }

    cout << ans - sum / 2;

	return 0;
}*/