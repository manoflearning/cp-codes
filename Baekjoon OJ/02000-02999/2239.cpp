#include <iostream>
#include <vector>
using namespace std;

int board[9][9];
vector<pair<int, int>> em;
vector<int> ans;
bool first = true;

bool visited[9][10]; //���� ĭ �ȿ��� �ߺ� ����
bool visitedX[9][10], visitedY[9][10]; //���� ��� ������ �ߺ� ����

void backtrack(int flag);
void print();

int main() {
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			char t;
			cin >> t;
			board[y][x] = t - '0';

			if (board[y][x] == 0) {
				em.push_back({ y , x });
			}
			else {
				int b = y / 3 * 3 + x / 3;
				visited[b][board[y][x]] = true;
				visitedX[x][board[y][x]] = true;
				visitedY[y][board[y][x]] = true;
			}
		}
	}

	backtrack(0);

	return 0;
}

void backtrack(int flag) {
	//base case
	if (!first) return;
	if (ans.size() == em.size()) {
		print();
		return;
	}

	int y = em[flag].first, x = em[flag].second;
	//���° ���� ĭ�� ���ϴ��� ����
	int b = y / 3 * 3 + x / 3;

	for (int i = 1; i <= 9; i++) {
		if (visited[b][i]) continue;
		if (visitedX[x][i] || visitedY[y][i]) continue;

		visited[b][i] = true;
		visitedX[x][i] = true, visitedY[y][i] = true;
		ans.push_back(i);

		backtrack(flag + 1);

		visited[b][i] = false;
		visitedX[x][i] = false, visitedY[y][i] = false;
		ans.pop_back();
	}
}
void print() {
	//���� ä��� ����� ������ ���, ù��°���� ���
	if (!first) return;
	first = false;
	//
	int flag = 0;

	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			if (board[y][x] == 0) {
				cout << ans[flag];
				flag++;
			}
			else cout << board[y][x];
		}
		cout << '\n';
	}
}
/*////////////////////////////////////////////////////////////////////
���� �ع�		: ��Ʈ��ŷ
���� ���		: ���� ��, ���� ��, ���� ĭ �ȿ��� ���ڰ� �ߺ��Ǹ� �ȵǱ⿡, ������ ��쿡 ������ ���� ���θ� �����ϴ� �迭�� ����. �� ĭ�� �Է��� ������ ���ÿ� ������.
������ ������		:
���� ����		: 1.
				  2.
*/////////////////////////////////////////////////////////////////////