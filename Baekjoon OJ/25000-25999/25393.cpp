#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define sz(x) (int)(x).size()

int n;
vector<int> L[1010101], R[1010101];

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        L[l].push_back(r);
        R[r].push_back(-l);
    }

    for (int i = 0; i < 1010101; i++) {
        sort(L[i].begin(), L[i].end());
        sort(R[i].begin(), R[i].end());
    }

    int q; cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;

        int idxl = lower_bound(L[l].begin(), L[l].end(), r) - L[l].begin();
        int idxr = lower_bound(R[r].begin(), R[r].end(), -l) - R[r].begin();

        if (idxl < sz(L[l]) && L[l][idxl] == r) cout << 1 << '\n';
        //else if (idxr < sz(R[r]) && R[r][idxr] == -l) cout << 1 << '\n';
        else if (idxl == sz(L[l]) || idxr == sz(R[r])) cout << -1 << '\n';
        else cout << 2 << '\n';
    }

    return 0;
}