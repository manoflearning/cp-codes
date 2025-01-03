// 한 동물 점에 방문하면 w까지 머물러 있는게 최적
// 한 동물 점은 한 번만 방문하는 것이 최적
// wi 기준 오름차순 정렬해서 차례로 방문하기
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(a) (int)(a).size()

struct Animal {
    int x, y;
    ll v, w;
    bool operator<(const Animal& rhs) const {
        return w < rhs.w;
    }
};

int n;
vector<Animal> a;
int dp[5050];

void input() {
    cin >> n;
    a.resize(n);
    for (auto& i : a) cin >> i.x >> i.y;
    for (auto& i : a) cin >> i.v >> i.w;
    a.push_back({ 0, 0, 0, 0 });
}

int dist(int i, int j) {
    return abs(a[i].x - a[j].x) + abs(a[i].y - a[j].y);
}

void bottomup() {
    memset(dp, -1, sizeof(dp));
    dp[0] = 0;
    for (int i = 1; i < sz(a); i++) {
        for (int j = 0; j < i; j++) {
            int d = dist(i, j);
            if (a[i].w - a[j].w < d) continue;
            if (dp[j] == -1) continue;
            int res = dp[j];
            res += a[i].w - max(a[i].v, a[j].w + d);
            dp[i] = max(dp[i], res);
        }
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

    sort(a.begin(), a.end());

    bottomup();

    int ans = 0;
    for (int i = 0; i < sz(a); i++) {
        ans = max(ans, dp[i]);
    }

    cout << ans;
}