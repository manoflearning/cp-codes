#include <bits/stdc++.h>
#include <random>
using namespace std;
#define all(x) (x).begin(), (x).end()

int n, m;
int a[505050];
vector<int> arr[505050];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    srand(time(NULL));

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        arr[a[i]].push_back(i);
    }

    while (m--) {
        int l, r;
        cin >> l >> r;

        int len = (r - l + 1);
        int ans = 0;
        for (int i = 0; i < 24; i++) {
            int idx = rand() % len + l;
            int v = a[idx];
            int cnt = lower_bound(all(arr[v]), r + 1) - lower_bound(all(arr[v]), l);
            if (cnt >= len / 2 + 1) ans = v;
        }
        cout << ans << '\n';
    }
}