#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int n;
ll A, B;
vector<ll> a;
vector<vector<ll>> ptt;

void init() {
    ptt.clear();
    ptt.shrink_to_fit();
}

void input() {
    cin >> n >> A >> B;
    a.resize(2 * n);
    for (auto& i : a) cin >> i;
}

int solve() {
    vector<ll> tmp;
    for (auto& i : a) {
        if (!tmp.empty() && i - tmp.back() > B) {
            ptt.push_back(tmp);
            tmp.clear();
        }
        tmp.push_back(i);
    }
    ptt.push_back(tmp);
    tmp.clear();
    tmp.shrink_to_fit();

    int ret = 0;
    queue<ll> que;
    for (int i = 0; i < sz(ptt); i++) {
        auto& dq_now = ptt[i];
        int s = 0, e = sz(dq_now) - 1;
        while (!que.empty() && (i + 1 == sz(ptt) || ptt[i + 1][0] - que.front() > A)) {
            if (s <= e && dq_now[s] - que.front() <= A) {
                s++;
                que.pop();
            }
            else return -1;
        }

        ret += (e - s + 1) / 2;
        if ((e - s + 1) & 1) {
            if (!que.empty() && dq_now[s] - que.front() <= A) que.pop();
            else que.push(dq_now[e]);
        }
    }
    if (sz(que)) return -1;

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();
        
        input();

        sort(all(a));

        cout << solve() << '\n';
    }
}