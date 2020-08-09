#include <iostream>
#include <queue>
using namespace std;

const int MAX = 100;
const pair<int, int> dir[4] = { {-1,0},{0,1},{1,0},{0,-1} }; //상, 우, 하, 좌

int n;
bool visited[MAX + 1][MAX + 1];
bool apple[MAX + 1][MAX + 1];
queue<pair<int, int>> snk;
queue<pair<int, char>> chng;

int simul(int Y, int X, int time, int dr);

int main() {
	cin >> n;
	//사과 위치 정보 입력
	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		int y, x;
		cin >> y >> x;

		apple[y][x] = true;
	}
	//방향 변환 정보 입력
	int c;
	cin >> c;
	for (int i = 0; i < c; i++) {
		int time;
		char dir;
		cin >> time >> dir;

		chng.push({ time, dir });
	}
	//
	snk.push({ 0, 0 });
	cout << simul(1, 1, 0, 1);

	return 0;
}

int simul(int Y, int X, int time, int dr) {
	//base case : 뱀의 머리가 몸 또는 벽과 충돌했을 때
	if (visited[Y][X]) return time;
	if (Y < 1 || n < Y || X < 1 || n < X) return time;
	//뱀 길이 늘리기, 뱀 정보 저장
	visited[Y][X] = true;
	snk.push({ Y,X });
	//사과를 먹던가 몸 길이를 줄어던가
	if (apple[Y][X]) apple[Y][X] = false;
	else {
		visited[snk.front().first][snk.front().second] = false;
		snk.pop();
	}
	//방향 전환
	if (!chng.empty() && time == chng.front().first) {
		if (chng.front().second == 'D') {
			if (dr == 3) dr = 0;
			else dr++;
		}
		else {
			if (dr == 0) dr = 3;
			else dr--;
		}
		chng.pop();
	}
	//이동
	return simul(Y + dir[dr].first, X + dir[dr].second, time + 1, dr);
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 
접근 방식		: 
결정적 깨달음		:
오답 원인		: 1. 상하가 거꾸로 정의됨. 배열에서 상은 {-1, 0}, 하는 {1, 0}임을 명심.
				  2.
*/////////////////////////////////////////////////////////////////////