#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

int n, a[101010], k;

void print(int lb, int rb) {
    set<int> s;
    vector<int> arr;
    for (int i = 1; i <= n; i++) {
        if (lb <= a[i] && a[i] <= rb) {
            s.insert(i);
            arr.push_back(a[i]);
        }
    }
    for (int i = lb; ; i++) {
        if (!s.count(i)) {
            s.insert(i);
            arr.push_back(a[i]);
        }
        if (sz(s) == 2 * k) break;
    }
    sort(arr.begin(), arr.end());
    int idx = 0;
    for (auto& i : s) {
        cout << i << ' ';
        a[i] = arr[idx++];
    }
    cout << '\n';
    /*for (int i = 1; i <= n; i++)
        cout << a[i] << ' ';
    cout << '\n';*/
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    k = n / 4;
    cout << 3 << '\n';
    print(1, k);
    print(k + 1, 2 * k);
    print(2 * k + 1, 3 * k);
}
