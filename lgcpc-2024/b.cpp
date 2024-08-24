#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int N = 505050;

int n, k;
int a[N], w[N];
int psum[N];
ll psum1[N], psum2[N];

inline int sum(int i, int j) { return psum[j] - psum[i - 1]; }
inline ll sum1(int i, int j) { return psum1[j] - psum1[i - 1]; }
inline ll sum2(int i, int j) { return psum2[j] - psum2[i - 1]; }

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        // input
        cin >> n >> k;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> w[i];

        // build prefix sum
        for (int i = 1; i <= n; i++)
            psum[i] = a[i] + psum[i - 1];

        for (int i = 1; i <= n; i++) {
            psum1[i] = (a[i] == 1 ? w[i] : 0) + psum1[i - 1];
            psum2[i] = (a[i] == 2 ? w[i] : 0) + psum2[i - 1];
        }

        // case 1
        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j += 2) {
                int len = (j - i + 1);
                if (sum(i, j) != len / 2 * 3) continue;
                if (abs(sum1(i, j) - sum2(i, j)) > k) continue;
                ans++;
            }
        }

        // case 2
        

        // output
        cout << ans << '\n';
    }
}
