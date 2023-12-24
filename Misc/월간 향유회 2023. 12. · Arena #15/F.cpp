// ? 1 N => K 얻음

// ? 2 N => x
// K <= x => 고유 원소 X
// x < K => 고유 원소 O

// A[i]가 고유 원소다 => sum[1][i - 1] < sum[1][i]
// A[i]가 고유 원소다 => sum[i + 1][N] > sum[i + 1][N]

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

const int MAXN = 1010;

int N, K;
vector<int> ans;
int sum[MAXN][MAXN];

int query(int L, int R) {
    assert(L <= R);

    cout << "? " << L << ' ' << R << '\n';
    cout << flush;

    int ret; cin >> ret;
    return ret;
}

void preprocessing() {
    // sum[1][N] = query(1, N);
    for (int i = 1; i <= N; i++) {
        sum[1][i] = query(1, i);
    }
    for (int i = 1; i <= N; i++) {
        sum[i][N] = query(i, N);
    }
}

void solve() {
    for (int x = 1; x <= N; x++) {
        bool ls = false, rs = false;
        if (x == 1 || (x > 1 && sum[1][x - 1] < sum[1][x])) ls = true;
        if (x == N || (x < N && sum[x][N] > sum[x + 1][N])) rs = true;
        if (ls && rs) ans.push_back(x);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    // cin.tie(NULL); cout.tie(NULL);
    // ios_base::sync_with_stdio(false);

    cin >> N;

    preprocessing();

    solve();

    cout << "! " << sz(ans) << ' ';
    for (auto& i : ans) cout << i << ' ';
    cout << flush;
}