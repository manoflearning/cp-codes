//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long

const ll INF = 1e18;

int n, m, k;

struct Snake { int len, idx; };
vector<Snake> snake;
ll lenSum = 0;

ll a[5050][5050];
int w[5050][5050];
ll dp[5050][5050];

void init() {
    for (int i = 0; i < 5050; i++) {
        for (int j = 0; j < 5050; j++) {
            dp[i][j] = -1;
        }
    }
}

void input() {
    cin >> m >> n >> k;
    snake.resize(k);
    for (int i = 0; i < k; i++) {
        cin >> snake[i].len;
        snake[i].idx = i;
        lenSum += snake[i].len;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            string s; cin >> s;
            if (s == "*") w[i][j] = 1;
            else a[i][j] = stoi(s);
        }
    }
}

ll f(int y, int x, int cnt) {
    if (cnt == 0) return 0;
    ll& ret = dp[y][x];
    if (ret != -1) return ret;
    
    ret = a[y][x];
    ll res = 0;
    if (y + 1 <= n && !w[y + 1][x]) res = max(res, f(y + 1, x, cnt - 1));
    if (x + 1 <= m && !w[y][x + 1]) res = max(res, f(y, x + 1, cnt - 1));
    
    ret += res;
    return ret;
}

void print(int y, int x, int cnt, int idx) {

}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    init();

	input();

    cout << f(1, 1, lenSum);

    print(1, 1, lenSum, 0);
}