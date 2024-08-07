#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    srand(time(NULL));

    int tc = 8;
    cout << tc << '\n';
    while (tc--) {
        int n = rand() % 250'000, m = rand() % 25'000;
        string r(n, 'a'), p(m, 'a');

        for (int i = 0; i < m; i++)
            p[i] = rand() % 5 + 'a';

        for (int i = 0; i < n; ) {
            int len = rand() % m + 1;
            for (int j = i; j < min(i + len, n); j++) {
                r[j] = p[j - i];
            }
            i += len;
        }

        cout << r << '\n' << p << '\n';
    }
}