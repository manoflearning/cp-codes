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
    a.resize(n + 1);

    a[1] = 1;
    for (int i = 2; i <= n; i++) {
        int v = i - 1;
        while (v > 1) {
            swap(a[v >> 1], a[v]);
            v >>= 1;
        }
        a[i] = i;
        swap(a[1], a[i]);
    }

    for (int i = 1; i <= n; i++)
        cout << a[i] << ' ';
}