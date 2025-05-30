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

int n;
vector<string> ans;
string s;

void bt(int x, ll val, ll op, ll prv) {
    if (x == n + 1) {
        if (val + op * prv == 0) {
            ans.push_back(s);
            //cout << val << ' ' << prv << '\n';
            //cout << s << '\n';
        }
        return;
    }

    s.push_back('+');
    s.push_back(x + '0');
    bt(x + 1, val + op * prv, 1, x);
    s.pop_back();
    s.pop_back();

    s.push_back('-');
    s.push_back(x + '0');
    bt(x + 1, val + op * prv, -1, x);
    s.pop_back();
    s.pop_back();

    s.push_back(' ');
    s.push_back(x + '0');
    bt(x + 1, val, op, prv * 10 + x);
    s.pop_back();
    s.pop_back();
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
        ans.clear();
		cin >> n;
        s.push_back('1');
        bt(2, 0, 1, 1);
        sort(all(ans));
        for (auto& i : ans)
            cout << i << '\n';
        cout << '\n';
        s.pop_back();
	}

	return 0;
}