// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define pii pair<int, int>
#define fr first
#define sc second

int gcd(int x, int y) {
    if (!y) return x;
    return gcd(y, x % y);
}

int n, k;
pii arr[5050 * 5050];
bool vi[5050];
int idx = 0;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> k;

    arr[idx++] = { 0, 1 };
    for (int x = n; x >= 1; x++) {
        if (vi[x]) continue;

        int y = x;
        for (int i = 2; i <= sqrt(y); i++) {
            if (y % i == 0) {
                vi[i] = 1;
                vi[y / i] = 1;
            }
        }

        for (int i = 1; i <= x; i++) {
            arr[idx++] = { i, x };
        }
    }

    sort(arr, arr+idx, [&](const pii& p1, const pii& p2) {
        return p1.fr * p2.sc < p2.fr * p1.sc;
    });
}