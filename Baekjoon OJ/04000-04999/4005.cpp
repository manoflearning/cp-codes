#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9;

int n, m, k;
vector<tuple<int, int, int>> co;

void input() {
    cin >> n >> m >> k;
    for (int i = 0; i < k; i++) {
        int y, x, w;
        cin >> y >> x >> w;
        co.push_back({y, x, w});
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    
        
}
