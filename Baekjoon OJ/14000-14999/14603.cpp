#pragma GCC optimize ("O3")
#pragma GCC optimize ("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

const int MAXM = 303, MAXN = 303;
const int MAXK = 101010;

struct Fenwick { // 0-indexed
	int flag, cnt; // array size
	vector<int> arr, t;
	void build() {
        arr.clear();
        t.clear();
		for (flag = 1; flag < MAXK; flag <<= 1, cnt++);
		arr.resize(flag);
		t.resize(flag);
		// for (int i = 0; i < MAXK; i++) cin >> arr[i];
		// for (int i = 0; i < MAXK; i++) {
		// 	t[i] += arr[i];
		// 	if (i | (i + 1) < flag) t[i | (i + 1)] += t[i];
		// }
	}
	void add(int p, int value) { // add value at position p
		arr[p] += value;
		while (p < flag) {
			t[p] += value;
			p |= p + 1;
		}
	}
	void modify(int p, int value) { // set value at position p
		add(p, value - arr[p]);
	};
	int kth(int k) { // find the kth smallest number (1-indexed)
		assert(t.back() >= k);
		int l = 0, r = arr.size();
		for (int i = 0; i <= cnt; i++) {
			int mid = (l + r) >> 1;
			int val = mid ? t[mid - 1] : t.back();
			if (val >= k) r = mid;
			else l = mid, k -= val;
		}
		return l;
	}
}fw;

int m, n, k, w;
int a[MAXM][MAXN];

void input() {
    cin >> m >> n >> k >> w;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            cin >> a[i][j];
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    for (int i = 1; i + w - 1 <= m; i++) {
        fw.build();

        for (int y = i; y <= i + w - 1; y++) { // O(W^2 log W)
            for (int x = 1; x <= w; x++) {
                fw.add(a[y][x], 1);
            }
        }
        
        cout << fw.kth((w * w + 1) / 2) << ' ';

        for (int j = 2; j + w - 1 <= n; j++) { // O(NW log W)
            for (int y = i; y <= i + w - 1; y++) {
                fw.add(a[y][j - 1], -1);
                fw.add(a[y][j + w - 1], 1);
            }
            cout << fw.kth((w * w + 1) / 2) << ' ';
        }

        cout << '\n';
    }
}
