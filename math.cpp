#include "math.h"
#include <string>
#include<stack>
using namespace math_namespace;

namespace math_namespace
{
	void (*pfun[4])() = { NULL,general_solve,min_two,mul_equ_solve };

	double** mat(int row, int col)///双精度浮点型矩阵生成器---小心内存泄漏：
	{
		double** arr = (double**)calloc((row + 1), sizeof(double*));
		if (arr == NULL)
			return NULL;
		double* p = (double*)calloc((row + 1) * (col + 1), sizeof(double));
		if (p == NULL)
			return NULL;
		int i = 0;
		for (i = 0; i <= row; i++)
		{
			arr[i] = p + i * (col + 1);
		}
		arr[0][0] = row;
		arr[0][1] = col;
		return arr;
	}

	double fun(double* p, double x, int k)/// k 次多项式求值 p[0]=a0 ....p[k]=ak：
	{
		int i = 0, j = 0;
		double sum = 0;
		for (i = 0; i <= k; i++)
		{
			double d = 1;
			for (j = 1; j <= i; j++)
			{
				d *= x;
			}
			sum += p[i] * d;
		}
		return sum;
	}

	double* solvep(double* p)///计算一元 n 次方程的实数解：p[0]=n,p[1]=a0,.....p[n+1]=an---小心内存泄漏:
	{
		srand((unsigned int)time(NULL));
		int n = (int)p[0];
		double** arr = mat(n, n);
		int i = 0, j = 0;
		for (i = 0; i <= n; i++)
		{
			arr[n][i] = p[i + 1];
		}

		for (i = n - 1; i > 0; i--)
		{
			for (j = 0; j <= i; j++)
			{
				arr[i][j] = arr[i + 1][j + 1] * (j + 1);
			}
		}
		double** arr1 = mat(n, n);
		if (arr == NULL)
			return NULL;

		arr1[1][1] = -arr[1][0] / arr[1][1];
		for (i = 2; i <= n; i++)
		{
			if (i % 2 == 0)
			{
				for (j = 1; j < i; j++)
				{
					if (arr[i][i] * fun(arr[i], arr1[i - 1][j], i) <= 0)
						break;
				}
				if (j == i)
					continue;
				for (j = 1; j <= i; j++)
				{
					if (j == 1)
					{
						double x = arr1[i - 1][1] - rand() + 0.1;
						int k = 0;
						while (k < 10000 && (fun(arr[i], x, i) > 0.0000000000001 || fun(arr[i], x, i) < -0.0000000000001))
						{
							x = x - fun(arr[i], x, i) / fun(arr[i - 1], x, i - 1);
							k++;
						}
						arr1[i][j] = x;
					}
					else if (j == i)
					{
						double x = arr1[i - 1][i - 1] + rand() + 0.1;
						int k = 0;
						while (k < 10000 && (fun(arr[i], x, i) > 0.0000000000001 || fun(arr[i], x, i) < -0.0000000000001))
						{
							x = x - fun(arr[i], x, i) / fun(arr[i - 1], x, i - 1);
							k++;
						}
						arr1[i][j] = x;
					}
					else
					{
						double x = (arr1[i - 1][j - 1] + arr1[i - 1][j]) / 2 - 0.000001;
						int k = 0;
						while (k < 10000 && (fun(arr[i], x, i) > 0.0000000000001 || fun(arr[i], x, i) < -0.0000000000001))
						{
							x = x - fun(arr[i], x, i) / fun(arr[i - 1], x, i - 1);
							k++;
						}
						arr1[i][j] = x;
					}
				}
			}
			else
			{
				for (j = 1; j <= i; j++)
				{
					if (j == 1)
					{
						double x = arr1[i - 1][1] - rand() + 0.1;
						int k = 0;
						while (k < 10000 && (fun(arr[i], x, i) > 0.0000000000001 || fun(arr[i], x, i) < -0.0000000000001))
						{
							x = x - fun(arr[i], x, i) / fun(arr[i - 1], x, i - 1);
							k++;
						}
						arr1[i][j] = x;
					}
					else if (j == i)
					{
						double x = arr1[i - 1][i - 1] + rand() + 0.1;
						int k = 0;
						while (k < 10000 && (fun(arr[i], x, i) > 0.0000000000001 || fun(arr[i], x, i) < -0.0000000000001))
						{
							x = x - fun(arr[i], x, i) / fun(arr[i - 1], x, i - 1);
							k++;
						}
						arr1[i][j] = x;
					}
					else
					{
						double x = (arr1[i - 1][j - 1] + arr1[i - 1][j]) / 2 - 0.000001;
						int k = 0;
						while (k < 10000 && (fun(arr[i], x, i) > 0.0000000000001 || fun(arr[i], x, i) < -0.0000000000001))
						{
							x = x - fun(arr[i], x, i) / fun(arr[i - 1], x, i - 1);
							k++;
						}
						arr1[i][j] = x;
					}
				}
			}
		}
		free(arr[0]);
		free(arr);
		double* arr2 = (double*)malloc(sizeof(double) * (n + 1));
		arr2[0] = n;
		for (i = 1; i <= n; i++)
		{
			arr2[i] = arr1[n][i];
		}
		free(arr1[0]);
		free(arr1);
		return arr2;
	}

	vector<string> mid_convert_beh(vector<string>& arr)
	{
		vector<string> ret;
		stack<string> st;
		for (auto i : arr)
		{
			if (i != "+" && i != "-" && i != "*" && i != "/"&&i!="^")
			{
				ret.push_back(i);
			}
			else
			{
				int pi = 0;
				if (i == "+" || i == "-")
				{
					pi = 1;
				}
				else if (i == "*" || i == "/")
				{
					pi = 2;
				}
				else
				{
					pi = 3;
				}
				while (1)
				{
					if (st.empty())
					{
						st.push(i);
						break;
					}
					string s = st.top();
					int ps = 0;
					if (s == "+" || s == "-")
					{
						ps = 1;
					}
					else if (s == "*" || s == "/")
					{
						ps = 2;
					}
					else
					{
						ps = 3;
					}
					if (pi>ps)
					{
						st.push(i);
						break;
					}
					ret.push_back(s);
					st.pop();
				}
			}
		}
		while (!st.empty())
		{
			ret.push_back(st.top());
			st.pop();
		}
		return ret;
	}

	double solve_beh(vector<string>& arr)
	{
		stack<double>st;
		for (auto& i : arr)
		{
			if (i != "+" && i != "-" && i != "*" && i != "/"&&i!="^")
			{
				try
				{
					st.push(stod(i));
				}
				catch (exception e)
				{
					cout << "\n\n\t表达式格式错误！\n";
					return 0;
				}
				
			}
			else
			{
				if (st.empty())
				{
					cout << "\n\n\t表达式格式错误！\n";
					return 0;
				}
				double right = st.top();
				st.pop();
				if (st.empty())
				{
					cout << "\n\n\t表达式格式错误！\n";
					return 0;
				}
				double left = st.top();
				st.pop();
				switch (i[0])
				{
				case '+':
					st.push(left + right);
					break;
				case '-':
					st.push(left - right);
					break;
				case '*':
					st.push(left * right);
					break;
				case '/':
					st.push(left / right);
					break;
				case '^':
					st.push(pow(left,right));
					break;
				}
			}
		}
		return st.top();
	}

	double solve(vector<string>& arr)
	{
		vector<string> arr0;
		stack<string> st;
		for (auto i : arr)
		{
			if (i == "(")
			{
				st.push(i);
				continue;
			}
			if (i == ")")
			{
				stack<string> st1;
				while (st.top() != "(")
				{
					st1.push(st.top());
					st.pop();
				}
				st.pop();
				vector<string> arr1;
				while (!st1.empty())
				{
					arr1.push_back(st1.top());
					st1.pop();
				}
				vector<string> arr2 = mid_convert_beh(arr1);
				double d = solve_beh(arr2);
				string s = to_string(d);
				if (st.empty())
				{
					arr0.push_back(s);
				}
				else
				{
					st.push(s);
				}
				continue;
			}
			if (st.empty())
			{
				arr0.push_back(i);
			}
			else
			{
				st.push(i);
			}
		}
		vector<string> arr3 = mid_convert_beh(arr0);
		return solve_beh(arr3);
	}

	double solve(string& str)
	{
		vector<string> arr;
		arr.push_back("");
		for (auto& i : str)
		{
			int n = arr.size() - 1;
			if (i == '+' || i == '-' || i == '*' || i == '/' || i == '^' || i == '(' || i == ')')
			{
				if (arr[n].empty())
				{
					if (i == '-' && (n==0||arr[n - 1] == "(" || arr[n - 1] == "^"))
					{
						arr[n].push_back(i);
					}
					else
					{
						arr[n].push_back(i);
						arr.push_back("");
					}
				}
				else
				{
					arr.push_back("");
					arr[n + 1].push_back(i);
					arr.push_back("");
				}
			}
			else
			{
				arr[n].push_back(i);
			}
		}
		if (arr.back().empty())
		{
			arr.pop_back();
		}
		return solve(arr);
	}

	void mul_equ_solve()
	{
		system("cls");
		cout << "\n\n\t请输入一元 N 次方程的次数: N=";
		int n=0;
		while (1)
		{
			scanf("%d", &n);
			if (n == 0)
			{
				cout << "\n\t输入错误！\n\n\t请重新输入：n=";
				while (getchar() != 10) {}
			}
			else
			{
				break;
			}
		}
		while (getchar() != 10) {}
		double* p = new double[n + 2];
		p[0] = n;
		cout << "\n\n\t从高到低依次输入各项个系数：\n\n\t[an-------a0]=";
		double d = -0.0000000000000000001;
		int a = 1;
		while (a)
		{
			a = 0;
			for (int i = n + 1; i > 0; i--)
			{
				scanf("%lf", &d);
				if (d != -0.0000000000000000001)
				{
					p[i] = d;
					d = -0.0000000000000000001;
				}
				else
				{
					cout << "\n\n\t格式错误！请重新输入:\n\n\t[an-------a0]=";
					a = 1;
					while (getchar() != 10) {}
					break;
				}
			}
		}
		while(getchar()!=10){}
		double*pp= solvep(p);
		delete[](p);
		int i = 0;
		for (i = 1; i <= n; i++)
		{
			if (pp[i] != 0)
				break;
		}
		if (i == n + 1)
		{
			cout << "\n\n\t\t方程无解！\n\n\t\t或者方程的 " << n << " 个解全为 0 \n\t";
		}
		else
		{
			cout << "\n\n\t\t方程的解如下：\n";
			for (int i = 1; i <= n; i++)
			{
				cout << "\n\t\t\tx" << i << "=" << pp[i] <<"\n";
			}
		}
		cout << "\n\n\n";
		free(pp);
		system("pause");
	}

	void general_solve()
	{
		system("cls");
		cout << "\n\n\n\n\t\t\t请输入您要计算的表达式：\n\n\t\t\t";
		string str;
		while (1)
		{
			int k = 0;
			cin >> str;
			for (auto& i : str)
			{
				if ((i < '0' || i>'9') && i != '+' && i != '-' && i != '*' && i != '/' && i != '(' && i != ')'&&i!='^'&&i!='.')
				{
					k = 1;
					break;
				}
			}
			if (k == 1)
			{
				cout << "\n\n\t\t\t格式错误！请重新输入：\n\n\t\t\t";
			}
			else
			{
				break;
			}
		}
		double d = solve(str);
		cout << "\n\n\t\t\t" << str << "=" << d << endl;
		system("pause");
	}

	void min_two()/// 最小二乘法
	{
		system("cls");
		int i, n = 0;
		printf("\n\n\t\t\t最小二乘法以及相关系数的确定：");
		printf("\n\n\n\t请输入节点总数: n=");
		while (1)
		{
			scanf("%d", &n);
			if (n<2)
			{
				cout << "\n\t输入错误！\n\n\t请重新输入大于 1 的整数：n=";
				while (getchar() != 10) {}
			}
			else
			{
				break;
			}
		}
		while (getchar() != 10) {}
		vector<double> X(n), Y(n);
		printf("\n\n\n\t请依次输入横坐标 X 的值：\n\n\t");
		double d = -0.0000000000000000001;
		int a = 1;
		while (a)
		{
			a = 0;
			for (i =0; i <n; i++)
			{
				scanf("%lf", &d);
				if (d != -0.0000000000000000001)
				{
					X[i] = d;
					d = -0.0000000000000000001;
				}
				else
				{
					cout << "\n\n\t格式错误！请重新输入 X 的值:\n\n\t";
					a = 1;
					while (getchar() != 10) {}
					break;
				}
			}
		}
		while (getchar() != 10){}
		printf("\n\n\n\t请依次输入纵坐标 y 的值：\n\n\t");
		d = -0.0000000000000000001;
		a = 1;
		while (a)
		{
			a = 0;
			for (i = 0; i < n; i++)
			{
				scanf("%lf", &d);
				if (d != -0.0000000000000000001)
				{
					Y[i] = d;
					d = -0.0000000000000000001;
				}
				else
				{
					cout << "\n\n\t格式错误！请重新输入 Y 的值:\n\n\t";
					a = 1;
					while (getchar() != 10) {}
					break;
				}
			}
		}
		while (getchar() != 10) {}
		double T00 = 0, T01 = 0, T11 = 0, F0 = 0, F1 = 0;
		for (i = 0; i < n; i++)
		{
			T00 = T00 + 1;
			T01 = T01 + X[i];
			T11 = T11 + X[i] * X[i];
			F0 = F0 + Y[i];
			F1 = F1 + X[i] * Y[i];
		}
		double a0, a1;
		a0 = (F0 * T11 - F1 * T01) / (T00 * T11 - T01 * T01);
		a1 = (T00 * F1 - T01 * F0) / (T00 * T11 - T01 * T01);
		if (a0 >= 0)
			printf("\n\n          最小二乘法的结果是：  y=%lfx+%lf\n\n\n", a1, a0);
		else
			printf("\n\n          最小二乘法的结果是：  y=%lfx%lf\n\n\n", a1, a0);
		double xx = 0, yy = 0, xy = 0, xp = 0, yp = 0, R;
		for (i = 0; i < n; i++)
		{
			xx = xx + Y[i] * Y[i];
			yy = yy + (a0 + a1 * X[i]) * (a0 + a1 * X[i]);
			xy = xy + (a0 + a1 * X[i]) * Y[i];
			xp = xp + Y[i];
			yp = yp + (a0 + a1 * X[i]);
		}
		xp = xp / n; yp = yp / n;
		R = (xy - n * xp * yp) / (n - 1.0) / sqrt((xx - n * xp * xp) / (n - 1.0)) / sqrt((yy - n * yp * yp) / (n - 1.0));
		printf("          相关系数: R=%lf  R^2=%lf\n\n\n\n", R, R * R);
		system("pause");
	}

	void menu()
	{
		cout << "\n                        欢迎来到：***数学空间***\n";
		printf("\n\n\t****************    0    退出	                   ***************\n");
		printf("\n\n\t****************    1    一般数学表达式计算 	   ***************\n");
		printf("\n\n\t****************    2    最小二乘法曲线拟合 	   ***************\n");
		printf("\n\n\t****************    3    一元 N 次方程实数根求解   ***************\n\n\n\t\t\t");
	}
}

void math()
{
	while (1)
	{
		system("cls");
		menu();
		printf("请输入您的选择： ");
		int n = -1;
		scanf("%d", &n);
		while (n < 0 || n>3)
		{
			cout << "\n\t\t输入错误：\n\n\t\t请输入0-3的整数:";
			while (getchar() != 10) {}
			scanf("%d", &n);
		}
		while(getchar()!=10){}
		if (n == 0)
			break;
		pfun[n]();
	}
}

