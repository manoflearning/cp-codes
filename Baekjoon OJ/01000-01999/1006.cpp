#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;
const int MAXN = 10101;

int N, W;
int a[4][MAXN];
int banned[4][MAXN];
int dp[MAXN][4];

void init() {}

void input() {
    cin >> N >> W;
    for (int i = 1; i <= N; i++) cin >> a[1][i];
    for (int i = 1; i <= N; i++) cin >> a[2][i];
}

int query(int x1, int x2) {
    // assert(abs(x1 - x2) <= 1);
    // assert(dp.count({ x1, x2 }));
    if (x1 == x2 - 1) return dp[x1][0];
    if (x1 == x2 + 0) return dp[x1][1];
    if (x1 == x2 + 1) return dp[x1][2];
}
void modify(int x1, int x2, int val) {
    // assert(abs(x1 - x2) <= 1);
    if (x1 == x2 - 1) dp[x1][0] = min(dp[x1][0], val);
    if (x1 == x2 + 0) dp[x1][1] = min(dp[x1][1], val);
    if (x1 == x2 + 1) dp[x1][2] = min(dp[x1][2], val);
}

void solveInit() {
    banned[1][1] = banned[2][1] = banned[1][N] = banned[2][N] = 0;
    for (int i = 0; i < MAXN; i++) {
        dp[i][0] = dp[i][1] = dp[i][2] = dp[i][3] = INF;
    }
}

int bottomup() {
    // base case
    modify(0, 0, 0);
    modify(1, 0, 1 - banned[1][1]);
    modify(0, 1, 1 - banned[2][1]);
    modify(1, 1, 2 - banned[1][1] - banned[2][1]);
    if (!banned[1][1] && !banned[2][1] && a[1][1] + a[2][1] <= W) modify(1, 1, 1);

    // inductive step
    for (int x = 2; x <= N; x++) {
        int y1 = 1, x1 = -1;
        int y2 = 2, x2 = -1;

        // x1 = x, x2 = x - 1
        x1 = x, x2 = x - 1;
        modify(x1, x2, 1 + query(x1 - 1, x2));
        if (a[y1][x1 - 1] + a[y1][x1] <= W) {
            modify(x1, x2, 1 + query(x1 - 2, x2));
        }
        
        // x1 = x - 1, x2 = x
        x1 = x - 1, x2 = x;
        modify(x1, x2, 1 + query(x1, x2 - 1));
        if (a[y2][x2 - 1] + a[y2][x2] <= W) {
            modify(x1, x2, 1 + query(x1, x2 - 2));
        }

        // x1 = x, x2 = x
        x1 = x, x2 = x;
        modify(x1, x2, 1 + query(x1 - 1, x2));
        modify(x1, x2, 1 + query(x1, x2 - 1));
        if (a[y1][x1] + a[y2][x2] <= W) {
            modify(x1, x2, 1 + query(x1 - 1, x2 - 1));
        }
        if (a[y1][x1 - 1] + a[y1][x1] <= W && a[y2][x2 - 1] + a[y2][x2] <= W) {
            modify(x1, x2, 2 + query(x1 - 2, x2 - 2));
        }
    }

    // return answer
    return query(N - banned[1][N], N - banned[2][N]);
}

int solve() {
    int ret = INF;
    
    solveInit();
    ret = min(ret, bottomup());

    if (a[1][1] + a[1][N] <= W) {
        solveInit();
        banned[1][1] = banned[1][N] = 1;
        ret = min(ret, 1 + bottomup());
    }

    if (a[2][1] + a[2][N] <= W) {
        solveInit();
        banned[2][1] = banned[2][N] = 1;
        ret = min(ret, 1 + bottomup());
    }

    if (a[1][1] + a[1][N] <= W && a[2][1] + a[2][N] <= W) {
        solveInit();
        banned[1][1] = banned[1][N] = 1;
        banned[2][1] = banned[2][N] = 1;
        ret = min(ret, 2 + bottomup());
    }

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        if (N == 1) {
            if (a[1][1] + a[2][1] <= W) cout << 1 << '\n';
            else cout << 2 << '\n';
        }
        else cout << solve() << '\n';
    }
}