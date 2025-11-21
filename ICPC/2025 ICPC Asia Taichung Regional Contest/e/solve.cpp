#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

vector<vector<int>> arr[5];

void preprocess(int x) {
    vector<int> ord(x);
    iota(all(ord), 1);
    do {
        arr[x].push_back(ord);
    } while (next_permutation(all(ord)));

    sort(all(arr[x]));
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    preprocess(2);
    preprocess(3);
    preprocess(4);

    int tc; cin >> tc;
    while (tc--) {
        string n; cin >> n;

        int l = sz(n);

        int j, k;
        cin >> j >> k;
        j--, k--;

        int ans1 = 0, ans2 = 0;
        for (int p = 0; p < sz(arr[l][j]); p++) {
            for (int q = 0; q < sz(arr[l][k]); q++) {
                if (arr[l][j][p] == arr[l][k][q]) {
                    ans1 += (p == q);
                    ans2 += (p != q);
                }
            }
        }

        cout << ans1 << "A" << ans2 << "B\n";
    }
}