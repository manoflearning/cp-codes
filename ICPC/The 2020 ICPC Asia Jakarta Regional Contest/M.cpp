#include <bits/stdc++.h>
using namespace std;

const int INF = 1e8;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n; cin >> n;

    int maxX, minX;
    int maxY, minY;
    maxX = maxY = -INF;
    minX = minY = INF;

    while (n--) {
        int x, y; cin >> x >> y;
        maxX = max(maxX, x);
        minX = min(minX, x);
        maxY = max(maxY, y);
        minY = min(minY, y);
    }

    int L = (maxX - minX + 1) / 2;
    int W = (maxY - minY + 1) / 2;

    cout << L << ' ' << W << '\n';
}