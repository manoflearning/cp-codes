#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int N = 2020, M = 2020;
const int INF = 1e9 + 7;

constexpr int  XMIN = 1, XMAX = 2020;           // 1‑based 입력
constexpr int  YMIN = 1, YMAX = 2020;
constexpr short INF_NEG = 0;                    // max 의 항등원

/*──────────────────── 2‑D Iterative Segment Tree ───────────────────
 *  ▷ 외부( X ) : 완전이진트리 크기 2·NX  (NX = 2^⌈log2 XMAX⌉ = 2048)
 *  ▷ 내부( Y ) : 완전이진트리 크기 2·NY  (NY = 2048)
 *  ▷ 배열형태  seg[2·NX][2·NY]  → 16 779 264 개 short ≈ 32 MiB
 *  ▷ 연산복잡도  O(log X · log Y) , 재귀 호출 0
 *------------------------------------------------------------------*/
struct Seg2D {
    static constexpr int NX = 2048;           // 2^11 ≥ 2000
    static constexpr int NY = 2048;

    vector<vector<short>> seg;                // [2·NX][2·NY]

    Seg2D() : seg(2*NX, vector<short>(2*NY, INF_NEG)) {}

    /*------------ 내부(Y) 1‑D 쿼리 (비재귀) ------------*/
    inline short queryY(int xi, int ly, int ry) const {
        short ret = INF_NEG;
        int l = ly + NY, r = ry + NY + 1;     // [ly,ry] → half‑open
        while (l < r) {
            if (l & 1) ret = max(ret, seg[xi][l++]);
            if (r & 1) ret = max(ret, seg[xi][--r]);
            l >>= 1;  r >>= 1;
        }
        return ret;
    }

    /*------------ point‑update ------------*/
    void modify(int x, int y, short v) {
        /* ① 1‑based → 0‑based leaf 인덱스로 변환 */
        int xi = (x - 1) + NX;
        int yi = (y - 1) + NY;

        /* ② leaf 갱신 (값 증가형 max) */
        if (v <= seg[xi][yi]) return;         // 더 크지 않으면 조용히 종료
        seg[xi][yi] = v;

        /* ③ 같은 X‑노드에서 Y‑쪽 upward 갱신 */
        for (int yj = yi >> 1; yj; yj >>= 1)
            seg[xi][yj] = max(seg[xi][yj << 1], seg[xi][yj << 1 | 1]);

        /* ④ X‑부모들에 대해, 해당 Y‑경로만 갱신 */
        for (int xp = xi >> 1; xp; xp >>= 1) {
            seg[xp][yi] = max(seg[xp << 1][yi], seg[xp << 1 | 1][yi]);
            for (int yj = yi >> 1; yj; yj >>= 1)
                seg[xp][yj] = max(seg[xp][yj << 1], seg[xp][yj << 1 | 1]);
        }
    }

    /*------------ orthogonal range‑max ------------*/
    short query(int lx, int rx, int ly, int ry) const {
        /* ① 1‑based → 0‑based half‑open [l,r) */
        int l = (lx - 1) + NX;
        int r = rx       + NX;               // (rx‑0‑based) +1
        ly--; ry--;                           // 0‑based 내부용

        short ans = INF_NEG;

        /* ② X‑축 iterative sweep */
        while (l < r) {
            if (l & 1) ans = max(ans, queryY(l++, ly, ry));
            if (r & 1) ans = max(ans, queryY(--r, ly, ry));
            l >>= 1; r >>= 1;
        }
        return ans;
    }
} d, u;

int n, m;
int a[N], b[M], c[N];
int mx;

void coor_comp() {
    vector<int> cc;
    cc.push_back(-INF);
    for (int i = 1; i <= n; i++) {
        cc.push_back(a[i]);
    }
    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());
    for (int i = 1; i <= n; i++) {
        c[i] = lower_bound(all(cc), a[i]) - cc.begin();
    }
    mx = sz(cc) - 1;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cin >> m;
    for (int i = 1; i <= m; i++) cin >> b[i];

    coor_comp();

    int ans = 0;

    for (int i = 1; i <= n; i++) {
        for (int x = 1; x <= m; x++) {
            if (a[i] != b[x]) continue;

            int y = c[i];

            int res_u = 1 + d.query(1, x - 1, 1, y - 1);
            int res_d = 1 + u.query(1, x - 1, y + 1, mx);

            ans = max({ans, res_u, res_d});

            u.modify(x, y, res_u);
            d.modify(x, y, res_d);

            // cout << i << ' ' << x << ' ' << y << ' ' << res_u << ' ' << res_d << '\n';
        }
    }
    
    if (ans < 2) {
        // 2) 값 v가 두 수열에 최소 2개씩 존재하는지 확인
        unordered_map<long long,int> ca, cb;
        for (int i=1;i<=n;i++) ca[a[i]]++;
        for (int i=1;i<=m;i++) cb[b[i]]++;
        for (auto &p: ca)
            if (p.second >= 2 && cb[p.first] >= 2) { ans = 2; break; }
    }

    cout << ans;
}
