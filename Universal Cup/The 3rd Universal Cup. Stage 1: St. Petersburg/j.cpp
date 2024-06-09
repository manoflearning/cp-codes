#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int ANS = 1e9;

int n, sum = 0;
vector<pair<int, int>> a;
vector<int> res;

int iter = 0;
void naive(int i) {
    if (sum == ANS) {
        cout << sz(res) << ' ';
        for (auto& i : res) cout << i << ' ';
        exit(0);
    }

    if (iter++ >= 1e4) return;
    if (i == sz(a)) return;

    if (sum + a[i].first <= ANS) {
        res.push_back(a[i].second);
        sum += a[i].first;
        naive(i + 1);
        sum -= a[i].first;
        res.pop_back();
    }
    
    naive(i + 1);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    srand(time(NULL));

    cin >> n;

    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i + 1;
    }

    while (1) {
        random_shuffle(all(a));

        iter = 0;

        naive(0);
    }
}