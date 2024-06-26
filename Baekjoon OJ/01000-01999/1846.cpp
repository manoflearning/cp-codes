#include <bits/stdc++.h>
using namespace std;

void printTheBoard(int n) {
    vector<vector<int>> arr(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; i++) 
        arr[i][i] = arr[i][n - i + 1] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << arr[i][j] << ' ';
        }
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

    int n; cin >> n;
    
    //printTheBoard(n);

    if (n == 3) {
        cout << -1;
        return 0;
    }

    vector<int> ans(n + 1);
    ans[1] = (n + 1) / 2;
    ans[n] = ans[1] + 1;
    for (int i = 2; i <= (n + 1) / 2; i++) ans[i] = i - 1;
    for (int i = (n + 1) / 2 + 1; i < n; i++) ans[i] = i + 1;

    for (int i = 1; i <= n; i++)
        cout << ans[i] << '\n';
}