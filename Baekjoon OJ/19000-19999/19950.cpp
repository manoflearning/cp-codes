#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll sx, sy, sz, ex, ey, ez, d = 0;
int n;
vector<int> a;
ll sum = 0;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> sx >> sy >> sz >> ex >> ey >> ez;
    cin >> n;
    a.resize(n);
    for (auto& i : a) cin >> i;

    d += abs(sx - ex) * abs(sx - ex);
    d += abs(sy - ey) * abs(sy - ey);
    d += abs(sz - ez) * abs(sz - ez);

    for (auto& i : a) sum += i;

    sort(a.rbegin(), a.rend());
    if (sum * sum >= d) {
        if (2 * a[0] - sum < 0 || (2 * a[0] - sum) * (2 * a[0] - sum) <= d) cout << "YES";
        else cout << "NO";
    }
    else cout << "NO";
}