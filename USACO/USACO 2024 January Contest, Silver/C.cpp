// a[i] = pL + q (p >= 4, at most 3 distinct q)

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const ll INF = 1e18;

int n;
vector<ll> a;
ll ub = INF;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    a.resize(n);
    for (auto& i : a) {
        cin >> i;
        ub = min(ub, i / 4);
    }

    sort(all(a));
    a.erase(unique(all(a)), a.end());

    n = sz(a);

    for (auto& i : a) cout << i << '\n';

    vector<ll> diffs;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            diffs.push_back(a[j] - a[i]);
        }
    }

    sort(all(diffs));
    for (auto& i : diffs) cout << i << ' ';
}