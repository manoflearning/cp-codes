#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

int n, m;
pii a[101010];
multiset<int> L, R;

int maxL() { auto it = L.end(); it--; return *it; }
int minR() { return *R.begin(); }

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    // input
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i].fr >> a[i].sc;
    
    // solve
    int ans1 = 0;
    vector<pii> arr;

    int e = 0;
    L.insert(0);
    R.insert(m + 1);
    for (int s = 1; s <= n; s++) { // [s, e]
        while (e < n && max(a[e + 1].fr, maxL()) <= min(a[e + 1].sc, minR())) {
            L.insert(a[e + 1].fr);
            R.insert(a[e + 1].sc);
            e++;
        }

        assert(s <= e);

        if (ans1 < e - s + 1) {
            ans1 = e - s + 1;
            arr.clear();
            arr.push_back({ maxL(), minR() });
        }
        else if (ans1 == e - s + 1) {
            arr.push_back({ maxL(), minR() });
        }

        L.erase(L.find(a[s].fr));
        R.erase(R.find(a[s].sc));
    }

    // get size of union
    int ans2 = 0; 
    sort(arr.begin(), arr.end());
    ans2 += arr[0].sc - arr[0].fr + 1;
    int mxe = arr[0].sc;
    for (int i = 1; i < sz(arr); i++) {
        if (mxe < arr[i].fr) {
            ans2 += arr[i].sc - arr[i].fr + 1;
            mxe = arr[i].sc;
        }
        else if (mxe < arr[i].sc) {
            ans2 += arr[i].sc - mxe;
            mxe = arr[i].sc;
        }
    }
    
    cout << ans1 << ' ' << ans2;
}