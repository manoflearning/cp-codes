#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
};

struct Query {
    int l, r, x, idx;
    bool operator<(const Query& rhs) {
        return x < rhs.x;
    }
};

int n, q;
vector<Point> a;

vector<Query> b;
vector<int> ans;

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> q;

    a.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y;
    }

    b.resize(q);
    ans.resize(q);
    for (int i = 0; i < q; i++) {
        cin >> b[i].l >> b[i].r >> b[i].x;
        b[i].idx = i;
    }

    sort(b.begin(), b.end());

    for (int i = 0; i < q; i++) {
        if (i == 0 || b[i].x > b[i - 1].x) {
            if (i == 0) ;
            else ;
        }
    }

    return 0;
}