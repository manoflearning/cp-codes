#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr frist
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 1010;

int n, cnt0[MAXN][MAXN];
bool a[MAXN], ans[MAXN][MAXN];

void preprocess() {
    for (int i = 0; i < MAXN; i++) {
        a[i] = 1;
        for (int j = 0; j < MAXN; j++) ans[i][j] = 1;
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
            cin >> cnt0[i][j];
        }
    }
}

void solve() {
    for (int i = 1; i <= n - 1; i++) {
        for (int j = 1; j <= n; j++) {
            if (!ans[i][j - 1]) cnt0[i][j]--;
            if (!ans[i][j + 1]) cnt0[i][j]--;
            if (!ans[i - 1][j]) cnt0[i][j]--;
            if (!ans[i - 1][j - 1]) cnt0[i][j]--;
            if (!ans[i - 1][j + 1]) cnt0[i][j]--;
        }
        
        if (cnt0[i][1] == 0 || cnt0[i][1] == 2) {
            if (cnt0[i][1] == 0) ans[i + 1][1] = ans[i + 1][2] = 1;
            if (cnt0[i][1] == 2) ans[i + 1][1] = ans[i + 1][2] = 0;
            for (int j = 2; j <= n - 1; j++)  {
                int val = (!ans[i + 1][j - 1] ? 1 : 0) + (!ans[i + 1][j] ? 1 : 0);
                if (val < cnt0[i][j]) ans[i + 1][j + 1] = 0;
                else ans[i + 1][j + 1] = 1;
            }
        }
        else if (cnt0[i][1] == 1) {
            ans[i + 1][1] = 0, ans[i + 1][2] = 1;
            for (int j = 2; j <= n - 1; j++)  {
                int val = (!ans[i + 1][j - 1] ? 1 : 0) + (!ans[i + 1][j] ? 1 : 0);
                if (val < cnt0[i][j]) ans[i + 1][j + 1] = 0;
                else ans[i + 1][j + 1] = 1;
            }

            bool isValid = 1;
            for (int j = 1; j <= n; j++) {
                int val = (!ans[i + 1][j - 1] ? 1 : 0) + (!ans[i + 1][j] ? 1 : 0) + (!ans[i + 1][j + 1] ? 1 : 0);
                isValid &= (val == cnt0[i][j]);
            }

            if (isValid) continue;

            ans[i + 1][1] = 1, ans[i + 1][2] = 0;
            for (int j = 2; j <= n - 1; j++)  {
                int val = (!ans[i + 1][j - 1] ? 1 : 0) + (!ans[i + 1][j] ? 1 : 0);
                if (val < cnt0[i][j]) ans[i + 1][j + 1] = 0;
                else ans[i + 1][j + 1] = 1;
            }
        }
    }
}

void output() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << (ans[i][j] ? 1 : 0) << ' ';
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

    preprocess();

    input();

    solve();

    output();
}