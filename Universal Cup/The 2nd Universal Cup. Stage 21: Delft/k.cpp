#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int dy[] = { 0, 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 0, 1, -1, 0, 0, 1, -1, 1, -1 };

void f(int st, int en, vector<string>& a) {
    if (en - st + 1 < 2) return;
    if (en - st + 1 == 2) {
        a[st][st] = a[st][st + 1] = '#';
        return;
    }

    for (int y = st; y + 3 <= en; y += 2) {
        a[y][st] = a[y][st + 1] = '#';
    }
    for (int y = st + 3; y <= en; y += 2) {
        a[y][en - 1] = a[y][en] = '#';
    }
    for (int x = st; x + 3 <= en; x += 2) {
        a[en - 1][x] = a[en][x] = '#';
    }
    for (int x = st + 3; x <= en; x += 2) {
        a[st][x] = a[st + 1][x] = '#';
    }

    f(st + 3, en - 3, a);
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
        int n; cin >> n;
        vector<string> a(n, string(n, '.'));

        if (n == 1) {}
        else if (n & 1) {
            for (int y = 0; y < n; y += 2) {                
                for (int x = 0; x < n; x++) {
                    if (x % 3 != 2) a[y][x] = '#';
                }
            }
            if (n % 3 == 1) {
                for (int y = 0; y < n; y++) {
                    if (y + 1 < n && y % 3 != 2) a[y][n - 1] = '#';
                    else a[y][n - 1] = '.';
                }
            }
            if (n % 3 == 0) {
                for (int y = 0; y < n; y++) {
                    if (y % 3 != 2) a[y][n - 3] = a[y][n - 1] = '#', a[y][n - 2] = '.';
                    else a[y][n - 3] = a[y][n - 2] = a[y][n - 1] = '.';
                }
            }
        }
        else if (!(n & 1)) {
            f(0, n - 1, a);
        }

        for (auto& i : a)
            cout << i << '\n';
    }
}