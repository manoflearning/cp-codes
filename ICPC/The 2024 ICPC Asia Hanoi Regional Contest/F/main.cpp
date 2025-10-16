#include <bits/stdc++.h>
using namespace std;
#define ll long long

// constexpr int MAX = 3.3 * 1e4;

// bool isPrime[MAX + 1];
// vector<int> prime(1, 2);

// void getPrime() {
//     fill(isPrime + 2, isPrime + MAX + 1, 1);
//     for (ll i = 4; i <= MAX; i += 2) isPrime[i] = 0;
//     for (ll i = 3; i <= MAX; i += 2) {
//         if (!isPrime[i]) continue;
//         prime.push_back(i);
//         for (ll j = i * i; j <= MAX; j += i * 2) {
//             isPrime[j] = 0;
//         }
//     }
// }

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // getPrime();

    int tc; cin >> tc;
    while (tc--) {
        int n;
        string s;
        cin >> n >> s;

        // ll p = -1, q = -1;
        // for (int i : prime) {
        //     if (n % i) continue;

        //     p = 
        // }

        if (s == "fizzbuzz") {
            if (n == 1) {
                cout << -1 << ' ' << -1 << '\n';
            } else {
                cout << 1 << ' ' << n << '\n';
            }
        } else if (s == "fizz") {
            if (n <= 2) {
                cout << 1 << ' ' << n + 1 << '\n';
            } else {
                cout << 1 << ' ' << n - 1 << '\n';
            }
        } else if (s == "buzz") {
            if (n <= 2) {
                cout << -1 << ' ' << -1 << '\n';
            } else {
                cout << n - 1 << ' ' << n << '\n';
            }
        } else {
            if (n <= 4) {
                cout << n + 1 << ' ' << n + 2 << '\n';
            } else {
                cout << n - 2 << ' ' << n - 1 << '\n';
            }
        }
    }
}
