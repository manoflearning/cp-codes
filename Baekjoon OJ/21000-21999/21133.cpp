#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n; cin >> n;

    vector<int> ans;
    if (n % 6 == 2 || n % 6 == 3) {
        for (int i = 2; i <= n; i += 2) ans.push_back(i);
        for (int i = 1; i <= n; i += 2) ans.push_back(i);
        if (n % 6 == 2) {
            for (int i = 0; i < n; i++)
                if (ans[i] == 1) { swap(ans[i], ans[i + 1]); break; }
            for (int i = 0; i + 1 < n; i++)
                if (ans[i] == 5) swap(ans[i], ans[i + 1]);
        }
        if (n % 6 == 3) {
            for (int i = 0; i + 1 < n; i++) {
                if (ans[i + 1] % 2 == 0) {
                    swap(ans[i], ans[i + 1]);
                }
            }
            for (int i = 0; i + 2 < n; i++) {
                if (ans[i] % 2 == 1 && ans[i + 1] % 2 == 1 && ans[i + 2] % 2 == 1) {
                    swap(ans[i + 1], ans[i + 2]);
                    swap(ans[i], ans[i + 1]);
                }
            }
        }
    }
    else {
        for (int i = 2; i <= n; i += 2) ans.push_back(i);
        for (int i = 1; i <= n; i += 2) ans.push_back(i);
    }

    for (auto& i : ans) 
        cout << i << '\n';
}