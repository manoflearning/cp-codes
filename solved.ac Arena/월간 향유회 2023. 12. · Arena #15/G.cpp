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

int n;
ll m;
vector<ll> a;
vector<bool> vi;

void input() {
    cin >> n >> m;
    a.resize(n);
    vi.resize(n);
    for (auto& i : a) cin >> i;
}

void solve() {
    ll sum = 0;
    for (auto& i : a) sum += i;

    while (1) {
        ll tmp = m;
        m %= sum;

        for (int i = 0; i < n; i++) {
            if (vi[i]) continue;
            if (m < a[i]) {
                vi[i] = 1;
                sum -= a[i];
            }
            else m -= a[i];
        }

        if (tmp == m || sum == 0) break;
    }

    cout << m;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    solve();
}