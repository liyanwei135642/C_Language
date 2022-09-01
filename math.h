#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<iostream>
#include<vector>
using namespace std;

void math();

namespace math_namespace
{
	double** mat(int row, int col);

	double fun(double* p, double x, int k);

	double* solvep(double* p);

	void mul_equ_solve();

	void general_solve();

	void math_menu();

	vector<string> mid_convert_beh(vector<string>& arr);

	double solve_beh(vector<string>& arr);

	double solve(vector<string>& arr);

	double solve(string& str);

	void min_two();

	void get_int(int& n);///获取整型赋值给 n：


}