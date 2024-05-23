#include "bits/stdc++.h"
#include"graph.h"
#include"graph.cpp"
using namespace std;


void solution1() {
	for (int i = 1; i <= 100; i++) {

		LARGE_INTEGER start_time; //开始时间  64位整数
		LARGE_INTEGER end_time;   //结束时间
		double dqFreq;            //计时器频率
		LARGE_INTEGER freq;       //计时器频率
		QueryPerformanceFrequency(&freq);
		dqFreq = (double)freq.QuadPart;

		string iin = "E:\\TEST\\DS4\\input";
		iin += to_string(i) + ".in";
		string iout = "E:\\TEST\\DS4\\result1.txt";
		//iout += to_string(i) + ".txt";
		fin.open(iin);
		fout.open(iout,ios::app);
		if (!fin.is_open() || !fout.is_open()) {
			cout << "w\n";
		}
		QueryPerformanceCounter(&start_time); //计时开始

	    graph g;
		g.topsort();
		g.backtracking(1, 0);
		fout << g.bestRes << "\n";

		QueryPerformanceCounter(&end_time); //计时end
		fin.close();
		fout.close();
		ofstream fo("E:\\TEST\\DS4\\cost1.txt", ios::app);
		double run_time = (end_time.QuadPart - start_time.QuadPart) / dqFreq * 1000;//ms
		fo << i << " " << run_time << "\n";
		fo.close();

		//空间 第一种 回溯
		ofstream foo("E:\\TEST\\DS4\\room1.txt", ios::app);
		//int 4 bool 1
		long long romcost = 5 * g.n + 4 * g.m + 4 * g.n;//press+booster==5  4
		foo << i << " " << romcost << "\n";
		foo.close();
	}
}

void solution2() {
	for (int i = 1; i <= 100; i++) {
		LARGE_INTEGER start_time; //开始时间
		LARGE_INTEGER end_time;   //结束时间
		double dqFreq;            //计时器频率
		LARGE_INTEGER freq;       //计时器频率
		QueryPerformanceFrequency(&freq);
		dqFreq = (double)freq.QuadPart;

		string iin = "E:\\TEST\\DS4\\input";
		iin += to_string(i) + ".in";
		string iout = "E:\\TEST\\DS4\\result2.txt";
		//iout += to_string(i) + ".txt";
		fin.open(iin);
		fout.open(iout,ios::app);
		if (!fin.is_open() || !fout.is_open()) {
			cout << "w\n";
		}
		QueryPerformanceCounter(&start_time); //计时开始

		graph g;
		g.topsort();
		g.branch_bound();
		fout << g.bestRes << "\n";

		QueryPerformanceCounter(&end_time); //计时开始
		fin.close();
		fout.close();
		ofstream fo("E:\\TEST\\DS4\\cost2.txt", ios::app);
		double run_time = (end_time.QuadPart - start_time.QuadPart) / dqFreq * 1000;
		fo << i << " " << run_time << "\n";
		fo.close();

		//空间 第2种 分支定界
		ofstream foo("E:\\TEST\\DS4\\room2.txt", ios::app);
		//int 4     btnode   
		long long romcost = 32 * g.n + 4 * g.m;//指针4/8
		foo << i << " " << romcost << "\n";
		foo.close();

	}
}
int main(){
    //graph a;
    //a.topsort();
    //a.backtracking(1,0);
    //a.branch_bound();
    //cout<<a.bestRes<<endl;
    solution1();
    solution2();
    return 0;
}
