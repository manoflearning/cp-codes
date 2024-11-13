#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 101010;

int n, a[MAXN];
vector<int> idxs;
bool vis[MAXN];

vector<int> get_answer() {
    vector<int> ret(n + 2);

    priority_queue<int> pq;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) pq.push(i);
    }

    vector<pii> rg;
    for (int i = 0; i + 1 < sz(idxs); i++) {
        rg.push_back({idxs[i], idxs[i + 1]});
    }

    sort(all(rg), [&](const pii &p1, const pii &p2) {
        if (max(a[p1.fr], a[p1.sc]) ^ max(a[p2.fr], a[p2.sc]))
            return max(a[p1.fr], a[p1.sc]) > max(a[p2.fr], a[p2.sc]);
        else return min(a[p1.fr], a[p1.sc]) > min(a[p2.fr], a[p2.sc]);
    });

    for (auto [l, r] : rg) {
        ret[l] = a[l];
        ret[r] = a[r];
        if (a[l] > a[r]) {
            for (int i = l + 1; i < r; i++) {
                ret[i] = pq.top();
                pq.pop();
            }
        } else {
            for (int i = r - 1; i > l; i--) {
                ret[i] = pq.top();
                pq.pop();
            }
        }
    }

    bool is_valid = 1;

    bool is_inc = 1;
    for (int i = 1; i + 1 <= n; i++) {
        if (!ret[i]) { is_valid = 0; break; }

        if (is_inc) {
            if (ret[i] < ret[i + 1]) continue;
            else is_inc = 0;
        } else {
            if (ret[i] < ret[i + 1]) { is_valid = 0; break; }
            else continue;
        }
    }

    if (is_valid) return ret;
    else return vector<int>();
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    idxs.push_back(0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i]) {
            idxs.push_back(i);
            vis[a[i]] = 1;
        }
    }
    idxs.push_back(n + 1);

    vector<vector<int>> ans;

    a[0] = -1, a[n + 1] = 0;
    ans.push_back(get_answer());
    a[0] = 0, a[n + 1] = -1;
    ans.push_back(get_answer());
    
    a[0] = 0, a[n + 1] = n + 1;
    ans.push_back(get_answer());
    a[0] = n + 1, a[n + 1] = 0;
    ans.push_back(get_answer());

    a[0] = n + 1, a[n + 1] = n + 2;
    ans.push_back(get_answer());
    a[0] = n + 2, a[n + 1] = n + 1;
    ans.push_back(get_answer());

    for (auto &x : ans) {
        if (x.empty()) continue;
        for (int i = 1; i <= n; i++) cout << x[i] << ' ';
        exit(0);
    }

    cout << "*";
}
