#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()
#define pii pair<int, int>
#define fr first
#define sc second

const int INF = 1e9 + 7;

// Fenwick 구조체 코드 출처
// : https://github.com/manoflearning/cp-reference-codes/blob/master/reference-codes/1-data-structure/fenwick-tree/fenwick_tree.cpp
struct Fenwick { // 0-indexed
	int flag, cnt; // array size
	vector<ll> arr, t;
	void build(int n) {
        cnt = 0;
        arr.clear(); t.clear();
		for (flag = 1; flag < n; flag <<= 1, cnt++);
		arr.resize(flag); t.resize(flag);
	}
	void add(int p) { // add value at position p
		arr[p]++;
		while (p < flag) { t[p]++; p |= p + 1; }
	}
	ll query(int x) {
		ll ret = 0;
		while (x >= 0) ret += t[x], x = (x & (x + 1)) - 1;
		return ret;
	}
	ll query(int l, int r) { return query(r) - (l ? query(l - 1) : 0); }
}fw;

// Seg 구조체 코드 출처
// : https://github.com/manoflearning/cp-reference-codes/blob/master/reference-codes/1-data-structure/segment-tree/segment_tree_iterative.cpp
// struct Seg {  // 0-indexed
// 	int n;  // array size
// 	int t[2020202];
//     void clear() {
//         for (int i = 1; i < 2 * n; i++) t[i] = INF;
//     }
// 	void build(int N) { n = N; }
// 	void modify(int p, int value) {  // set value at position p
// 		for (t[p += n] = value; p > 1; p >>= 1) t[p >> 1] = min(t[p], t[p ^ 1]);
// 	}
// 	int query(int l, int r) {  // sum on interval [l, r)
// 		int ret = INF;
// 		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
// 			if (l & 1) ret = min(ret, t[l++]);
// 			if (r & 1) ret = min(ret, t[--r]);
// 		}
// 		return ret;
// 	}
// }seg;

int n;
string s;

void init() {
    // seg.clear();
}

ll naive() {
    int ret = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int cnt1 = 0, cnt2 = 0;
            int isAns = 1;
            for (int k = i; k <= j; k++) {
                if (s[k] == '(') cnt1++;
                else if (s[k] == ')') {
                    if (cnt1 > 0) cnt1--;
                    else { isAns = 0; break; }
                }
                else if (s[k] == '{') cnt2++;
                else if (s[k] == '}') {
                    if (cnt2 > 0) cnt2--;
                    else { isAns = 0; break; }
                }
            }
            if (cnt1 > 0 || cnt2 > 0) isAns = 0;
            if (isAns) ret++;
        }
    }
    return ret;
}

void input() { cin >> n >> s; }

bool isGroup1() { return n <= 200; }
bool isGroup2() {
    for (auto& c : s) {
        if (c == '{' || c == '}') return false;
    }
    return true;
}

ll group1() {
    ll ret = 0;

    vector<int> psum1(n + 1), psum2(n + 1);
    for (int i = 0; i < n; i++) {
        psum1[i + 1] = (s[i] == '(' ? 1 : (s[i] == ')' ? -1 : 0)) + psum1[i];
        psum2[i + 1] = (s[i] == '{' ? 1 : (s[i] == '}' ? -1 : 0)) + psum2[i];
    }

    for (int i = 0; i < n; i++) {
        int pmn1 = INF, pmn2 = INF;
        for (int j = i; j < n; j++) {
            pmn1 = min(pmn1, psum1[j]);
            pmn2 = min(pmn2, psum2[j]);

            if (psum1[j + 1] != psum1[i] || psum2[j + 1] != psum2[i]) continue;
            if (pmn1 < psum1[i] || pmn2 < psum2[i]) continue;

            ret++;
        }
    }
    return ret;
}

ll group2() {
    ll ret = 0;

    vector<int> psum(n + 1);
    for (int i = 0; i < n; i++) {
        psum[i + 1] = (s[i] == '(' ? 1 : (s[i] == ')' ? -1 : 0)) + psum[i];
    }

    vector<pii> ord;
    for (int i = 0; i <= n; i++) {
        ord.push_back({ psum[i], i });
    }

    sort(all(ord));

    fw.build(n + 1);

    ll cnt = 1;
    int prv = ord[0].sc, prvDiff = ord[0].fr;
    fw.add(prv);
    for (int i = 1; i < sz(ord); i++) {
        int now = ord[i].sc, nowDiff = ord[i].fr;
        if (fw.query(prv + 1, now - 1) || nowDiff != prvDiff) {
            ret += cnt * (cnt - 1) / 2; cnt = 0; 
        }
        cnt++;
        prv = now, prvDiff = nowDiff;
        fw.add(prv);
    }
    if (cnt) ret += cnt * (cnt - 1) / 2;

    return ret;
}

// ll group3() {
//     ll ret = 0;

//     seg.build(n + 1);

//     vector<int> psum1(n + 1), psum2(n + 1);
//     seg.modify(0, psum2[0]);
//     for (int i = 0; i < n; i++) {
//         psum1[i + 1] = (s[i] == '(' ? 1 : (s[i] == ')' ? -1 : 0)) + psum1[i];
//         psum2[i + 1] = (s[i] == '{' ? 1 : (s[i] == '}' ? -1 : 0)) + psum2[i];
//         seg.modify(i + 1, psum2[i + 1]);
//     }

//     vector<int> ord;
//     for (int i = 0; i <= n; i++) ord.push_back(i);
//     sort(all(ord), [&](const int p1, const int p2) {
//         return ((psum1[p1] ^ psum1[p2]) ? psum1[p1] < psum1[p2] : p1 < p2);
//     });

//     fw.build(n + 1);

//     ll cnt = 1;
//     int prv = ord[0];
//     fw.add(prv);
//     for (int i = 1; i < sz(ord); i++) {
//         int now = ord[i];
//         if (psum1[prv] != psum1[now] ||
//         psum2[prv] != psum2[now] ||
//         fw.query(prv + 1, now - 1) ||
//         seg.query(prv + 1, now) < psum2[now]) {
//             ret += cnt * (cnt - 1) / 2; cnt = 0; 
//         }
//         cnt++;
//         prv = now;
//         fw.add(prv);
//     }
//     if (cnt) ret += cnt * (cnt - 1) / 2;

//     return ret;
// }

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    // for (int i = 0; i < 2020202; i++) seg.t[i] = INF;

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << endl;

        init();

        input();
        
        if (isGroup1()) cout << group1() << endl;
        else if (isGroup2()) cout << group2() << endl;
        else cout << 0 << endl;
    }
}