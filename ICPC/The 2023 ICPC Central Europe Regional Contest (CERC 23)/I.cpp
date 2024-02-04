// QUERY 111000
// x1 x2 x3 x4 x5 x6
// sum(xi) <= 2n - 2 - (# zeros)

// QUERY 11110000
// QUERY 11001100
// QUERY 10101010

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int n;
map<int, int> arr[16];
vector<int> idx[30303];

map<int, int> degs[30303];
set<int> queryNodes[16];

set<pii> ans;

vector<int> query(int bit, int i) {
    cout << "QUERY ";
    for (int v = 0; v < n; v++) {
        cout << (bit & v ? '0' : '1');
        if (!(bit & v)) queryNodes[i].insert(v);
    }
    cout << '\n';
    cout << flush;

    vector<int> ret;
    for (int v = 0; v < n; v++) {
        int x; cin >> x;
        ret.push_back(x);
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    // cin.tie(NULL); cout.tie(NULL);
    // ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < 16; i++) {
        int bit = (1 << i);
        auto tmp = query(bit, i);
        for (int v = 0; v < n; v++) {
            if (tmp[v] > 0) arr[i][v] = tmp[v];
        }
        
        for (int v = 0; v < n; v++) {
            if (!(bit & v)) idx[v].push_back(i);
        }
    }

    for (int v = 0; v < n; v++) {
        int u = idx[v][0];
        auto& deg = degs[v];
        deg = arr[u];
        set<int> nodes = queryNodes[u];

        for (int i = 1; i < sz(idx[v]); i++) {
            u = idx[v][i];

            vector<int> lazy;
            for (auto& it : deg) {
                if (arr[u].count(it.fr) == 0) {
                    lazy.push_back(it.fr);
                }
                else it.sc = min(it.sc, arr[u][it.fr]);
            }
            for (auto& x : lazy) deg.erase(x);
            lazy.clear();

            for (auto& it : nodes) {
                if (queryNodes[u].count(it) == 0) {
                    lazy.push_back(it);
                }
            }
            for (auto& x : lazy) nodes.erase(x);
            lazy.clear();
        }

        for (auto& i : nodes) {
            if (i == v) continue;
            vector<int> lazy;
            for (auto& it : deg) {
                if (degs[i].count(it.fr) == 0) {
                    lazy.push_back(it.fr);
                }
                else it.sc = min(it.sc, degs[i][it.fr]);
            }
            for (auto& x : lazy) deg.erase(x);
        }

        cout << v + 1 << '\n';
        for (auto& it : deg) {
            // assert(it.sc == 1);
            cout << it.fr + 1 << ' ' << it.sc << '\n';
            // cout << min(v, it.fr) + 1 << ' ' << max(v, it.fr) + 1 << '\n';
            ans.insert({ min(v, it.fr), max(v, it.fr) });
        }
    }

    cout << "ANSWER\n";
    for (auto& i : ans)
        cout << i.fr + 1 << ' ' << i.sc + 1 << '\n';
}