#include <bits/stdc++.h>
using namespace std;

int n, a[5050];
unordered_set<int> s;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            if (s.count(a[i] - a[j])) { ans++; break; }
        }
        for (int j = 1; j <= i; j++) s.insert(a[j] + a[i]);
    }

    cout << ans;
}