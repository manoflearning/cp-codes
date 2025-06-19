#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int N = 101;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    srand(time(NULL));

    int tc = 100;
    cout << tc << '\n';
    while (tc--) {
        int n = rand() % N + 1;

        vector<int> a(n), b(n);
        iota(all(a), 1);
        iota(all(b), 1);

        random_shuffle(all(a));
        random_shuffle(all(b));

        cout << n << '\n';
        for (auto &i : a) cout << i << ' ';
        cout << '\n';
        for (auto &i : b) cout << i << ' ';
        cout << '\n';
    }
}
