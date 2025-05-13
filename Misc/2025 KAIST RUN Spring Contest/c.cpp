// 문명이 존재한다 <=>
// A[i] == 0인 i가 2 이상이어야 함

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int N = 101010;

int n;
vector<int> a(N);
vector<pii> ans;

void print(int u, int v) {
    if (u > v) swap(u, v);
    ans.push_back({u, v});
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<int> ord;
    for (int i = 1; i <= n; i++)
        ord.push_back(i);

    sort(all(ord), [&](int p1, int p2) {
        return (a[p1] ^ a[p2] ? a[p1] < a[p2] : p1 < p2);
    });

    if (a[ord[1]] >= 1) {
        cout << -1;
        exit(0);
    }

    for (int i = 2; i < n; i++) {
        int l = i / 2;
        if (l < a[ord[i]]) {
            cout << -1;
            exit(0);
        }

        print(ord[i - 2], ord[i]);
    }
    print(ord[n - 2], ord[n - 1]);

    for (auto &[u, v] : ans) {
        cout << u << ' ' << v << '\n';
    }
}
