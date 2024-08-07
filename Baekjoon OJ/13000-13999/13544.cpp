#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define sz(x) (int)(x).size()
#define all(c) (c).begin(), (c).end()

const int MAX = 1 << 17;

struct MergeSortTree {
    vector<int> tree[1 << 18];

    void add(int idx, int val) {
        tree[idx + MAX].push_back(val);
    }

    void build(const vector<int>& arr) {
        for (int i = 0; i < sz(arr); i++) add(i + 1, arr[i]);

        for (int i = MAX - 1; i >= 1; i--) {
            tree[i].resize(sz(tree[i << 1]) + sz(tree[i << 1 | 1]));
            merge(all(tree[i << 1]), all(tree[i << 1 | 1]), tree[i].begin());
        }
    }

    int query(int l, int r, int k) {
        l += MAX, r += MAX;
        int ret = 0;
        while (l <= r) {
            if (l & 1) ret += tree[l].end() - upper_bound(all(tree[l]), k), l++;
            if (~r & 1) ret += tree[r].end() - upper_bound(all(tree[r]), k), r--;
            l >>= 1, r >>= 1;
        }
        return ret;
    }
}mstree;

int n;
vector<int> arr;

int main() {
    #ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    arr.resize(n);
    for (auto& i : arr) cin >> i;

    mstree.build(arr);

    int q; cin >> q;
    int prvAns = 0;

    while (q--) {
        int a, b, c;
        cin >> a >> b >> c;
        a ^= prvAns, b ^= prvAns, c ^= prvAns;

        int ans = mstree.query(a, b, c);
        cout << ans << '\n';
        prvAns = ans;
    }
    
    return 0;
}