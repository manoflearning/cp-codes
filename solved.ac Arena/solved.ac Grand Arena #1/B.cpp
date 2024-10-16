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
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n, m;
vector<string> a, b;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    a.resize(n);
    for (auto& i : a) cin >> i;

    cin >> m;
    b.resize(m);
    for (auto& i : b) cin >> i;

    if (n == 1) {
        cout << b[0];
        return 0;
    }

    set<string> vi;
    for (auto& i : a) {
        if (i != "?") vi.insert(i);
    }

    char st = '*', en = '*';
    for (int i = 0; i < n; i++) {
        if (a[i] == "?") {
            if (i == 0) en = a[i + 1][0];
            else if (i == n - 1) st = a[i - 1].back();
            else st = a[i - 1].back(), en = a[i + 1][0];
        }
    }
    
    for (auto& i : b) {
        if (st != '*' && i.front() != st) continue;
        if (en != '*' && i.back() != en) continue;
        if (vi.count(i)) continue;
        cout << i;
        return 0;
    }
}