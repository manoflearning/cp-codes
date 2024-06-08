#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type, less_equal<int>, rb_tree_tag,tree_order_statistics_node_update>

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int N = 101010, R = 101010;

int n, k;
int r[N];
vector<int> rev_r[R];
string s;

set<int> st0;
ordered_set du;
vector<ordered_set> acc;
map<pair<int, int>, int> mp;

int ans = 0;

void input() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> r[i];
        rev_r[r[i]].push_back(i);
    }
    cin >> s;
    s = "0" + s;
}

int rightmost(int ub) { // [1, ub]
    auto it = st0.upper_bound(ub);
    it--;
    return *it;
}
int leftmost(int lb) { // [lb, N]
    auto it = st0.lower_bound(lb);
    return *it;
}

void modify_ans(int idx, int lb) {
    if (sz(acc[idx]) < k) return;
	
	// for (auto& i : acc[idx]) cout << i << ' ';
	// cout << '\n';
	
    int res = *acc[idx].find_by_order(sz(acc[idx]) - k);
	
	// cout << res << '\n';
    if (lb <= res) ans = max(ans, res);
}

int main() {
//     #ifndef ONLINE_JUDGE
//     freopen("input.txt", "r", stdin);
//     freopen("output.txt", "w", stdout);
//     #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    st0.insert(0);
    for (int i = 1; i <= n; i++) {
        if (s[i] == '0') st0.insert(i);
    }
    st0.insert(n + 1);

    acc.push_back(du);
    for (int i = 1; i <= n; ) {
        if (s[i] == '0') i++;
        else {
            int ss = rightmost(i - 1) + 1;
            int ee = leftmost(i + 1) - 1;

            ordered_set x;
            for (int j = ss; j <= ee; j++) x.insert(r[j]);

            mp[{ ss, ee }] = sz(acc);
            acc.push_back(x);

            modify_ans(mp[{ ss, ee }], 1);

            i = ee + 1;
        }
    }

    for (int i = 1; i < R; i++) {
        for (auto& j : rev_r[i]) {
            if (s[j] == '0') {
                int ss = rightmost(j - 1) + 1;
                int ee = leftmost(j + 1) - 1;

                ordered_set& stl = acc[mp[{ ss, j - 1 }]];
                ordered_set& str = acc[mp[{ j + 1, ee }]];

                if (sz(stl) <= sz(str)) {
                    for (auto& p : stl) str.insert(p);
                    stl.clear();
                    mp[{ ss, ee }] = mp[{ j + 1, ee }];
                }
                else {
                    for (auto& p : str) stl.insert(p);
                    str.clear();
                    mp[{ ss, ee }] = mp[{ ss, j - 1 }];
                }

                st0.erase(j);
            }
        }

        for (auto& j : rev_r[i]) {
            if (s[j] != '0') continue;

            int ss = rightmost(j - 1) + 1;
            int ee = leftmost(j + 1) - 1;

            modify_ans(mp[{ ss, ee }], i + 1);
        }
    }

    cout << ans;
}