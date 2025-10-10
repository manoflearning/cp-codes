#include <bits/stdc++.h>
using namespace std;

const int N = 1010101;

bool is_prime[N];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 2; i < N; i++) {
        is_prime[i] = 1;
    }

    for (int i = 2; i < N; i++) {
        if (!is_prime[i]) continue;
        for (int j = 2 * i; j < N; j += i) {
            is_prime[j] = 0;
        }
    }

    int tc; cin >> tc;
    while (tc--) {
        int a, b;
        cin >> a >> b;
        cout << "NY"[is_prime[a] && is_prime[b] && (a + 2 == b)] << '\n';
    }
}