#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
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

const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

struct xy {
    int x, y;
};

struct idxx {
    int idx, x;
};

bool operator<(const idxx& a, const idxx& b) {
    return a.x < b.x;
}

int n;
vt<xy> a;
vt<int> b;
vt<idxx> yy[404040];
string s;

void input() {
    cin >> n;
    a.resize(n);
    EACH(i, a) {
        cin >> i.x >> i.y;
        b.push_back(i.x);
        b.push_back(i.y);
    }
    cin >> s;
}

int main() {
	#ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
    freopen("/Users/jeongwoo-kyung/Programming/PS-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/PS-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    input();

    sort(all(b));
    b.erase(unique(all(b)), b.end());

    FOR(n) {
        a[i].x = lower_bound(all(b), a[i].x) - b.begin();
        a[i].y = lower_bound(all(b), a[i].y) - b.begin();
        yy[a[i].y].push_back({ i, a[i].x });
    }

    int ans = 0;
    FOR(404040) {
        sort(all(yy[i]));
        int isR = 0;
        EACH(j, yy[i]) {
            if (s[j.idx] == 'R') isR = 1;
            if (s[j.idx] == 'L' && isR) ans = 1;
        }
    }

    if (ans) cout << "Yes";
    else cout << "No";

	return 0;
}