// |T| = 2 * n - 1

// if n = 2 and YES
// <=> a = [1, 0] or [0, 1]

// if n = 3 and YES
// <=> a = [1, 2, 0] or [2, 1, 0] or [0, 1, 2] or [0, 2, 1]
// or [1, 0, 1] or [0, 1, 1] or [1, 1, 0]

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

const int MAXN = 202020;

int n, a[MAXN];
vector<vector<int>> idx;

void init() {
    idx.clear();
}

void input() {
    cin >> n;
    idx.resize(n);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        idx[a[i]].push_back(i);
    }
}

bool naiveCheck(int s, int e, int sub) {
    if (s > e) return true;

    vector<int> arr;
    for (int i = s; i <= e; i++)
        arr.push_back(a[i]);
    sort(all(arr));
    arr.erase(unique(all(arr)), arr.end());

    if (arr[0] != sub + 1) return false;
    for (int i = 1; i < sz(arr); i++) {
        if (arr[i - 1] + 1 < arr[i]) return false;
    }
    return true;
}

int naiveMin(int s, int e) {
    int ret = INF;
    for (int i = s; i <= e; i++) {
        ret = min(ret, a[i]);
    }
    return ret;
}

bool f(int l, int r, int sub) {
    if (l > r) return true;
    if (l == r) return false;
    if (naiveMin(l, r) < sub) return false;

    int itl = lower_bound(all(idx[sub]), l) - idx[sub].begin();
    int itr = upper_bound(all(idx[sub]), r) - idx[sub].begin();
    if (itl + 1 != itr) return false;

    bool ret = false;

    int flag = idx[sub][itl];

    if (naiveCheck(l, flag - 1, sub)) ret |= f(flag + 1, r, sub + 1);
    if (naiveCheck(flag + 1, r, sub)) ret |= f(l, flag - 1, sub + 1);

    return ret;
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

        cout << (f(1, n, 0) ? "YES" : "NO") << '\n';
    }
}