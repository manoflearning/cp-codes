#include <bits/stdc++.h>
using namespace std;

int n, x;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> x;

    string ans;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= 26; j++) {
            if (j <= x && n - i - 1 <= x - j && x - j <= 26 * (n - i - 1)) {
                ans.push_back('A' + j - 1);
                x -= j;
                break;
            }
        }
        if (ans.size() != i + 1) {
            cout << "!";
            return 0;
        }
    }
    cout << ans;
}