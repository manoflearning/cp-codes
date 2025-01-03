#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

const int INF = 1e9 + 7;

int n, lb;
vector<int> a, b;
int dp[404][404][404];

int f(int i, int j, int k) {
    int& ret = dp[i][j][k];
    if (ret != -INF) return ret;
    if (i == 0 && j == 0) {
        if (lb <= k) return ret = 0;
        else return ret = -INF;
    }

    ret = -INF;
    if (i > 0 && j > 0) ret = max(ret, a[i] * b[j] + f(i - 1, j - 1, k + 1));
    if (i > 0) ret = max(ret, f(i - 1, j, k));
    if (j > 0) ret = max(ret, f(i, j - 1, k));
    
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    for (int i = 0; i < 404; i++) {
        for (int j = 0; j < 404; j++) {
            for (int k = 0; k < 404; k++) {
                dp[i][j][k] = -INF;
            }
        }
    }

    cin >> n;
    a.push_back(0);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        if (x) a.push_back(x);
    }
    b.push_back(0);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        if (x) b.push_back(x);
    }

    lb = n - (n - sz(a) + 1) - (n - sz(b) + 1);

    cout << f(sz(a) - 1, sz(b) - 1, 0);
}