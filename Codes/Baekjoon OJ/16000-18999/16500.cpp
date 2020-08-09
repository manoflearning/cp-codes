#include <iostream>
#include <map>
#include <cstring>
using namespace std;

int N;
string s;
map<string, int> mp;
int dp[101];

bool canMake(int left);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	memset(dp, -1, sizeof(dp));

	cin >> s >> N;

	for (int i = 0; i < N; i++) {
		string a; cin >> a;
		mp.insert({ a, i });
	}

	if (canMake(0)) cout << 1;
	else cout << 0;

	return 0;
}

bool canMake(int left) {
	//base case
	if (left == s.size()) return true;
	if (left > s.size()) return false;

	int& ret = dp[left];
	if (ret != -1) return ret;

	for (int len = left; len < s.size(); len++) {
		//cout << s.substr(left, len + 1 - left + 1) << '\n';
		map<string, int>::iterator it = mp.find(s.substr(left, len + 1 - left));
		if (it != mp.end()) {
			if (canMake(len + 1)) return ret = true;
		}
	}
	return ret = false;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 동적계획법, map
결정적 깨달음		: 
시간복잡도		: O(|s|lgn)
오답 원인		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////