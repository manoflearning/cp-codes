#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()

int n;
vector<pair<string, string>> a;
vector<string> c;
vector<int> vi;

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
        cin >> i.first;
        cin >> i.second;
        c.push_back(i.first);
        c.push_back(i.second);
    }

    sort(c.begin(), c.end());
    c.erase(unique(all(c)), c.end());

    vi.resize(c.size());

    vi[lower_bound(all(c), "ChongChong") - c.begin()] = 1;

    for (auto& i : a) {
        int u = lower_bound(all(c), i.first) - c.begin();
        int v = lower_bound(all(c), i.second) - c.begin();

        int b1 = vi[u], b2 = vi[v];
        if (b1) vi[v] = 1;
        if (b2) vi[u] = 1;
    }

    int ans = 0;
    for (int i = 0; i < c.size(); i++) {
        ans += vi[i];
    }

    cout << ans;

    return 0;
}