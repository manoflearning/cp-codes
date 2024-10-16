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

const double EPS = 1e-8;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

ll a, b, c, d;
ll a2, b2, c2;

double cal(double x) {
    return a * pow(x, 3) + b * pow(x, 2) + c * x + d;
}

double bs(double l, double r) {
    int bitl = (cal(l) < 0);

    if (bitl) {
        while (r - l >= 0.00001) {
            double mid = (l + r) / 2;
            if (cal(mid) < 0) l = mid + 0.00001;
            else r = mid;
        }
        return l;
    }
    else {
        while (r - l >= 0.00001) {
            double mid = (l + r) / 2;
            if (cal(mid) > 0) l = mid + 0.00001;
            else r = mid;
        }
        return l;
    }
}

pair<double, double> cal2() {
    double ret1 = (double)(-b2 - sqrt(pow(b2, 2) - 4 * a2 * c2)) / (2 * a2);
    double ret2 = (double)(-b2 + sqrt(pow(b2, 2) - 4 * a2 * c2)) / (2 * a2);
    return { ret1, ret2 };
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

    cout << fixed;
    cout.precision(4);

    int tc; cin >> tc;
	while (tc--) {
        cin >> a >> b >> c >> d;
        if (a < 0) a *= -1, b *= -1, c *= -1, d *= -1;

        a2 = 3 * a;
        b2 = 2 * b;
        c2 = c;

        pair<double, double> res = cal2();
        //cout << res.fr << ' ' << res.sc << '\n';
        int bit1 = (cal(res.fr) < 0 ? 0 : (cal(res.fr) < EPS ? 1 : 2));
        int bit2 = (cal(res.sc) < 0 ? 0 : (cal(res.sc) < EPS ? 1 : 2));
        
        // 삼차방정식에 극대, 극솟값이 존재하지 않음
        if (res.sc - res.fr < EPS) {
            cout << bs(-1010101, 1010101);
        }
        // 중근 존재
        else if (bit1 == 1 || bit2 == 1) {
            if (bit1 == 1) {
                cout << res.fr << ' ' << bs(res.fr + 0.0001, 1010101);
            }
            if (bit2 == 1) {
                cout << bs(-1010101, res.sc - 0.0001) << ' ' << res.sc;
            }
        }
        // 일반적인 케이스
        else {
            if (bit1 == bit2) {
                cout << bs(-1010101, 1010101);
            }
            else {
                cout << bs(-1010101, res.fr) << ' ' << bs(res.fr, res.sc) << ' ' << bs(res.sc, 1010101);
            }
        }
        cout << '\n';
    }
    
	return 0;
}