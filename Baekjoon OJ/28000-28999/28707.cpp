#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;

int n, m;
vector<int> a;
int p10[9];
int dist[(int)1e8];
vector<pair<pair<int, int>, int>> ops;

int Hash(const vector<int>& a) {
    int ret = 0;
    for (int i = 0; i < a.size(); i++) {
        ret += p10[(int)a.size() - i - 1] * a[i];
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    // initialize
    p10[0] = 1;
    for (int i = 1; i < 8; i++) {
        p10[i] = 10 * p10[i - 1];
    }
    for (int i = 0; i < (int)1e8; i++) {
        dist[i] = INF;
    }

    // input
    cin >> n;
    a.resize(n);
    for (auto& i : a) { cin >> i; i--; }
    cin >> m;
    ops.resize(m);
    for (auto& i : ops) {
        cin >> i.first.first >> i.first.second >> i.second;
        i.first.first--;
        i.first.second--;
    }

    // dijkstra
    priority_queue<pair<int, vector<int>>, vector<pair<int, vector<int>>>, greater<pair<int, vector<int>>>> pq;
    dist[Hash(a)] = 0;
    pq.push({ dist[Hash(a)], a });

    while (!pq.empty()) {
        auto [w, v] = pq.top();
        pq.pop();

        if (w < dist[Hash(v)]) continue;

        for (auto& i : ops) {
            auto nxt = v;
            swap(nxt[i.first.first], nxt[i.first.second]);
            if (w + i.second < dist[Hash(nxt)]) {
                dist[Hash(nxt)] = w + i.second;
                pq.push({ dist[Hash(nxt)], nxt });
            }
        }
    }

    sort(a.begin(), a.end());
    cout << (dist[Hash(a)] == INF ? -1 : dist[Hash(a)]);
}