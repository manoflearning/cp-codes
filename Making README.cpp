#pragma once
#include <iostream>
#include <io.h>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

struct Contents {
	string name;
	int cnt;
	bool operator<(Contents& rhs) {
		if(cnt != rhs.cnt) return cnt > rhs.cnt;
		return name < rhs.name;
	}
};

vector<Contents> contents;

void printIntro();
void printTheNumOfSolvedProblem();
int searchingDir(string path, int dep);
bool isFile(_finddata_t fd);
bool isExeFile(string s);
void printLastRenewalTime();

int main() {
	printIntro();

	cout<<"<br/>\n";

	printTheNumOfSolvedProblem();

	cout<<"<br/>\n";

	printLastRenewalTime();

    return 0;
}

void printIntro() {
	cout<<"# PS-Codes\n";
	cout<<"알고리즘 문제 정답 코드 저장용입니다. <br/>\n";
}

void printTheNumOfSolvedProblem() {
	string path = "D:\\0JWK\\0programming\\PS-Codes\\Codes";
	searchingDir(path, 0);

	sort(contents.begin(), contents.end());

	cout<<"현재까지 <br/>\n";
	for(int i = 1; i < contents.size(); i++) {
		cout<<"**"<<contents[i].name<<"**에서 **"<<contents[i].cnt<<"**문제, <br/>\n";
	}
	cout<<"총합 **"<<contents[0].cnt<<"**문제를 풀었습니다.<br/>\n";
}

int searchingDir(string path, int dep) {
	string dirPath = path + "\\*.*";
	struct _finddata_t fd;
	intptr_t handle;
	list<_finddata_t> fdlist;

	if ((handle = _findfirst(dirPath.c_str(), &fd)) == -1L) {
		cout << "No file in directory!" << endl;
		return 0;
	}

	int ret = 0;
	do {
		int isF = isFile(fd);
		if (fd.name[0] != '.') {
			if (isF == 0) {
				int sum = searchingDir(path + "\\" + fd.name, dep + 1);
				ret += sum;
				if(dep == 0) contents.push_back({fd.name, sum});
			}
			else {
				if (!isExeFile(fd.name)) ret++;
				fdlist.push_back(fd);
			}
		}
	} while (_findnext(handle, &fd) == 0);

	_findclose(handle);

	if(dep == 0) contents.push_back({"all", ret});

	return ret;
}

bool isFile(_finddata_t fd) {
	if (fd.attrib & _A_SUBDIR) return 0;
	else return 1;
}

bool isExeFile(string s) {
	if(s.back() == 'e') return 1;
	else return 0;
}

void printLastRenewalTime() {
	struct tm curr_tm;
	time_t curr_time = time(nullptr);

	localtime_r(&curr_time, &curr_tm);

	int year = curr_tm.tm_year + 1900;
	int month = curr_tm.tm_mon + 1;
	int day = curr_tm.tm_mday;

	cout<<'('<<year<<'/'<<month<<'/'<<day<<"에 마지막으로 갱신함.) <br/>\n";
}