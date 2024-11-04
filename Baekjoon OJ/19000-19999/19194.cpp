#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int n;
vector<int> p;
vector<vector<int>> cyc;
int k;
vector<vector<int>> ans;

void init() {
    p.clear();
    cyc.clear();
    k = 0;
    ans.clear();
}

void input() {
    cin >> n;
    p.resize(n);
    for (auto &i : p) cin >> i;
}

void dnc(int i, int l, int r, vector<int> &arr) {
    if (l >= r) return;
    assert(i >= 0);

    int mid = (l + r) >> 1;
    
    swap(ans[i][arr[mid]], ans[i][arr[r]]);
    swap(arr[mid], arr[r]);

    dnc(i - 1, l, mid, arr);
    dnc(i - 1, mid + 1, r, arr);
}

bool is_valid() {
    vector<int> res(n), e(n);
    iota(all(res), 1);
    iota(all(e), 1);
    for (int i = 0; i < k; i++) {
        vector<int> tmp(n);
        for (int j = 0; j < n; j++)
            tmp[j] = ans[i][res[j] - 1];
        res = tmp;
        if (ans[i] == e) return 0;
    }
    return res == p;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        {
            vector<bool> vis(n);
            for (int i = 0; i < n; i++) {
                if (vis[i]) continue;
                vector<int> res;
                for (int j = i; !vis[j]; j = p[j] - 1) {
                    vis[j] = 1;
                    res.push_back(j);
                }
                cyc.push_back(res);
            }
        }
        
        {
            int mxcyc = 0;
            for (auto &i : cyc)
                mxcyc = max(mxcyc, sz(i));
            for (k = 0; (1 << k) < mxcyc; k++);
        }
        
        ans.resize(k, vector<int>(n));
        for (int i = 0; i < k; i++)
            iota(all(ans[i]), 1);
        
        for (auto &i : cyc) {
            auto tmp = i;
            dnc(k - 1, 0, sz(i) - 1, tmp);
        }

        assert(is_valid());

        cout << k << '\n';
        for (auto &i : ans) {
            for (auto &j : i) cout << j << ' ';
            cout << '\n';
        }
    }
}
