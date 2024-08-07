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

int n, m;
deque<int> d, s, dg, sg;

int main() {
	#ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	cin >> n >> m;
    FOR(n) {
        int a, b;
        cin >> a >> b;
        d.push_back(a);
        s.push_back(b);
    }

    FOR(m) {
        if (i % 2 == 0) {
            dg.push_back(d.back());
            d.pop_back();
        }
        else {
            sg.push_back(s.back());
            s.pop_back();
        }

        if (d.empty()) {
            cout << "su";
            return 0;
        }
        if (s.empty()) {
            cout << "do";
            return 0;
        }

        // do 
        if ((sz(dg) && dg.back() == 5) || sz(sg) && sg.back() == 5) {
            while (sz(sg)) {
                d.push_front(sg.front());
                sg.pop_front();
            }
            while (sz(dg)) {
                d.push_front(dg.front());
                dg.pop_front();
            }
        }
        // su
        if (sz(dg) && sz(sg) && dg.back() + sg.back() == 5) {
            while (sz(dg)) {
                s.push_front(dg.front());
                dg.pop_front();
            }
            while (sz(sg)) {
                s.push_front(sg.front());
                sg.pop_front();
            }
        }

        if (d.empty()) {
            cout << "su";
            return 0;
        }
        if (s.empty()) {
            cout << "do";
            return 0;
        }
    }

    if (sz(d) < sz(s)) cout << "su";
    else if (sz(d) > sz(s)) cout << "do";
    else cout << "dosu";

	return 0;
}