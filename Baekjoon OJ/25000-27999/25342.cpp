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

/*const int MAX = 1e5;

bool isPrime[MAX + 1];
vector<int> prime(1, 2);

void getPrime() {
	fill(isPrime + 2, isPrime + MAX + 1, 1);

	for (ll i = 4; i <= MAX; i += 2)
		isPrime[i] = 0;
	for (ll i = 3; i <= MAX; i++) {
		if (isPrime[i]) prime.push_back(i);
		for (ll j = i * i; j <= MAX; j += i * 2)
			isPrime[j] = 0;
	}
}*/

ll gcd(ll a, ll b) {
	if (b == 0) return a;
	else return gcd(b, a % b);
}

ll lcm(ll a, ll b) {
	return a * b / gcd(a, b);
}

ll lcm2(ll a, ll b, ll c) {
    return lcm(lcm(a, b), c);
}

ll cal(int n) {
    ll ans = 0;
    ans = max(ans, lcm2(n, n - 1, n - 2));
    ans = max(ans, lcm2(n, n - 1, n - 3));
    ans = max(ans, lcm2(n, n - 1, n - 4));
    ans = max(ans, lcm2(n, n - 2, n - 3));
    ans = max(ans, lcm2(n, n - 2, n - 4));
    ans = max(ans, lcm2(n, n - 3, n - 4));
    ans = max(ans, lcm2(n - 1, n - 2, n - 3));
    ans = max(ans, lcm2(n - 1, n - 2, n - 4));
    ans = max(ans, lcm2(n - 1, n - 3, n - 4));
    ans = max(ans, lcm2(n - 2, n - 3, n - 4));
    return ans;
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

	//getPrime();

    int tc; cin >> tc;
    while (tc--) {
        int n;
        cin >> n;    

        cout << cal(n) << '\n';
    }

    /*for (int n = 3; n <= 200; n++) {
        ll ans = 0;
        vt<int> res;
        for (ll i = 1; i <= n; i++) {
            for (ll j = i + 1; j <= n; j++) {
                for (ll k = j + 1; k <= n; k++) {
                    if (ans <= lcm(lcm(i, j), k)) {
                        ans = lcm(lcm(i, j), k);
                        res.clear();
                        res.push_back(i);
                        res.push_back(j);
                        res.push_back(k);
                    }
                }
            }
        }
        //cout << n << ' ' << ans << '\n';
        if (ans != cal(n)) {
            cout << n << ' ' << ans << ' ' << cal(n) << '\n';
            EACH(i, res) cout << i << ' ';
            cout << '\n' << '\n';
        }
    }*/

	return 0;
}