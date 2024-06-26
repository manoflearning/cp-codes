#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    int mid = n / 2;
    if (mid * (n - mid) < m) {
        cout << -1;
        return 0;
    }

    string ans;
    for (int i = 0; i < mid; i++) ans.push_back('B');
    for (int i = 0; i < n - mid; i++) ans.push_back('A');
    
    int res = 0;    
    while (res < m) {
        res++;
        int bit = 0;
        for (int i = 0; i + 1 < n; i++) {
            if (ans[i] == 'B' && ans[i + 1] == 'A') {
                swap(ans[i], ans[i + 1]);
                bit = 1;
                break;
            }
        }
    }

    cout << ans;
}