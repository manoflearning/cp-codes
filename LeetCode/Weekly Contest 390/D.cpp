const char st = 'a';
const int MAXC = 'z' - 'a' + 1;
const int INF = 1e9 + 7;

class trie {
public:
	trie* child[MAXC];
	int opt, len;
	trie() {
		fill(child, child + MAXC, nullptr);
		opt = -1, len = INF;
	}
	~trie() {
		for (int i = 0; i < MAXC; i++)
			if (child[i]) delete child[i];
	}
	void insert(const string& s, int idx, int key = 0) {
        if (s.size() < len) {
            len = s.size(), opt = idx;
        }

		if (key < s.size()) {
			int next = s[key] - st;
			if (!child[next]) child[next] = new trie;
			child[next]->insert(s, idx, key + 1);
		}
	}
	int find(const string& s, int key = 0) {
		if (s.size() == key) return opt;
		else {
			int next = s[key] - st;
            // if (!child[next]) cout << key << ' ' << s[key] << '\n';
			if (!child[next]) return opt;
			else return child[next]->find(s, key + 1);
		}
	}
};

class Solution {
public:
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        trie* root = new trie;

        for (auto& s : wordsContainer) {
            reverse(s.begin(), s.end());
        }
        for (auto& s : wordsQuery) {
            reverse(s.begin(), s.end());
        }

        int n = wordsContainer.size();
        int m = wordsQuery.size();
        for (int i = 0; i < n; i++) {
            root->insert(wordsContainer[i], i);
        }

        vector<int> ans(m);
        for (int i = 0; i < m; i++) {
            ans[i] = root->find(wordsQuery[i]);
        }

        delete root;

        return ans;
    }
};