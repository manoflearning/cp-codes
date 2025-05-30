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

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

ll ans1 = 0, ans2 = 0;

void cal(ll len) {
    ans1 += len;

    ll cnt = len / 5;
    ans2 += cnt / 4;
    cnt %= 4;
    if (cnt) ans2++;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int n; cin >> n;
    stack<ll> stk;

    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        x -= 20;
        x /= 2;
        
        while (!stk.empty() && x <= stk.top()) {
            ll y = stk.top();
            stk.pop();
            cal(y - max(x, (stk.empty() ? 0 : stk.top())));
        }
        stk.push(x);
    }

    while (!stk.empty()) {
        ll y = stk.top();
        stk.pop();
        cal(y - (stk.empty() ? 0 : stk.top()));
    }

    cout << ans1 * 4 << ' ' << ans2 * 4;

	return 0;
}