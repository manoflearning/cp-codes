#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e6;

int n;
vector<int> a;
int cnt[MAX + 1], ans[MAX + 1];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    a.resize(n);
    for (auto& i : a) {
        cin >> i;
        cnt[i]++;
    }

    for (int i = 1; i <= MAX; i++) {
        if (!cnt[i]) continue;
        ans[i] += cnt[i] - 1;
        for (int j = 2 * i; j <= MAX; j += i) {
            ans[j] += cnt[i];
        }
    }

    for (auto& i : a)
        cout << ans[i] << '\n';
}