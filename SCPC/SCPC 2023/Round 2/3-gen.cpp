// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const int MAXN = 5050;
const int INF = 1e9 + 7;

int N, M, t;
int a[MAXN];

struct group12 {
    int toLeft(int x) { // [1, x]
        int ret = 1;
        for (int i = x - 1; i >= max(1, x - t); i--) {
            if (a[i] == 2) break;
            ret++;
        }
        return ret;
    }
    int toRight(int x) { // [x, N]
        int ret = 1;
        for (int i = x + 1; i <= min(N, x + t); i++) {
            if (a[i] == 2) break;
            ret++;
        }
        return ret;
    }
    int sum(int l, int r) { // [l, r]
        if (l == r) return 1;
        int ret = 2;
        int lmx = l;
        for (int i = l + 1; i <= min(r - 1, l + t); i++) {
            if (a[i] == 2) break;
            ret++, lmx = i;
        }
        for (int i = r - 1; i >= max(lmx + 1, r - t); i--) {
            if (a[i] == 2) {
                if (i == lmx + 1 && i <= l + t) ret++;
                break;
            }
            ret++;
        }
        return ret;
    }
    int dp[MAXN][MAXN];
    int solve() {
        int ret = 0;

        // base case
        for (int v = 1; v <= N; v++) {
            dp[v][1] = toLeft(v) + (M == 1 ? toRight(v) - 1 : 0);
            ret = max(ret, dp[v][1]);
        }

        // inductive step
        for (int cnt = 2; cnt <= M; cnt++) {
            for (int e = 1; e <= N; e++) {
                dp[e][cnt] = -INF;
                for (int s = 1; s < e; s++) {
                    int now = dp[s][cnt - 1];
                    now += sum(s, e) - 1;
                    if (cnt == M) now += toRight(e) - 1;
                    dp[e][cnt] = max(dp[e][cnt], now);
                }
                ret = max(ret, dp[e][cnt]);
            }
        }

        return ret;
    }
} g12;

// group 3
int sum[MAXN][MAXN];
int toLeft[MAXN], toRight[MAXN];

int getToLeft(int x) { // [1, x]
    int ret = 1;
    for (int i = x - 1; i >= max(1, x - t); i--) {
        if (a[i] == 2) break;
        ret++;
    }
    return ret;
}
int getToRight(int x) { // [x, N]
    int ret = 1;
    for (int i = x + 1; i <= min(N, x + t); i++) {
        if (a[i] == 2) break;
        ret++;
    }
    return ret;
}
void buildToLeftOfRight() {
    for (int i = 1; i <= N; i++) {
        toLeft[i] = getToLeft(i);
        toRight[i] = getToRight(i);
    }
}

int getSum(int l, int r) { // [l, r]
    if (l == r) return 1;
    int ret = 2;
    int lmx = l;
    for (int i = l + 1; i <= min(r - 1, l + t); i++) {
        if (a[i] == 2) break;
        ret++, lmx = i;
    }
    for (int i = r - 1; i >= max(lmx + 1, r - t); i--) {
        if (a[i] == 2) {
            if (i == lmx + 1 && i <= l + t) ret++;
            break;
        }
        ret++;
    }
    return ret;
}
void buildSum() {
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            sum[i][j] = getSum(i, j);
        }
    }
}

void init() {}

void input() {
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> a[i];
    cin >> M >> t;
}

int dp[MAXN];
int getAns() {
    int ret = 0, idx = -1;

    // base case
    for (int v = 1; v <= N; v++) {
        dp[v] = toLeft[v] + toRight[v] - 1;
        if (ret < dp[v] || (ret == dp[v] && idx < v)) {
            ret = dp[v];
            idx = v;
        }
    }

    // inductive step
    for (int cnt = 2; cnt <= M; cnt++) {
        int val = ret, loc = idx;
        for (int e = val + 1; e <= N; e++) {
            int now = val + sum[loc][e] - 1 - toRight[loc] + 1;
            now += toRight[e] - 1;
            dp[e] = max(dp[e], now);
            if (ret < dp[e] || (ret == dp[e] && idx < e)) {
                ret = dp[e], idx = e;
            }
        }
    }

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    srand(time(NULL));
    for (int tc = 0; tc < 1000000; tc++) {
        N = 4;
        M = (rand() % N <= N / 3 ? 1 : rand() % N + 1);
        t = rand() % N + 1;

        for (int i = 1; i <= N; i++) {
            a[i] = rand() % 2 + 1;
        }

        buildToLeftOfRight();
        buildSum();

        if (g12.solve() != getAns()) {
            cout << N << '\n';
            for (int i = 1; i <= N; i++) cout << a[i] << ' ';
            cout << '\n';
            cout << M << ' ' << t << '\n';
            cout << g12.solve() << ' ' << getAns() << '\n';
            for (int i = 1; i <= N; i++) cout << dp[i] << ' ';
            cout << '\n';
            break;
        }
    }
}