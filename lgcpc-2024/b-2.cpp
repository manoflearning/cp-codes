#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second

const int N = 505050;

int n, k;
int a[N], w[N];
int psum[N];
ll psum1[N], psum2[N];

inline int sum(int i, int j) { return psum[j] - psum[i - 1]; }
inline ll sum1(int i, int j) { return psum1[j] - psum1[i - 1]; }
inline ll sum2(int i, int j) { return psum2[j] - psum2[i - 1]; }

int ltor[N];

ll case3() {
    // sliding window
    int cnt1 = 0, cnt2 = 0;
    int r = 1;
    for (int l = 1; l <= n; l++) {
        if (l > 1) {
            cnt1 -= a[l - 1] == 1;
            cnt2 -= a[l - 1] == 2;
        }

        while (r <= n && (l >= r || cnt1 != cnt2)) {
            cnt1 += a[r] == 1;
            cnt2 += a[r] == 2;
            r++;
        }

        if (cnt1 != cnt2) continue;

        ltor[l] = r - 1;
        cout << l << ' ' << ltor[l] << '\n';
    }
    return 0;
}

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

        // solve
        cout << case3() << '\n';
    }
}
