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

struct Node { ll a, b; };

ll n, m, k;
vector<Node> arr;

void input() {
    cin >> n >> m >> k;
    arr.resize(n);
    for (auto& i : arr)
        cin >> i.a >> i.b;
}

ll gcd(ll a, ll b) {
	if (b == 0) return a;
	else return gcd(b, a % b);
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();

    sort(all(arr), [&](const Node& lhs, const Node& rhs) {
        return lhs.b * rhs.a > rhs.b * lhs.a;
    });

    vector<Node> tmp;
    for (auto& i : arr) {
        if (tmp.empty()) {
            tmp.push_back(i);
            continue;
        }

        Node lhs = tmp.back(), rhs = i;
        if (lhs.b * rhs.a == rhs.b * lhs.a) {
            if (lhs.a + lhs.b < rhs.a + rhs.b) {
                tmp.pop_back();
                tmp.push_back(i);
            }
        }
        if (lhs.b * rhs.a > rhs.b * lhs.a) {
            if (lhs.a + lhs.b < rhs.a + rhs.b) {
                tmp.push_back(i);
            }
        }
    }
    arr = tmp;

    int now = 0;
    for (int d = 1; d <= m; d++) {
        while (now + 1 < sz(arr)) {
            ll B1 = arr[now].b - k * d, A1 = arr[now].a + k * d;
            ll B2 = arr[now + 1].b - k * d, A2 = arr[now + 1].a + k * d;
            
            if (B1 * A2 <= B2 * A1) now++;
            else break;
        }

        ll B = arr[now].b - k * d, A = arr[now].a + k * d;
        if (B == 0) cout << "0/0\n";
        else {
            ll g = gcd(A, B);
            B /= g, A /= g;
            if (A < 0) A *= -1, B *= -1;
            cout << B << '/' << A << '\n';
        }
    }

	return 0;
}