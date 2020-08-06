#include <iostream>
#include <vector>
using namespace std;

vector<char> num;

int main() {
	int t;
	cin >> t;

	for (int test = 0; test < t; test++) {
		//reset
		num.clear();
		//
		int n;
		cin >> n;
		//
		int twoOrone = 0; // 주어진 수의 홀짝 여부 판별
		for (int i = 0; i < n; i++) {
			char a;
			cin >> a;

			if (a != '0') {
				num.push_back(a);

				if ((a - '0') % 2 == 1) twoOrone++;
			}
		}
		//맨 뒤의 숫자를 홀수로 만들기
		while (!num.empty() && (num.back() - '0') % 2 == 0) {
			num.pop_back();
		}
		//
		if (twoOrone % 2 == 0) {
			if (num.empty()) cout << "-1\n";
			else {
				for (int i = 0; i < num.size(); i++)
					cout << num[i];
				cout << '\n';
			}
		}
		else {
			bool check = false;
			int flag;
			for (int i = 0; i < num.size() - 1; i++)
				if ((num[i] - '0') % 2 == 1) {
					flag = i;
					check = true;
					break;
				}

			if (check) {
				for (int i = 0; i < num.size(); i++)
					if (i != flag) cout << num[i];
				cout << '\n';
			}
			else cout << "-1\n";
		}
	}

	return 0;
}