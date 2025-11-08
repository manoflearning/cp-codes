#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int MOD = 998'244'353;
constexpr int N = 202020;

int d, n;
int l[N], r[N], c[N];
int psum[2 * N];

void input() {
    cin >> d >> n;
    for (int i = 1; i <= n; i++) {
        cin >> l[i] >> r[i] >> c[i];
    }
}

vector<int> cc;
void coor_comp() {
    cc.push_back(-1);
    for (int i = 1; i <= n; i++) {
        cc.push_back(l[i]);
        cc.push_back(r[i]);
    }
    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());
    for (int i = 1; i <= n; i++) {
        l[i] = lower_bound(all(cc), l[i]) - cc.begin();
        r[i] = lower_bound(all(cc), r[i]) - cc.begin();
    }
    d = sz(cc) - 1;
}

void build_psum() {
    for (int i = 1; i <= n; i++) {
        psum[l[i]]++;
        psum[r[i] + 1]--;
    }
    for (int i = 0; i <= d; i++) {
        psum[i] += psum[i - 1];
    }
}

map<int, pii> mp_st_co, mp_en_co;
void solve() {
    for (int i = 1; i <= n; i++) {
        mp_st_co[{l[i], c[i]}]++;
        mp_en_co[{r[i], c[i]}]++;
    }

    map<int, int> acc_co1, acc_co2;
    for (int i = 1; i + 1 <= d; i++) {
        acc_co1[i] += mp_st
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    input();

    coor_comp();

    build_psum();


}
