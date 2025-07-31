#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int query(vector<int> a) {
    cout << "? " << sz(a) << ' ';
    for (auto &i : a) cout << i << ' ';
    cout << '\n';
    cout.flush();
    
    int ret; cin >> ret;
    return ret;
}

pair<int, int> f1(int l, int r) {
    if (l + 1 == r) {
        int res = query({l, r});
        return (res == 1 ? pair<int, int>{l, r} : pair<int, int>{r, l});
    }
    
    int mid = (l + r + 1) >> 1;
    if (2 * (mid - l + 1) > 1000) mid--;
    
    vector<int> a;
    for (int i = l; i <= mid; i++) a.push_back(i);
    for (int i = l; i <= mid; i++) a.push_back(i);
    
    int res = query(a);
    
    if (res > 0) return f1(l, mid);
    else return f1(mid, r);
}

void modify(string &ans, int idx, char c) {
    ans[idx - 1] = c;
}

int main() {
    // cin.tie(NULL); cout.tie(NULL);
    // ios_base::sync_with_stdio(false);
    
    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        
        auto [l_idx, r_idx] = f1(1, n);
        
        string ans(n, '.');
        
        modify(ans, l_idx, '(');
        modify(ans, r_idx, ')');
        
        vector<int> rem;
        for (int i = 1; i <= n; i++) {
            if (i == l_idx || i == r_idx) continue;
            rem.push_back(i);
        }
        
        for (int i = 0; i + 1 < sz(rem); i += 2) {
            vector<int> a;
            a.push_back(l_idx);
            a.push_back(l_idx);
            a.push_back(rem[i]);
            a.push_back(rem[i + 1]);
            a.push_back(rem[i]);
            a.push_back(rem[i + 1]);
            a.push_back(r_idx);
            
            int res = query(a);
            
            if (res == 1) {
                // if t = "(((((()"
                modify(ans, rem[i], '(');
                modify(ans, rem[i + 1], '(');
            } else if (res == 2) {
                // if t = "(()))))"
                modify(ans, rem[i], ')');
                modify(ans, rem[i + 1], ')');
            } else if (res == 6) {
                // if t = "(()()()"
                modify(ans, rem[i], ')');
                modify(ans, rem[i + 1], '(');
            } else if (res == 4) {
                // if t = "((()())"
                modify(ans, rem[i], '(');
                modify(ans, rem[i + 1], ')');
            } else {
                assert(0);
            }
        }
        
        if (sz(rem) & 1) {
            int res = query({l_idx, rem.back()});
            modify(ans, rem.back(), res == 1 ? ')' : '(');
        }
        
        cout << "! " << ans << '\n';
        cout.flush();
    }
}
