#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int N = 303;

int n;
vector<vector<int>> a(N, vector<int>(N));

vector<int> dp[N];

// vector<int> naive_1d() {
//     vector<int> ret;

//     vector<int> arr(n);
//     iota(all(arr), 0);

//     do {
//         bool is_valid = 1;
//         for (int i = 0; i < n; i++) {
//             for (int j = i + 1; j < n; j++) {
//                 for (int k = j + 1; k < n; k++) {
//                     int d1 = (arr[j] - arr[i] + n) % n;
//                     int d2 = (arr[k] - arr[j] + n) % n;
//                     if (d1 == d2) {
//                         is_valid = 0;
//                         i = j = k = n;
//                         break;
//                     }
//                 }
//             }
//         }

//         if (is_valid) {
//             ret = arr;

//             for (auto &i : arr) cout << i << ' ';
//             cout << '\n';
//             for (int i = 0; i + 1 < n; i++) {
//                 cout << (arr[i + 1] - arr[i] + n) % n << ' ';
//             }
//             cout << '\n';
//             cout << '\n';
//         }
//     } while (next_permutation(all(arr)));

//     return ret;
// }

bool validate(vector<vector<int>> arr) {
    for (int r = 0; r < n; r++) {
        set<int> st1, st2;
        for (int i = 0; i < n; i++) {
            st1.insert(arr[r][i]);
            st2.insert(arr[i][r]);
        }
        if (sz(st1) != n || sz(st2) != n) return 0;
    }
    for (int r = 0; r < n; r++) {
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    if (arr[r][i] + arr[r][k] == 2 * arr[r][j]) return 0;
                    if (arr[i][r] + arr[k][r] == 2 * arr[j][r]) return 0;
                }
            }
        }
    }
    return 1;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;

    dp[2] = {1};
    for (int i = 2; (i << 1) < N; i *= 2) {
        for (auto x : dp[i]) dp[i << 1].push_back(x << 1);
        dp[i << 1].push_back(1);
        for (auto x : dp[i]) dp[i << 1].push_back(x << 1);
    }

    if (n == 1) {
        cout << 1 << '\n' << 1 << '\n';
    }
    else if (!dp[n].empty()) {
        vector<int> ord;
        ord.push_back(0);
        for (auto x : dp[n]) {
            ord.push_back((ord.back() + x) % n);
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] = (i + j) % n;
            }
        }
        
        vector<vector<int>> arr(n, vector<int>(n));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                arr[i][j] = a[ord[i]][ord[j]] + 1;
            }
        }

        // assert(validate(arr));

        cout << 1 << '\n';
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << arr[i][j] << ' ';
            }
            cout << '\n';
        }
    } else {
        cout << 0;
    }
}
