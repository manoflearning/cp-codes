#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
};

int n, q;
vector<Point> a;

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> q;

    a.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y;
    }

    

    return 0;
}