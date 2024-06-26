#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<int> a;
priority_queue<int, vector<int>, greater<int>> pq;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> k;
    a.resize(n);
    for (auto& i : a) cin >> i;

    for (int i = 0; i < k; i++) pq.push(a[i]);

    for (int i = 0; i + k < n; i++) {
        pq.push(a[i + k]);
        cout << pq.top() << ' ';
        pq.pop();
    }

    while (!pq.empty()) {
        cout << pq.top() << ' ';
        pq.pop();
    }
}