#include <bits/stdc++.h>
using namespace std;
#define ll long long

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

    int sum = 0;
    for (auto& i : a) sum += i;

    if (sum != (n - 1) * n / 2) {
        cout << -1;
        return 0;
    }

    sum = 0;
    sort(a.begin(), a.end());
    for (int i = 0; i <= n - 1; i++) {
        sum += a[i];
        if (sum < i * (i + 1) / 2) {
            cout << -1;
            return 0;
        }
    }

    cout << 1;
}