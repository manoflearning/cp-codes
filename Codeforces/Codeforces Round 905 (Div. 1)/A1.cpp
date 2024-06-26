// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

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
vector<int> a, b;

void init() {}

void input() {
    cin >> n >> m;
    a.resize(n - 1);
    b.resize(n);
    for (auto& i : a) cin >> i;
    for (auto& i : b) cin >> i;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        init();

        input();

        a.push_back(1);
        sort(all(a));
        sort(all(b));

        int l = 0, r = n;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            int isValid = 1;
            for (int i = 0; i < mid; i++) {
                if (a[i] >= b[n - mid + i]) { isValid = 0; break; }
            }
            if (isValid) l = mid;
            else r = mid - 1;
        }

        cout << n - l << '\n';
    }
}