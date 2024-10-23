#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()

const int SQ = 373;

int n, a[101010];
vector<int> bu[101010 / SQ];

void update(int i, int k) { // O(sqrt(n) log n)
    auto it = lower_bound(all(bu[i / SQ]), a[i]);
    *it = a[i] = k;
    sort(all(bu[i / SQ]));
}
int query(int i, int j, int k) { // O(sqrt(n) log n)
    int ret = 0;
    if (i / SQ == j / SQ) {
        for (int p = i; p <= j; p++) ret += (a[p] > k);
    } else {
        for (int p = i; p < (i / SQ + 1) * SQ; p++) ret += (a[p] > k);
        for (int p = i / SQ + 1; p <= j / SQ - 1; p++)
            ret += bu[p].end() - upper_bound(all(bu[p]), k);
        for (int p = j / SQ * SQ; p <= j; p++) ret += (a[p] > k);
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        bu[i / SQ].push_back(a[i]);
    }
    for (int i = 0; i < 101010 / SQ; i++) sort(all(bu[i]));

    int q; cin >> q;
    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int i, j, k;
            cin >> i >> j >> k;
            cout << query(i - 1, j - 1, k) << '\n';
        }
        if (op == 2) {
            int i, k;
            cin >> i >> k;
            update(i - 1, k);
        }
    }
}
