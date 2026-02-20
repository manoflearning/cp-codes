#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;

const int inf = 1e9;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; cin >> n;

    int mny = inf; vector<pii> mnp;

    vector<pii> arr;
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        mny = min(y, mny);
        if(sz(mnp) && mnp[0].second != mny) {
            while(sz(mnp)) arr.push_back(mnp.back()), mnp.pop_back();
        }

        if(y == mny) mnp.push_back({x, y});
        else arr.push_back({x,y});
    }

    vi xrr; for(auto &[x,y]:arr) xrr.push_back(x);
    sort(all(xrr)); xrr.erase(unique(all(xrr)), xrr.end());

    sort(all(arr));

    vector<pii> ans;

    sort(all(mnp)); reverse(all(mnp));
    ans.insert(ans.end(), all(mnp));
    int j = 0;

    for(int i = 0; i < sz(xrr); i++) {
        vector<pii> adds;

        if(arr[j].second != mny + 1) adds.push_back({xrr[i], mny + 1});
        while(arr[j].first == xrr[i]) adds.push_back(arr[j++]);
        if(i + 1 < sz(xrr) && xrr[i] + 1 != xrr[i + 1]) {
            adds.push_back({xrr[i] + 1, mny + 1});
        }

        if(i + 1 == sz(xrr)) {
            if(xrr[i] == inf) {
                if(i && xrr[i] - xrr[i - 1] <= 2) {}
                else {
                    adds.push_back({xrr[i] - 1, mny + 1});
                }

                reverse(all(adds));
            }
            else {
                adds.push_back({xrr[i] + 1, mny + 1});
            }
        }

        ans.insert(ans.end(), all(adds));
    }

    if(sz(arr) == 0) {
        if(mny == inf) {
            ans.push_back({inf, mny - 1});
        }
        else {
            ans.push_back({inf, mny + 1});
        }
    }

    cout << sz(ans) << '\n';
    for(auto &[x, y] : ans) cout << x << ' ' << y << '\n';
}
