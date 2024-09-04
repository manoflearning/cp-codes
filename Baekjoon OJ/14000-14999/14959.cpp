#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 1010101;
const int MOD1 = 1e9 + 7, MOD2 = 1e9 + 9;
const int INF = 1e9 + 7;
const int D = 1'000'000;

int n, a[MAXN];
ll Hash1[MAXN], Hash2[MAXN];
ll exp_d1[MAXN], exp_d2[MAXN];

int get_hash(int u, int v, bool is_1) {
    if (is_1) {
        return ((Hash1[v] - exp_d1[v - u + 1] * Hash1[u - 1]) % MOD1 + MOD1) % MOD1;
    }
    else {
        return ((Hash2[v] - exp_d2[v - u + 1] * Hash2[u - 1]) % MOD2 + MOD2) % MOD2;
    }
}

bool match(int u, int v, int p, int q) {
    assert(v - u == q - p);
    assert(u <= v && p <= q);

    if (p < 1 || n < q) return 0;
    if (u < 1 || n < v) return 0;
    
    if (get_hash(u, v, 1) != get_hash(p, q, 1)) return 0;
    if (get_hash(u, v, 0) != get_hash(p, q, 0)) return 0;
    return 1;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    // input
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    // rabin-karp
    exp_d1[0] = exp_d2[0] = 1;
    for (int i = 1; i <= n; i++) {
        exp_d1[i] = D * exp_d1[i - 1] % MOD1;
        exp_d2[i] = D * exp_d2[i - 1] % MOD2;
    }

    Hash1[0] = Hash2[0] = 0;
    for (int i = 1; i <= n; i++) {
        Hash1[i] = (D * Hash1[i - 1] + a[i]) % MOD1;
        Hash2[i] = (D * Hash2[i - 1] + a[i]) % MOD2;
    }

    // get answer
    int ans_k = 0, ans_p = n;
    for (int p = 1; p < n; p++) {
        int k = INF;
        for (int i = n - 2 * p + 1; ; i -= p) {
            int j = i + p - 1;
            if (i <= 1 || (i > 1 && !match(i, j, j + 1, j + p))) {
                int l = max(i, 1), r = j + 1;
                while (l < r) {
                    int mid = (l + r) >> 1;
                    if (match(mid, j, mid + p, j + p)) r = mid;
                    else l = mid + 1;
                }
                k = l - 1;
                break;
            }
            else k = i;
        }

        if (k + p < ans_k + ans_p || (k + p == ans_k + ans_p && p < ans_p)) {
            ans_k = k, ans_p = p;
        }
    }

    cout << ans_k << ' ' << ans_p;
}
