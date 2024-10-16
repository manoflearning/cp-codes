#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, k;
    cin >> n >> k;

    if (n == 1) { cout << k; return 0; }

    vector<int> x(1, k);
    vector<int> y(2);
    y[0] = x[0] * n % 10;
    y[1] = x[0] * n / 10;

    int isAns = 0;
    for (int i = 1; i < 101010; i++) {
        if (y[i - 1] == x[0] && y[i] == 0 && x.back() != 0) { isAns = 1; break; }
        x.resize(i + 1);
        y.resize(i + 2);

        x[i] = y[i - 1];
        y[i] += x[i] * n;
        y[i + 1] += y[i] / 10;
        y[i] %= 10;
    }
    
    if (isAns) {
        reverse(x.begin(), x.end());
        for (auto& i : x) cout << i;
    }
    else cout << 0;
}