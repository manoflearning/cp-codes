#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(x) (x).begin(), (x).end()

int n;
string s[303030];

const char st = 'a';
const int MAXC = 'z' - 'a' + 1;
struct trie {
	trie* child[MAXC];
	ll term;
	trie() {
		fill(child, child + MAXC, nullptr);
		term = 0;
	}
	~trie() {
		for (int i = 0; i < MAXC; i++)
			if (child[i]) delete child[i];
	}
	void insert(const string& s, int key = 0) {
        if (key != 0) term++;
		if (s.size() == key) return;
		else {
			int next = s[key] - st;
			if (!child[next]) child[next] = new trie;
			child[next]->insert(s, key + 1);
		}
	}
	ll find(const string& s, int key = 0) {
		if (s.size() == key) return term;
		else {
			int next = s[key] - st;
			if (!child[next]) return term;
			else return term + child[next]->find(s, key + 1);
		}
	}
};

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    trie* root = new trie;

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> s[i];

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += root->find(s[i]);
        root->insert(s[i]);
    }

    cout << ans;

    delete root;
}