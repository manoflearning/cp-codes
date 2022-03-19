#include <iostream>
#include <map>
using namespace std;

map<string, string> mp;

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N, M; 
	cin >> N >> M;

	while (N--) {
		string s1, s2;
		cin >> s1 >> s2;

		mp.insert({ s1, s2 });
	}

	while (M--) {
		string s; cin >> s;

		cout << mp.find(s)->second << '\n';
	}

	return 0;
}
/*//////////////////////////////////////////////////////////////////
문제 해법		: 맵
결정적 깨달음		: 
시간복잡도		: O((n + m)lgn)
오답 원인		: 1. 
				  2. 
*///////////////////////////////////////////////////////////////////