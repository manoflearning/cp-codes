#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

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
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

struct Node { 
    ll x, y; 
    bool operator<(const Node& rhs) const {
        return x * (rhs.x + rhs.y) < rhs.x * (x + y);
    }
    bool operator<=(const Node& rhs) const {
        return x * (rhs.x + rhs.y) <= rhs.x * (x + y);
    }
    bool operator==(const Node& rhs) const {
        return x * (rhs.x + rhs.y) == rhs.x * (x + y);
    }
};

int n, m, k;
vector<Node> a, b;
multiset<Node> c;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> m >> k;
    a.resize(n);
    b.resize(m);
    for (auto& i : a) cin >> i.x >> i.y;
    for (auto& i : b) cin >> i.x >> i.y;

    for (auto& i : a) {
        for (auto& j : b) {
            c.insert({ i.x + j.x, i.y + j.y });
            if (sz(c) > k) c.erase(c.begin());
        }
    }

    cout << fixed;
    cout.precision(9);

    /*for (auto& i : c) {
        cout << (double)i.x / (i.x + i.y) * 100 << '\n';
    }*/
    auto it = c.end();
    for (int i = 0; i < k; i++) it--;
    cout << (double)it->x / (it->x + it->y) * 100;
}