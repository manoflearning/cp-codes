#include <iostream>
#include <vector>
using namespace std;

int board[9][9];
vector<pair<int, int>> em;
vector<int> ans;

bool visited[9][10]; //굵은 칸 안에서 중복 방지
bool visitedX[9][10], visitedY[9][10]; //같은 행과 열에서 중복 방지

void backtrack(int flag);
void print();

int main() {
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			cin >> board[y][x];

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
	if (ans.size() == em.size()) {
		print();
		return;
	}

	int y = em[flag].first, x = em[flag].second;
	//몇번째 굵은 칸에 속하는지 정리
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
	//판을 채우는 방법이 여럿인 경우, 첫번째만을 출력
	static bool first = true;
	if (!first) return;
	first = false;
	//
	int flag = 0;

	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			if (board[y][x] == 0) {
				cout << ans[flag] << ' ';
				flag++;
			}
			else cout << board[y][x] << ' ';
		}
		cout << '\n';
	}
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 백트래킹
접근 방식		: 같은 행, 같은 열, 같은 칸 안에서 숫자가 중복되면 안되기에, 각각의 경우에 숫자의 존재 여부를 저장하는 배열을 만듦. 빈 칸은 입력을 받음과 동시에 저장함.
결정적 깨달음		:
오답 원인		: 1. 
				  2.
*/////////////////////////////////////////////////////////////////////