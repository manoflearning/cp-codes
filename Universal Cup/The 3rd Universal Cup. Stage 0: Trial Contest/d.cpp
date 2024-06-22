#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> a, b;

void yes() { cout << 1; exit(0); }

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    a.resize(n);
    for (auto& i : a) cin >> i;
    b.resize(m);
    for (auto& i : b) cin >> i;

    for (int i = 0; i < n; i++) {
        bool is_same = 1;
        for (int j = i, k = 0; k < m; j = (j + 1) % n, k++) {
            if (a[j] != b[k]) { is_same = 0; break; }
        }

        if (is_same) yes();
    }

    for (int i = 0; i < n; i++) {
        bool is_same = 1;
        for (int j = i, k = 0; k < m; j = (j + n - 1) % n, k++) {
            if (a[j] != b[k]) { is_same = 0; break; }
        }

        if (is_same) yes();
    }

    cout << 0;
}