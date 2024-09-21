#include <bits/stdc++.h>
using namespace std;

const int MAXN = 101010;

bool is_valid(int l, int r, const vector<int>& arr) {
    bool is_increasing = 1, is_decreasing = 1;
    for (int i = l; i + 1 <= r; i++) {
        is_increasing &= (arr[i] < arr[i + 1]);
        is_decreasing &= (arr[i] > arr[i + 1]);
    }
    return is_increasing || is_decreasing;
}

void yes() {
    cout << "POSSIBLE";
    exit(0);
}
void no() {
    cout << "IMPOSSIBLE";
    exit(0);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n; cin >> n;

    vector<int> a(MAXN), b(MAXN);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    int s = 1, e = n;
    while (s <= n && a[s] == b[s]) s++;
    while (1 <= e && a[e] == b[e]) e--;

    if (s > e) yes();

    if (s + 1 == e) {
        if (1 < s && is_valid(s - 1, e, b)) yes();
        if (e < n && is_valid(s, e + 1, b)) yes();
        no();
    }

    if (1 < s && is_valid(s - 1, e, b)) yes();
    if (e < n && is_valid(s, e + 1, b)) yes();
    
    for (int i = s; i + 2 <= e; i++) {
        if (is_valid(i, i + 2, b)) yes();
    }
    
    no();
}
