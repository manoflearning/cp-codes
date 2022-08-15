#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>

const int MOD = 1e9 + 7;

int n;
ll x0, a, b;
int l[1010], r[1010];

int qcnt;
vector<int> q;
ll ans;

void init() {
    for (int i = 0; i < 1010; i++) r[i] = MOD;
}

void input() {
    cin >> n >> x0 >> a >> b;
    cin >> qcnt;
    q.resize(qcnt);
    for (auto& i : q) cin >> i;
}

void pbs() {
    while (1) {
        vector<pii> arr;
        for (int i = 0; i < qcnt; i++) {
            if (l[i] == r[i]) continue;
            int mid = (l[i] + r[i]) >> 1;
            arr.push_back({ mid, i });
        }

        sort(arr.begin(), arr.end());

        
    }
}

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    init();

    input();

    pbs();

    return 0;
}