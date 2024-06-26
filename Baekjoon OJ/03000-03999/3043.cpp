#include <bits/stdc++.h>
using namespace std;

struct Node { int y, x, idx; };

int n, vi[505][505], idxToNode[505];
vector<Node> a;
vector<pair<int, char>> ans;

void modify(Node& it, char dir) {
    assert(vi[it.y][it.x] == it.idx);

    vi[it.y][it.x] = 0;
    if (dir == 'L') it.x--;
    if (dir == 'R') it.x++;
    if (dir == 'U') it.y--;
    if (dir == 'D') it.y++;

    assert(1 <= it.y && it.y <= n);
    assert(1 <= it.x && it.x <= n);

    if (vi[it.y][it.x]) {
        int idx = vi[it.y][it.x];
        modify(a[idxToNode[idx]], dir);
    }
    vi[it.y][it.x] = it.idx;

    ans.push_back({ it.idx, dir });
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        auto& it = a[i];
        cin >> it.y >> it.x;
        it.idx = i + 1;
        vi[it.y][it.x] = it.idx;
    }

    sort(a.begin(), a.end(), [&](const Node& n1, const Node& n2) {
        return n1.y < n2.y;
    });
    for (int i = 0; i < n; i++) idxToNode[a[i].idx] = i;

    for (int i = 0, y = 1; i < n; i++, y++) {
        auto& it = a[i];
        while (it.y < y) modify(it, 'D');
        while (y < it.y) modify(it, 'U');
    }

    sort(a.begin(), a.end(), [&](const Node& n1, const Node& n2) {
        return n1.x < n2.x;
    });
    for (int i = 0; i < n; i++) idxToNode[a[i].idx] = i;

    for (int i = 0, x = 1; i < n; i++, x++) {
        auto& it = a[i];
        while (it.x < x) modify(it, 'R');
        while (x < it.x) modify(it, 'L');
    }

    cout << ans.size() << '\n';
    for (auto& i : ans)
        cout << i.first << ' ' << i.second << '\n';
}