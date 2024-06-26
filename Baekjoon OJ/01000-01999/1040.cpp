#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

ll n;
int k;

vector<int> a;
int aCnt = 0;

void pre() {
    string s = to_string(n);
    for (int i = 0; i < sz(s); i++)
        a.push_back(s[i] - '0');

    vector<int> vi(10);
    for (auto& i : a) {
        if (!vi[i]) vi[i] = 1, aCnt++;
    }
}

vector<int> val, ans;

int valCnt = 0;
vector<int> valVi(10);
void add(int x) {
    val.push_back(x);
    if (!valVi[x]) valCnt++;
    valVi[x]++;
}
void del() {
    int x = val.back();
    val.pop_back();
    valVi[x]--;
    if (!valVi[x]) valCnt--;
}

vector<int> getRem() {
    int mn = 10;
    vector<int> mustAdd;
    for (int i = 0; i <= 9; i++) {
        if (valVi[i]) mn = min(mn, i);
        else mustAdd.push_back(i);
    }
    
    if (k - valCnt > sz(a) - sz(val)) return vector<int>(1, 0);

    mustAdd.resize(k - valCnt);
    if (sz(mustAdd)) mn = min(mn, mustAdd[0]);

    vector<int> ret = val;
    for (auto& i : mustAdd) ret.push_back(i);
    while (sz(ret) < sz(a)) ret.push_back(mn);
    sort(ret.begin() + sz(val), ret.end());

    return ret;
}

int isValidAns(const vector<int>& arr) {
    int cnt = 0;
    vector<int> vi(10);
    for (auto& i : arr) if (!vi[i]) cnt++, vi[i] = 1;
    if (cnt != k) return 0;

    if (sz(arr) != sz(a)) return 0;

    if (arr <= a) return 0;

    return 1;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> k;

    pre();

    if (aCnt == k) {
        cout << n;
        return 0;
    }
    if (sz(a) < k) {
        cout << 10;
        for (int i = 2; i < k; i++) cout << i;
        return 0;
    }
 
    // now ans should be strictly bigger than n (ans > n)

    // if sz(a) + 1 == sz(ans)
    ans.push_back(1);
    for (int i = 0; i < (sz(a) + 1) - (k - 1); i++) ans.push_back(0);
    for (int i = 2; i < k; i++) ans.push_back(i);

    // if sz(a) == sz(ans)
    for (int i = 0; i < sz(a); i++) {
        if (valCnt > k) break;
        
        for (int x = a[i] + 1; x <= 9; x++) {
            add(x);
            if (valCnt <= k) {
                vector<int> res = getRem();
                if (isValidAns(res)) {
                    if (sz(res) == sz(ans)) ans = min(ans, res);
                    else ans = res;
                }
            }
            del();
        }
        add(a[i]);
    }

    for (auto& i : ans) cout << i;
}