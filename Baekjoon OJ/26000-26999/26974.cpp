// r[i][i + 1] means absolute difference between a[i] and a[i + 1] (|a[i] - a[i + 1]|)

// Let r[i][i + 1] > 0 and r[i + 1][i + 2] > 0.
// r[i][i + 2] = (r[i][i + 1] + r[i + 1][i + 1]) or max(r[i][i + 1], r[i + 1][i + 2])

// If r[i][i + 2] = r[i][i + 1] + r[i + 1][i + 1],
// sign of (a[i + 1] - a[i]) is equals to (a[i + 2] - a[i]).

// If r[i][i + 2] = max(r[i][i + 1], r[i + 1][i + 2]),
// sign of (a[i + 1] - a[i]) is equals to -(a[i + 2] - a[i]).

#include <bits/stdc++.h>
using namespace std;

int n;
int r[303][303];
int diff[303], ans[303]; // diff[i] := a[i] - a[i - 1]

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    // initialize
    memset(r, -1, sizeof(r));

    // input
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            cin >> r[i][j];
        }
    }

    // solve
    diff[2] = r[1][2];
    for (int e = 3; e <= n; e++) {
        if (r[e - 1][e] == 0) {
            diff[e] = 0;
            continue;
        }

        int s = e - 1;
        while (s >= 2 && diff[s] == 0) s--;
        if (s < 2) {
            diff[e] = r[e - 1][e];
            continue;
        }

        s--;
        if (r[s][e] == r[s][e - 1] + r[e - 1][e]) {
            if (diff[s + 1] < 0) diff[e] = -r[e - 1][e];
            else diff[e] = r[e - 1][e];
        }
        if (r[s][e] != r[s][e - 1] + r[e - 1][e]) {
            if (diff[s + 1] < 0) diff[e] = r[e - 1][e];
            else diff[e] = -r[e - 1][e];
        }
    }

    ans[1] = 0;
    for (int i = 2; i <= n; i++) {
        ans[i] = diff[i] + ans[i - 1];
    }

    // output
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
}