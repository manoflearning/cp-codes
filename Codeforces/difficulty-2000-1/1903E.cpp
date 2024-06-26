// (odd, odd)
// (odd, even)
// (even, odd)
// (even, even)

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
int stx, sty;
priority_queue<int> a, b;
vector<int> vis;

void init() {
    while (!a.empty()) a.pop();
    while (!b.empty()) b.pop();
    vis.clear();
}

void input() {
    cin >> n;
    cin >> stx >> sty;
    vis.resize(n + 1);
    for (int i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        if ((x & 1) == (y & 1)) a.push(i + 1);
        else b.push(i + 1);
    }
    if ((stx & 1) != (sty & 1)) swap(a, b);
}

void myturn() {
    while (!a.empty() && vis[a.top()]) a.pop();
    while (!b.empty() && vis[b.top()]) b.pop();

    int x = -1;
    if (!b.empty()) x = b.top();
    else x = a.top();
    cout << x << '\n';
    vis[x] = 1;
    cout.flush();
}

void opturn() {
    int x; cin >> x;
    vis[x] = 1;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        init();

        input();

        if (sz(a) >= sz(b)) {
            cout << "First" << '\n';
            cout.flush();
            for (int i = 0; i < n; i++) {
                if (i & 1) opturn();
                else myturn();
            }
        }
        else {
            cout << "Second" << '\n';
            cout.flush();
            swap(a, b);
            for (int i = 0; i < n; i++) {
                if (i & 1) myturn();
                else opturn();
            }
        }        
    }
}