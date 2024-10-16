//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")

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

int a, b, c, d, cord;
string s, t;
vector<string> AB, BA;

void init() {
    a = b = c = d = cord = 0;
    s.clear(); t.clear();
    AB.clear(); BA.clear();
}

void input() {
    cin >> a >> b >> c >> d; 
    cin >> s;
}

bool condition() {
    int cntA = 0, cntB = 0;
    for (auto& c : s) {
        if (c == 'A') cntA++;
        if (c == 'B') cntB++;
    }
    return (cntA == a + c + d && cntB == b + c + d);
}

void cal() {
    if (sz(t) && t.front() == 'A' && t.back() == 'A') {
        cord += sz(t) / 2, a--;
    }
    if (sz(t) && t.front() == 'B' && t.back() == 'B') {
        cord += sz(t) / 2, b--;
    }
    if (sz(t) && t.front() == 'A' && t.back() == 'B') AB.push_back(t);
    if (sz(t) && t.front() == 'B' && t.back() == 'A') BA.push_back(t);
    t.clear();
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int tc; cin >> tc;
	for (int tt = 1; tt <= tc; tt++) {
        init();

		input();

        if (!condition()) {
            cout << "NO\n";
            continue;
        }

        //
        for (int i = 0; i < sz(s); i++) {
            if (0 < i && i + 1 < sz(s) && s[i] == s[i - 1] && s[i] == s[i + 1]) {
                cal();
                if (s[i] == 'A') a--;
                if (s[i] == 'B') b--;
            }
            else {
                if (sz(t) && t.back() == s[i]) cal();
                t.push_back(s[i]);
            }
        }
        cal();

        //
        sort(all(AB), [&](const string& lhs, const string& rhs) {
            return sz(lhs) > sz(rhs);
        });
        sort(all(BA), [&](const string& lhs, const string& rhs) {
            return sz(lhs) > sz(rhs);
        });

        int aandb = max(0, min(a, b));
        for (int l = 0; l < sz(AB); l++) {
            int r = aandb - (l + 1) - 1;
        }
        /*for (int i = 0; i < sz(AB); i++) {
            if (a <= 0 || b <= 0) {
                if (AB[i].front() == 'A') c -= sz(AB[i]) / 2;
                if (AB[i].front() == 'B') d -= sz(AB[i]) / 2;
            }
            else {
                cd += (sz(AB[i]) - 2) / 2;
                a--, b--;
            }
        }*/

        if (c > 0) {
            int tmp = min(cord, c);
            cord -= tmp, c -= tmp;
        }
        if (d > 0) {
            int tmp = min(cord, d);
            cord -= tmp, d -= tmp;
        }
        if (a > 0 && b > 0 && cord > 0) {
            int tmp = min({ a, b, cord });
            cord -= tmp, a -= tmp, b -= tmp;
        }
        
        if (a || b || c || d || cord) cout << "NO\n";
        else cout << "YES\n";
	}

	return 0;
}