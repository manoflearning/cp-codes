#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("input.txt", "w", stdout);

    srand(time(NULL));

    int tc = 32;
    int n = 50'000;
    vector<int> a(n, 3);

    int q = 50'000;
    cout << tc << '\n';
    while (tc--) {
        cout << n << '\n';
        for (auto& i : a) cout << i << ' ';
        cout << '\n';
        cout << q << '\n';
        for (int i = 0; i < q; i++) {
            int l = rand() % n + 1, r = rand() % n + 1;
            if (l > r) swap(l, r);
            cout << l << ' ' << r << '\n';
        }
    }
}