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
const ll INF = 1e18;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n, m, k;
struct Snake { int len, idx; };
vector<Snake> snake;
ll a[5050][5050];
int w[5050][5050];

ll psum[5050][5050], wcnt[5050][5050];
int visitedColumn[5050];
pii ans[5050];
int len[5050];

void input() {
    cin >> m >> n >> k;
    snake.resize(k);
    for (int i = 0; i < k; i++) {
        cin >> snake[i].len;
        snake[i].idx = i;
        len[i] = snake[i].len;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            string s; cin >> s;
            if (s == "*") w[i][j] = 1;
            else a[i][j] = stoi(s);
        }
    }
}

ll getw(int x, int l, int r) {
    if (l >= 1) return wcnt[r][x] - wcnt[l - 1][x];
    else {
        l += n;
        return (wcnt[n][x] - wcnt[l - 1][x]) + wcnt[r][x];
    }
    /*if (l >= 1) return wcnt[y][r] - wcnt[y][l - 1];
    else {
        l += m;
        return (wcnt[y][m] - wcnt[y][l - 1]) + wcnt[y][r];
    }*/
}

ll getSum(int x, int l, int r) {
    if (l >= 1) return psum[r][x] - psum[l - 1][x];
    else {
        l += n;
        return (psum[n][x] - psum[l - 1][x]) + psum[r][x];
    }
}

void solve() {
    for (auto& v : snake) {
        ll mx = 0; int resi = 0, resj = 0;
        for (int j = 1; j <= m; j++) {
            if (visitedColumn[j]) continue;
            for (int i = 1; i <= n; i++) {
                if (getw(j, i - v.len + 1, i) > 0) continue;
                ll sum = getSum(j, i - v.len + 1, i);
                if (mx < sum) {
                    mx = sum;
                    resi = i, resj = j;
                }
            }
        }
        //if (mx == 0) continue;
        visitedColumn[resj] = 1;
        ans[v.idx] = { resi, resj };
        /*for (int i = 1; i <= n; i++) {
            if (visitedRow[i]) continue;
            for (int j = 1; j <= m; j++) {
                if (getw(i, j - v.len + 1, j) > 0) continue;
                ll sum = getSum(i, j - v.len + 1, j);
                if (mx < sum) {
                    mx = sum;
                    resi = i, resj = j;
                }
            }
        }
        visitedRow[resi] = 1;
        ans[v.idx] = { resi, resj };*/
    }
}

void print() {
    for (int i = 0; i < k; i++) {
        if (ans[i].fr == 0) { cout << '\n'; continue; }
        cout << ans[i].sc - 1 << ' ' << ans[i].fr - 1 << ' ';
        for (int j = 0; j < len[i] - 1; j++) cout << "U ";
        cout << '\n';
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

	input();

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            psum[i][j] = a[i][j] + psum[i - 1][j];
            wcnt[i][j] = w[i][j] + wcnt[i - 1][j];
        }
    }

    sort(all(snake), [&](const Snake& lhs, const Snake& rhs) {
        return lhs.len > rhs.len;
    });

    solve();

    print();
}