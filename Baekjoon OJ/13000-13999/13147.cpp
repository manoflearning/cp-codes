#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

int n;
vector<pair<string, string>> a;
vector<int> adj[202020];
int ind[202020];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    a.resize(n);
    for (auto& i : a) {
        char op;
        cin >> i.first >> op >> i.second;
        if (op == '>') swap(i.first, i.second);
    }

    vector<string> c;
    for (auto& i : a) {
        c.push_back(i.first);
        c.push_back(i.second);
    }

    sort(c.begin(), c.end());
    c.erase(unique(c.begin(), c.end()), c.end());

    for (auto& i : a) {
        int u = lower_bound(c.begin(), c.end(), i.first) - c.begin() + 1;
        int v = lower_bound(c.begin(), c.end(), i.second) - c.begin() + 1;
        adj[u].push_back(v);
        ind[v]++;
    }

    queue<int> qu;
    for (int v = 1; v <= sz(c); v++) {
        if (!ind[v]) qu.push(v);
    }

    while (!qu.empty()) {
        auto v = qu.front();
        qu.pop();

        for (auto& i : adj[v]) {
            ind[i]--;
            if (!ind[i]) qu.push(i);
        }
    }

    for (int v = 1; v <= sz(c); v++) {
        if (ind[v] > 0) { cout << "impossible"; exit(0); }
    }

    cout << "possible";
}