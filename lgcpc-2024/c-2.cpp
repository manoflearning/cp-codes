#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int N = 404, K = 808;
const int INF = 1e9 + 7;

int n, k;
int m[N][K];

int dp[K][K];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            cin >> m[i][j];
        }
    }

    
}

// observations:
// * time 2t => ans <= t
// * 