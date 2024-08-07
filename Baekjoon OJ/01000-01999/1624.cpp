#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second
#define all(x) (x).begin(), (x).end()

const int MAXN = 1010;

int n;
vector<int> a;

void input() {
    cin >> n;
    a.resize(n);
    for (auto& i : a) cin >> i;
}

void cc() {
    vector<int> c = a;
    sort(all(c));
    c.erase(unique(all(c)), c.end());

    for (auto& i : a)
        i = lower_bound(all(c), i) - c.begin();
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    cc();

    int ans = 0;
    
    for (int i = 0; i < n; i++) {
        int l = i, r = n - 1;
        while (l < r) {
            int j = (l + r + 1) >> 1;
            int isPos = 1;
            deque<int> dq;
            for (int k = 0; k < n; k++) {
                if (a[k] < i || j < a[k]) continue;
                if (dq.empty() || dq.back() <= a[k]) dq.push_back(a[k]);
                else if (a[k] <= dq.front()) dq.push_front(a[k]);
                else { isPos = 0; break; }
            }
            if (isPos) l = j;
            else r = j - 1;
        }
        i = l;
        ans++;
    }

    cout << ans;
}