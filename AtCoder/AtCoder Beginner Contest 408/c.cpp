#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int INF = 1e9 + 7;
const int N = 1010101;
const int M = 202020;

int n, m;
int l[M], r[M];
int psum[N];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> l[i] >> r[i];
        psum[l[i]]++, psum[r[i] + 1]--;
    }

    int ans = INF;
    for (int i = 1; i <= n; i++) {
        psum[i] += psum[i - 1];
        ans = min(ans, psum[i]);
    }
    cout << ans;
}
