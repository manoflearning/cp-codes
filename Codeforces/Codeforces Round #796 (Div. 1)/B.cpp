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

int n, m;
vector<pll> edge;

ll query1(int idx) {
    cout << "? ";
    for (int i = 1; i <= m; i++) {
        cout << (char)('0' + (i == idx ? 1 : 0));
    }
    cout << endl;

    ll ret; cin >> ret;
    return ret;
}

int bit[505];
ll query2() {
    cout << "? ";
    for (int i = 1; i <= m; i++) {
        cout << (char)('0' + bit[i]);
    }
    cout << endl;

    ll ret; cin >> ret;
    return ret;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        ll w = query1(i);
        edge.push_back({ w, i });
    }

    sort(all(edge));
    ll ans = 0;
    for (auto& i : edge) {
        bit[i.sc] = 1;
        ll res = query2();
        if (ans + i.fr == res) ans = res;
        else bit[i.sc] = 0;
    }

    cout << "! " << ans << endl;

	return 0;
}