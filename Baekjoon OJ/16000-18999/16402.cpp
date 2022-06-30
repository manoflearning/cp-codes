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

const int MAX = 1e4;

vector<int> p(MAX + 1, -1);
vector<int> winner(MAX + 1);

int find(int x) {
	if (p[x] < 0) return x;
	return p[x] = find(p[x]);
}

void merge(int a, int b) {
	int A = find(a), B = find(b);
	if (A == B) return;
	p[A] += p[B];
	p[B] = A;
}

int n, m;
vt<string> cc;

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
        string s1, s2, s3;
        cin >> s1 >> s2 >> s3;
        cc.push_back(s3);
    }

    sort(all(cc));

    FOR(MAX + 1) winner[i] = i;

    FOR(m) {
        string s1, s2, s3, s4, s5;
        cin >> s1 >> s2 >> s3 >> s4 >> s5;
        
        string sa, sb;
        EACH(i, s3) {
            if (i == ',') break;
            sa.push_back(i);
        }
        EACH(i, s5) {
            if (i == ',') break;
            sb.push_back(i);
        }

        int win = s5.back() - '0';
        
        int a = lower_bound(all(cc), sa) - cc.begin();
        int b = lower_bound(all(cc), sb) - cc.begin();
        if (find(a) ^ find (b)) {
            a = winner[find(a)];
            b = winner[find(b)];
        }

        merge(a, b);
        if (win == 1) winner[find(a)] = a;
        if (win == 2) winner[find(a)] = b;

        /*FOR(sz(cc)) {
            cout << i << ' ' << winner[find(i)] << '\n';
        }
        cout << '\n';*/
    }

    vt<string> ans;
    FOR(sz(cc)) {
        if (winner[find(i)] == i) {
            ans.push_back(cc[i]);
        }
    }

    cout << sz(ans) << '\n';
    EACH(i, ans) {
        cout << "Kingdom of ";
        cout << i << '\n';
    }

	return 0;
}