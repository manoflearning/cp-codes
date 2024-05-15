#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-7;

int n;
vector<double> a[10];
double ans[10];

void input() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        a[i].resize(n + 1);
        for (auto& j : a[i]) cin >> j;
    }
}

void solve() {
    sort(a, a + n);

    // since numbers are small, it's solid to use real numbers
    for (int i = 0; i < n; i++) {
        double tmp = a[i][i];
        for (int j = i; j < n + 1; j++) a[i][j] /= tmp;

        for (int j = i + 1; j < n; j++) {
            if (a[j][i] == 0) continue; 
            double tmp = a[j][i];
            for (int k = i; k < n + 1; k++) {
                a[j][k] -= tmp * a[i][k];
            }
        }
    }

    // for (int i = 0; i < n; i++) {
    //     for (auto& j : a[i]) cout << j << ' ';
    //     cout << '\n';
    // }

    ans[n - 1] = a[n - 1][n];
    for (int i = n - 2; i >= 0; i--) {
        double sum = a[i][n];
        for (int j = i + 1; j < n; j++) sum -= a[i][j] * ans[j];
        ans[i] = sum;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    solve();

    for (int i = 0; i < n; i++)
        cout << (int)(ans[i] + EPS) << ' ';
}