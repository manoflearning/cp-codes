#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> a;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    if (n == 0) {
        cout << 0;
        return 0;
    }
    a.resize(n);
    for (auto& i : a) cin >> i;

    sort(a.begin(), a.end());

    int x = (n * 15 + 50) / 100;
    
    int sum = 0;
    for (int i = x; i < n - x; i++) sum += a[i];
    
    cout << (int)((double)sum / (n - 2 * x) + 0.5);
}