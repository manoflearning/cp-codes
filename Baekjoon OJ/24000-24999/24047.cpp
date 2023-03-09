#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n, k;
int a[505050];
set<int> s;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int i = 1; i < n; i++)
        if (a[i] > a[i + 1]) s.insert(i);
    s.insert(1e9);

    int cnt = 0;
    for (int last = n; last >= 2; last--) {
        for (int lb = 1; lb < last; ) {
            int idx = *s.lower_bound(lb);
            if (idx >= last) break;
            //cout << lb << ' ' << idx << '\n';
            assert(lb <= idx);

            cnt++;
            swap(a[idx], a[idx + 1]);
            s.erase(idx);
            if (1 <= idx - 1 && a[idx - 1] > a[idx]) s.insert(idx - 1);
            if (idx + 2 <= n && a[idx + 1] > a[idx + 2]) s.insert(idx + 1);

            if (cnt == k) break;
            
            lb = idx + 1;
        }

        if (cnt == k) break;
    }

    if (cnt < k) {
        cout << -1;
        return 0;
    }

    for (int i = 1; i <= n; i++)
        cout << a[i] << ' ';
}