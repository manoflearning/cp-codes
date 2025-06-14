#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, q;
    cin >> n >> q;

    vector<int> box(n + 1);

    vector<int> x(q);
    for (auto &i : x) {
        cin >> i;
        if (i >= 1) {
            box[i]++;
            cout << i << ' ';
        }
        else {
            int opt = 1;
            for (int j = 2; j <= n; j++) {
                if (box[opt] > box[j]) opt = j;
            }
            box[opt]++;
            cout << opt << ' ';
        }
    }
}
