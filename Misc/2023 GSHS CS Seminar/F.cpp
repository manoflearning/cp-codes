#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 1010;

int n, a[MAXN], cnt[MAXN][MAXN], ans[MAXN][MAXN];

void init() {
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++) {
            ans[i][j] = 1;
        }
    }
}

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        ans[1][i] = a[i];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> cnt[i][j];
        }
    }
}

void solve() {
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cnt[i - 1][j] -= (ans[i - 2][j - 1] ? 0 : 1);
            cnt[i - 1][j] -= (ans[i - 2][j] ? 0 : 1);
            cnt[i - 1][j] -= (ans[i - 2][j + 1] ? 0 : 1);
            cnt[i - 1][j] -= (ans[i - 1][j - 1] ? 0 : 1);
            cnt[i - 1][j] -= (ans[i - 1][j + 1] ? 0 : 1);
        }

        if (cnt[i - 1][1] == 0 || cnt[i - 1][1] == 2) {
            if (cnt[i - 1][1] == 0) ans[i][1] = ans[i][2] = 1;
            if (cnt[i - 1][1] == 2) ans[i][1] = ans[i][2] = 0;
            for (int j = 3; j <= n; j++) {
                int val = (ans[i][j - 2] ? 0 : 1) + (ans[i][j - 1] ? 0 : 1);
                if (cnt[i - 1][j - 1] == val) ans[i][j] = 1;
                else ans[i][j] = 0;
            }
        }
        else if (cnt[i - 1][1] == 1) {
            ans[i][1] = 0, ans[i][2] = 1;
            for (int j = 3; j <= n; j++) {
                int val = (ans[i][j - 2] ? 0 : 1) + (ans[i][j - 1] ? 0 : 1);
                if (cnt[i - 1][j - 1] == val) ans[i][j] = 1;
                else ans[i][j] = 0;
            }

            bool isValid = 1;
            for (int j = 1; j <= n; j++) {
                int val = (ans[i][j - 1] ? 0 : 1)  + (ans[i][j] ? 0 : 1) + (ans[i][j + 1] ? 0 : 1);
                isValid &= (cnt[i - 1][j] == val);
            }

            if (isValid) continue;

            ans[i][1] = 1, ans[i][2] = 0;
            for (int j = 3; j <= n; j++) {
                int val = (ans[i][j - 2] ? 0 : 1) + (ans[i][j - 1] ? 0 : 1);
                if (cnt[i - 1][j - 1] == val) ans[i][j] = 1;
                else ans[i][j] = 0;
            }
        }
    }
}

void output() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << ans[i][j] << ' ';
        }
        cout << '\n';
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    init();

    input();

    solve();

    output();
}