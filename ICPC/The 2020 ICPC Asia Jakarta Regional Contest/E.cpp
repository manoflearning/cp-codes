#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> e;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    e.resize(n - 1);
    for (auto& i : e) cin >> i;

    int ans = 1, res = 0;
    for (auto& i : e) {
        if (i == 1) { ans = min(ans, 2); res = 1; }
        else {
            res++;
            ans = max(ans, res);
        }
    }

    cout << ans;
}