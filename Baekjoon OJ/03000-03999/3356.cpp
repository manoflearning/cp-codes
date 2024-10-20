#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD1 = 1e9 + 7;
const int MOD2 = 1e9 + 9;
const int MAXN = 1010101; // arbitrary size
const int D = 26;

int n;
vector<int> a;
ll h1[MAXN], h2[MAXN];
ll d1[MAXN], d2[MAXN];

void input() {
    string s;
    cin >> n >> s;
    for (int i = 0; i < n; i++) {
        a.push_back(s[i] - 'a');
    }
}

void get_hash() {
    h1[0] = a[0], h2[0] = a[0];
    for (int i = 1; i < n; i++) {
        h1[i] = (D * h1[i - 1] + a[i]) % MOD1;
        h2[i] = (D * h2[i - 1] + a[i]) % MOD2;
    }

    d1[0] = 1, d2[0] = 1;
    for (int i = 1; i <= n; i++) {
        d1[i] = D * d1[i - 1] % MOD1;
        d2[i] = D * d2[i - 1] % MOD2;
    }
}

ll solve() {
    for (int len = 1; len < n; len++) {
        bool is_valid = 1;
        ll x1 = h1[len - 1], x2 = h2[len - 1];
        for (int i = len; i < n; i += len) {
            if (i + len - 1 < n) {
                x1 = (x1 * d1[len] + h1[len - 1]) % MOD1;
                x2 = (x2 * d2[len] + h2[len - 1]) % MOD2;
            }
            else {
                int left_len = n - i;
                x1 = (x1 * d1[left_len] + h1[left_len - 1]) % MOD1;
                x2 = (x2 * d2[left_len] + h2[left_len - 1]) % MOD2;
            }

            // if (len == 3) {
            //     cout << x1 << ' ' << x2 << '\n';
            //     cout << h1[min(n - 1, i + len - 1)] << ' ' << h2[min(n - 1, i + len - 1)] << '\n';
            // }
            if (x1 != h1[min(n - 1, i + len - 1)] || x2 != h2[min(n - 1, i + len - 1)]) {
                is_valid = 0;
                break;
            }
        }

        if (is_valid) return len;
    }
    return n;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    get_hash();

    cout << solve();
}