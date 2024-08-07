#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> a;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    a.resize(n);
    for (auto& i : a) cin >> i;

    sort(a.begin(), a.end());

    int ansMn = n - 1;
    for (int l = 0; l < n; l++) {
        int r = lower_bound(a.begin(), a.end(), a[l] + n - 1) - a.begin();
        int res = -1;
        if (r < n && a[r] == a[l] + n - 1) {
            res = n - (r - l + 1);
        }
        else {
            if (r == n || l == 0) continue;
            else res = n - (r - l);
        }
        ansMn = min(ansMn, res);
    }

    int ansMx = max(a[n - 2] - a[0] - n + 2, a[n - 1] - a[1] - n + 2);

    cout << ansMn << '\n' << ansMx;
}