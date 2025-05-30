#include <bits/stdc++.h>
using namespace std;

const int MAXC = 2;

struct trie {
	trie* child[MAXC];
	bool term;

	trie() {
		fill(child, child + MAXC, nullptr);
		term = false;
	}
	~trie() {
		for (int i = 0; i < MAXC; i++)
			if (child[i]) delete child[i];
	}

	void insert(int x, int key = 31) {
		if (key == -1) term = true;
		else {
			int next = (x & (1 << key) ? 1 : 0);
			if (!child[next]) child[next] = new trie;
			child[next]->insert(x, key - 1);
		}
	}

    int query(int x, int key = 31) {
        if (key == -1) return 0;
        else {
            int next = (x & (1 << key) ? 0 : 1);
            if (!child[next]) return child[!next]->query(x, key - 1);
            else return (1 << key) | child[next]->query(x, key - 1);
        }
    }
};

int n, a[101010], psum[101010];

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        trie* root = new trie;

        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        
        root->insert(0);
        for (int i = 1; i <= n; i++) {
            psum[i] = a[i] ^ psum[i - 1];
            root->insert(psum[i]);
        }
        
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            ans = max(ans, root->query(psum[i]));
        }

        cout << ans << '\n';

        delete root;
    }

    return 0;
}