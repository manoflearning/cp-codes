// b1, b2, ..., bn 순으로 왼쪽부터 오른쪽으로 값을 배치할 때,

// 1. bi in {bj | j < i}
// 1.1. bi = bj (j < i)인 j가 unique
// 
// 1.2. bi = bj (j < i)인 j가 두 개 이상
// 
// 2. otherwise
// 

// 싱힌: (n + 1) / 2 * (n / 2)

// 상한인 경우의 해 예시:
// 1 2 ... n 1 2 ... n
// 1 2 ... n n n-1 ... 1
// 

// 관찰:

// 어떤 두 구간이 교집합이 0이어서는 안된다.

// 

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int N = 202020;
const ll INF = 1e18;

// int flag;    // array size
// struct Seg { // 1-indexed
//   vector<ll> t;
//   void init() { t.clear(); }
//   void build(int n) {
//     for (flag = 1; flag < n; flag <<= 1);
//     t.resize(2 * flag, INF);
//   }
//   void modify(int p, ll value) {
//     for (t[p += flag - 1] = value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
//   }
//   ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) { // sum on interval [l, r]
//     if (r < nl || nr < l) return INF;
//     if (l <= nl && nr <= r) return t[n];
//     int mid = (nl + nr) / 2;
//     return min(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
//   }
// } seg;

int n;
vector<int> a;
vector<int> ra[N];

void init() {
    for (int i = 1; i <= n; i++) {
        ra[i].clear();
    }
}

void input() {
    cin >> n;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
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

        for (int i = 1; i <= n; i++) {
            if (a[i] > n / 2) a[i] = n / 2;
        }

        for (int i = 1; i <= n; i++) {
            ra[a[i]].push_back(i);
        }

        ll ans = 0;
        set<int> st;

        vector<pii> ranges;
        for (int x = n / 2; x >= 1; x--) {
            for (auto &i : ra[x]) st.insert(i);

            if (sz(st) <= 1) continue;

            int lb = *st.begin();
            int ub = *st.rbegin();
            
            // cout << x << ' ' << lb << ' ' << ub << '\n';
            // if (lb + 1 == ub && (n / 2 < lb || ub <= n / 2) && x > 1 && sz(st) <= 3) continue;
            if ((n / 2 < lb || ub <= n / 2) && sz(st) <= 3) continue;
            // cout << x << ' ' << lb << ' ' << ub << '\n';
            ranges.push_back({lb, ub});

            st.erase(lb);
            st.erase(ub);

            ans += ub - lb;
        }

        sort(all(ranges));

        priority_queue<int, vector<int>, greater<int>> pq;

        for (auto &[l, r] : ranges) {
            pq.push(r);
        }

        reverse(all(ranges));
        
        for (auto &[l, r] : ranges) {
            // cout << l << ' ' << r << '\n';
            if (!pq.empty() && pq.top() < l) {
                ans += l - pq.top();
                pq.pop();
                // pq.push(l);
            }
        }

        

        cout << ans << '\n';
    }
}

// 8
// 1 5 2 8 4 1 4 2
// 1 4 2 4 4 1 4 2
// ? 4 ? ? ? ? 4 ?
// ? 4 ? 3 3 ? 4 ?