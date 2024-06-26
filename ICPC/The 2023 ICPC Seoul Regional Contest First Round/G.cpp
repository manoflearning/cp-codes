// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define pii pair<int, int>
#define fr first
#define sc second

int n, k;
pii arr[5050 * 5050];
int idx = 0;

int gcd(int x, int y) {
    if (!y) return x;
    return gcd(y, x % y);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> k;
    arr[idx++] = { 0, 1 };
    // arr[idx++] = { 1, 1 };

    for (int i = 2; i <= n; i++) {
        if (i % 2 == 0) {
            for (int j = 1; j < (i + 1) / 2; j += 2) {
                arr[idx++] = { j, i };
            }
        }
        else if (i % 3 == 0) {
            for (int j = 1; j < (i + 1) / 2; j++) {
                if (j % 3 == 0) continue;
                arr[idx++] = { j, i };
            }
        }
        else {
            for (int j = 1; j < (i + 1) / 2; j++) {
                arr[idx++] = { j, i };
            }
        }
    }

    sort(arr, arr + idx, [&](const auto& p1, const auto& p2) {
        return p1.fr * p2.sc < p2.fr * p1.sc;
    });

    // cout << idx << '\n';
    if (k == 1) {
        cout << arr[0].fr << ' ' << arr[0].sc;
        return 0;
    }
    k--;
    for (int i = 1; i < idx; i++) {
        if (arr[i - 1].fr * arr[i].sc != arr[i].fr * arr[i - 1].sc) {
            k--;
            // cout << arr[i].fr << ' ' << arr[i].sc << '\n';
        }
        if (k == 0) {
            int g = gcd(arr[i].fr, arr[i].sc);
            cout << arr[i].fr / g << ' ' << arr[i].sc / g;
            return 0;
        }
    }

    if (k == 1) {
        cout << 1 << ' ' << 2;
        return 0;
    }
    k--;

    // [mid, inf]
    for (int i = 0; i < idx; i++) {
        arr[i].fr = arr[i].sc - arr[i].fr;
        arr[i].sc;
    }

    sort(arr, arr + idx, [&](const auto& p1, const auto& p2) {
        return p1.fr * p2.sc < p2.fr * p1.sc;
    });

    if (k == 1) {
        int g = gcd(arr[0].fr, arr[0].sc);
        cout << arr[0].fr / g << ' ' << arr[0].sc / g << '\n';
        return 0;
    }
    k--;
    for (int i = 1; i < idx; i++) {
        if (arr[i - 1].fr * arr[i].sc != arr[i].fr * arr[i - 1].sc) k--;
        if (k == 0) {
            int g = gcd(arr[i].fr, arr[i].sc);
            cout << arr[i].fr / g << ' ' << arr[i].sc / g;
            return 0;
        }
    }
}