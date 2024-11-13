#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 101010;
const ll INF = 1e18;

int n, a[MAXN];
bool vis[MAXN];
vector<int> idxs;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i]) {
            vis[a[i]] = 1;
            idxs.push_back(i);
        }
    }

    int l = 1, r = n;
    int mn = 1;

    int s = 1, e = n;
    while (l <= r) {
        if (!a[l] && !a[r]) {
            s = max(s, l);
            e = min(e, r);
            while (!a[s] && s <= n) s++;
            while (!a[e] && 1 <= e) e--;

            while (vis[mn]) mn++;

            if (s < e) {
                if (a[s] < a[e]) a[l++] = mn;
                else a[r--] = mn;
            } else {
                if (s == e) {
                    if (abs(s - l) > abs(e - r)) a[l++] = mn;
                    else a[r--] = mn;
                }
                else a[l++] = mn;
            }
        } else if (!a[l]) {
            if (a[r] == mn) r--;
            else a[l++] = mn;
        } else if (!a[r]) {
            if (a[l] == mn) l++;
            else a[r--] = mn;
        } else {
            if (a[l] == mn) l++;
            else if (a[r] == mn) r--;
            else {
                cout << "*";
                exit(0);
            }
        }

        for (int i = 1; i <= n; i++) {
            cout << a[i] << ' ';
        }
        cout << '\n';

        mn++;
    }

    for (int i = 1; i <= n; i++) {
        cout << a[i] << ' ';
    }
}
