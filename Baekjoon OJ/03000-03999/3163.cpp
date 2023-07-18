#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fr first
#define sc second

const ll INF = 1e18;

//int nearL[101010], nearR[101010];

int n, len, m;
pair<int, int> a[101010];
int pl[101010], pr[101010];
vector<int> L, R;

void init() {
    memset(pl, 0, sizeof(pl));
    memset(pr, 0, sizeof(pr));
    L.clear();
    R.clear();
}

void input() {
    cin >> n >> len >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].fr >> a[i].sc;
    }
}

int sumr(int s, int e) { return pr[e]; }
int suml(int s, int e) { return pl[s]; }

int getTime(int x) {
    int rcnt = sumr(1, x - 1), lcnt = suml(x + 1, n);
    
    if (a[x].sc < 0) {
        if (rcnt == 0) return a[x].fr;
        else {
            if (rcnt <= lcnt) return L[lcnt - rcnt];
            else return len - R[rcnt - lcnt - 1];
        }
    }

    if (a[x].sc > 0) {
        if (lcnt == 0) return len - a[x].fr;
        else {
            if (rcnt >= lcnt) return len - R[rcnt - lcnt];
            else return L[lcnt - rcnt - 1];
        }
    }

    return -1;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        for (int i = 1; i <= n; i++) {
            pr[i] = pr[i - 1];
            if (a[i].sc > 0) {
                pr[i]++;
                R.push_back(a[i].fr);
            }
        }

        for (int i = n; i >= 1; i--) {
            pl[i] = pl[i + 1];
            if (a[i].sc < 0) {
                pl[i]++;
                L.push_back(a[i].fr);
            }
        }

        int l = 1, r = n, ans = -1;
        for (int i = 0; i < m; i++) {
            int lt = getTime(l), rt = getTime(r);
            
            //cout << l << ' ' << r << ' ';
            if (make_pair(lt, a[l].sc) <= make_pair(rt, a[r].sc)) ans = a[l++].sc;
            else ans = a[r--].sc;
            //cout << lt << ' ' << rt << ' ' << ans << '\n';
        }

        cout << ans << '\n';

        // 입력 배열 a 범위 바뀜 [0, n - 1] -> [1, n]
        /*nearL[n - 1] = (a[n - 1].sc < 0 ? n - 1 : n);
        for (int i = n - 1; i >= 0; i--) {
            nearL[i] = nearL[i + 1];
            if (a[i].sc < 0) nearL[i] = i;
        }
        nearR[0] = (a[0].sc > 0 ? 0 : -1);
        for (int i = 1; i < n; i++) {
            nearR[i] = nearR[i - 1];
            if (a[i].sc > 0) nearR[i] = i;
        }

        int l = 0, r = n - 1, ans = -1;
        for (int i = 0; i < m; i++) {
            ll lt = 0, rt = 0;

            int pl = nearL[l];
            if (n <= pl) lt = len - a[l].fr;
            else lt = a[pl].fr;
            
            int pr = nearR[r];
            if (pr < 0) rt = a[r].fr;
            else rt = len - a[pr].fr;
            
            if (make_pair(lt, a[l].sc) <= make_pair(rt, a[r].sc)) ans = a[l++].sc;
            else ans = a[r--].sc;
        }

        cout << ans << '\n';*/
    }
}