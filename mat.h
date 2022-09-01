#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<iostream>
#include<vector>
#include<stack>
#include <string>

using namespace std;

namespace mat_namespace
{
	/// <summary>
	/// 矩阵类模板
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<class T>
	class matlab
	{
		/// <summary>
		/// 友元函数 int数字与矩阵乘法运算符重载：
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="d"></param>
		/// <param name="mat1"></param>
		/// <returns></returns>
		template<class T>
		friend matlab<double> operator*(int d, matlab<T> mat1);

		/// <summary>
		/// 友元函数 double数字与矩阵乘法运算符重载：
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="d"></param>
		/// <param name="mat1"></param>
		/// <returns></returns>
		template<class T>
		friend matlab<double> operator*(double d, matlab<T> mat1);


		int  _n;
		int _m;
		vector<vector<T>> _arr;
	public:

		string _name;

		/// <summary>
		///构造 n 行 m 列 全为 x 的矩阵：
		/// </summary>
		/// <param name="n"></param>
		/// <param name="m"></param>
		/// <param name="x"></param>
		matlab(int n = 0, int m = 0, T x = T())
		{
			_name = "ans";
			_n = n;
			if (m == 0)
			{
				m = n;
			}
			_m = m;
			_arr.resize(n + 1);
			for (auto& i : _arr)
			{
				i.resize(m + 1, x);
			}
		}

		/// <summary>
		/// 拷贝构造：
		/// </summary>
		/// <param name="mat1"></param>
		matlab(const matlab<T>& mat1)
		{
			_name = mat1._name;
			_n = mat1._n;
			_m = mat1._m;
			_arr.resize(_n + 1);
			for (int i = 0; i <= _n; i++)
			{
				_arr[i].resize(_m + 1);
				for (int j = 0; j <= _m; j++)
				{
					_arr[i][j] = mat1._arr[i][j];
				}
			}
		}

		/// <summary>
		/// 赋值运算符重载：
		/// </summary>
		/// <param name="mat1"></param>
		/// <returns></returns>
		matlab<T>& operator=(const matlab<T>& mat1)
		{
			if (this != &mat1)
			{
				_n = mat1._n;
				_m = mat1._m;
				_name = mat1._name;
				_arr.resize(_n + 1);
				for (int i = 0; i <= _n; i++)
				{
					_arr[i].resize(_m + 1);
					for (int j = 0; j <= _m; j++)
					{
						_arr[i][j] = mat1._arr[i][j];
					}
				}
			}
			return *this;
		}

		/// <summary>
		/// 获取矩阵的行数：
		/// </summary>
		/// <returns></returns>
		int lin()
		{
			return _n;
		}

		/// <summary>
		/// 获取矩阵的第 n 行, 返回一个行矩阵：
		/// </summary>
		/// <param name="n"></param>
		/// <returns></returns>
		matlab<T> lin(int n)
		{
			matlab<T> mat1(1, _m);
			for (int i = 1; i <= _m; i++)
			{
				mat1(1, i) = (*this)(n, i);
			}
			return mat1;
		}

		/// <summary>
		/// 把矩阵 mat1 的值赋值给当前矩阵的第 n 行：
		/// </summary>
		/// <param name="n"></param>
		/// <param name="mat1"></param>
		void lin(int n, matlab<T>& mat1)
		{
			for (int i = 1; i <= _m; i++)
			{
				(*this)(n, i) = mat1(1, i);
			}
		}


		/// <summary>
		/// 获取矩阵在数组 arr 当中的某几行,返回那几行的矩阵：
		/// </summary>
		/// <param name="arr"></param>
		/// <returns></returns>
		matlab<T> lin(vector<int>& arr)
		{
			int n = arr.size();
			matlab<T> mat1(n, _m);
			for (int i = 1; i <= n; i++)
			{
				for (int j = 1; j <= _m; j++)
				{
					mat1(i, j) = (*this)(arr[i - 1], j);
				}
			}
			return mat1;
		}

		/// <summary>
		/// 把矩阵 mat1 的值赋值给当前矩阵 arr 数组当中的某几行：
		/// </summary>
		/// <param name="arr"></param>
		/// <param name="mat1"></param>
		void lin(vector<int>& arr, matlab<T>& mat1)
		{
			int n = arr.size();
			for (int i = 1; i <= n; i++)
			{
				for (int j = 1; j <= _m; j++)
				{
					(*this)(arr[i - 1], j) = mat1(i, j);
				}
			}
		}

		/// <summary>
		/// 获取矩阵的列数：
		/// </summary>
		/// <returns></returns>
		int col()
		{
			return _m;
		}

		/// <summary>
		/// 获取矩阵的第 m 列, 返回一个列矩阵：
		/// </summary>
		/// <param name="m"></param>
		/// <returns></returns>
		matlab<T> col(int m)
		{
			matlab<T> mat1(_n, 1);
			for (int i = 1; i <= _n; i++)
			{
				mat1(i, 1) = (*this)(i, m);
			}
			return mat1;
		}

		/// <summary>
		/// 把矩阵 mat1 的值赋值给当前矩阵的第 n 列：
		/// </summary>
		/// <param name="m"></param>
		/// <param name="mat1"></param>
		void col(int m, matlab<T>& mat1)
		{
			for (int i = 1; i <= _n; i++)
			{
				(*this)(i, m) = mat1(i, 1);
			}
		}

		/// <summary>
		/// 获取矩阵在数组 arr 当中的某几列,返回那几列的矩阵：
		/// </summary>
		/// <param name="arr"></param>
		/// <returns></returns>
		matlab<T> col(vector<int>& arr)
		{
			int m = arr.size();
			matlab<T> mat1(_n, m);
			for (int i = 1; i <= _n; i++)
			{
				for (int j = 1; j <= m; j++)
				{
					mat1(i, j) = (*this)(i, arr[j - 1]);
				}
			}
			return mat1;
		}

		/// <summary>
		/// 把矩阵 mat1 的值赋值给当前矩阵 arr 数组当中的某几列：
		/// </summary>
		/// <param name="arr"></param>
		/// <param name="mat1"></param>
		void col(vector<int>& arr, matlab<T>& mat1)
		{
			int m = arr.size();
			for (int i = 1; i <= _n; i++)
			{
				for (int j = 1; j <= m; j++)
				{
					(*this)(i, arr[j - 1]) = mat1(i, j);
				}
			}
		}

		/// <summary>
		/// 返回矩阵的第 n 行，第 m 列的元素：
		/// </summary>
		/// <param name="n"></param>
		/// <param name="m"></param>
		/// <returns></returns>
		T& operator()(int n, int m)
		{
			if (n > _n)
			{
				_arr.resize(n + 1);
				for (int i = _n + 1; i <= n; i++)
				{
					_arr[i].resize(_m + 1);
				}
				_n = n;
			}
			if (m > _m)
			{
				for (int i = 0; i <= _n; i++)
				{
					_arr[i].resize(m + 1);
				}
				_m = m;
			}
			return _arr[n][m];
		}

		/// <summary>
		/// 获取矩阵在数组 arr1 当中的某几行和 arr2 当中的某几列,返回那一个新矩阵：
		/// </summary>
		/// <param name="arr1"></param>
		/// <param name="arr2"></param>
		/// <returns></returns>
		matlab<T> operator()(vector<int>& arr1, vector<int>& arr2)
		{
			int n = arr1.size();
			int m = arr2.size();
			matlab<T> mat1(n, m);
			for (int i = 1; i <= n; i++)
			{
				for (int j = 1; j <= m; j++)
				{
					mat1(i, j) = (*this)(arr1[i - 1], arr2[j - 1]);
				}
			}
			return mat1;
		}

		/// <summary>
		/// 把矩阵 mat1 的值赋值给当前矩阵的 arr1 的某些行和 arr2 的某些列：
		/// </summary>
		/// <param name="arr1"></param>
		/// <param name="arr2"></param>
		/// <param name="mat1"></param>
		void operator()(vector<int>& arr1, vector<int>& arr2, matlab<T>& mat1)
		{
			int n = arr1.size();
			int m = arr2.size();
			for (int i = 1; i <= n; i++)
			{
				for (int j = 1; j <= m; j++)
				{
					(*this)(arr1[i - 1], arr2[j - 1]) = mat1(i, j);
				}
			}
		}

		/// <summary>
		/// 打印矩阵：
		/// </summary>
		void print()
		{
			cout << "\n\n矩阵的 行数：" << _n << " 列数：" << _m << "\n\n";
			cout << "\t" << _name << "=\n\n";
			for (int i = 1; i <= _n; i++)
			{
				cout << "第 " << i << " 行" << "\t  ";
				for (int j = 1; j <= _m; j++)
				{
					cout << (*this)(i, j) << "\t";
				}
				cout << "\n\n";
			}
		}

		/// <summary>
		/// 保留 15 位小数 打印矩阵：
		/// </summary>
		void print_15()
		{
			cout << "\n\n矩阵的 行数：" << _n << " 列数：" << _m << "\n\n";
			cout << "\t" << _name << "=\n\n";
			for (int i = 1; i <= _n; i++)
			{
				cout << "第 " << i << " 行" << "\t  ";
				for (int j = 1; j <= _m; j++)
				{
					printf("%.15f\t", (*this)(i, j));
				}
				cout << "\n\n";
			}
		}

		/// <summary>
		/// 保留 6 位小数 打印矩阵：
		/// </summary>
		void print_6()
		{
			cout << "\n\n矩阵的 行数：" << _n << " 列数：" << _m << "\n\n";
			cout << "\t" << _name << "=\n\n";
			for (int i = 1; i <= _n; i++)
			{
				cout << "第 " << i << " 行" << "\t  ";
				for (int j = 1; j <= _m; j++)
				{
					printf("%.6f\t", (*this)(i, j));
				}
				cout << "\n\n";
			}
		}

		/// <summary>
		/// 普通打印矩阵：
		/// </summary>
		void print_double()
		{
			cout << "\n\n\t" << _name << "=\n\n";
			for (int i = 1; i <= _n; i++)
			{
				cout << "\t";
				for (int j = 1; j <= _m; j++)
				{
					cout << (*this)(i, j) << "\t";
				}
				cout << "\n\n";
			}
		}

		/// <summary>
		/// 保留 15 位小数 打印矩阵：
		/// </summary>
		void print_15_double()
		{
			cout << "\n\n\t" << _name << "=\n\n";
			for (int i = 1; i <= _n; i++)
			{
				cout << "\t";
				for (int j = 1; j <= _m; j++)
				{
					printf("%.15f\t", (*this)(i, j));
				}
				cout << "\n\n";
			}
		}

		/// <summary>
		/// 保留 6 位小数 打印矩阵：
		/// </summary>
		void print_6_double()
		{
			cout << "\n\n\t" << _name << "=\n\n";
			for (int i = 1; i <= _n; i++)
			{
				cout << "\t";
				for (int j = 1; j <= _m; j++)
				{
					printf("%.6f\t", (*this)(i, j));
				}
				cout << "\n\n";
			}
		}

		/// <summary>
		/// 当前矩阵是整型矩阵时，转换为浮点型矩阵，返回一个浮点型矩阵：
		/// </summary>
		/// <returns></returns>
		matlab<double> to_double()
		{
			matlab<double>d;
			d(_n, _m);
			for (int i = 0; i <= _n; i++)
			{
				for (int j = 0; j <= _m; j++)
				{
					d(i, j) = _arr[i][j];
				}
			}
			return d;
		}

		/// <summary>
		///求数值型矩阵的逆矩阵:
		/// </summary>
		/// <param name="arr"></param>
		/// <returns></returns>
		matlab<double> inv()
		{
			matlab<double> mat0;
			int n = _n;
			if (_n != _m || _n == 0)
			{
				cout << "\n\t当前矩阵不是数值方阵！不可逆：\n";
				return mat0;
			}
			matlab<double> mat1;
			string s = typeid((*this)(0, 0)).name();
			if (s != "int" && s != "double")
			{
				cout << "\n\t当前矩阵不是数值方阵！不可逆：\n";
				return mat0;
			}
			mat1 = (*this).to_double();
			matlab<double> mat2(n, n, 0);
			int i = 0, j = 0, c = 0;
			for (i = 1; i <= n; i++)
				{
					mat2(i, i) = 1;
				}
			for (i = 1; i <= n; i++)
				{
					if (mat1(i, i) == 0)
					{
						int k = 0;
						for (k = i + 1; k <= n; k++)
						{
							if (mat1(k, i) != 0)
								break;
						}
						if (k == n + 1)
						{
							cout << "\n\t当前矩阵不是有效方阵！不可逆：\n";
							return mat0;
						}
						matlab<double> d1;
						matlab<double> d2;
						d1 = mat2.lin(i);
						d2 = mat2.lin(k);
						mat2.lin(i, d2);
						mat2.lin(k, d1);
						d1 = mat1.lin(i);
						d2 = mat1.lin(k);
						mat1.lin(i, d2);
						mat1.lin(k, d1);
					}
					for (j = 1; j <= n; j++)
					{
						if (j == i)
							continue;
						double a = mat1(j, i) * 1.0 / mat1(i, i);
						for (c = 1; c <= n; c++)
						{
							mat1(j, c) -= a * mat1(i, c);
							mat2(j, c) -= a * mat2(i, c);
						}
					}
				}
			for (i = 1; i <= n; i++)
				{
					for (j = 1; j <= n; j++)
					{
						mat2(i, j) /= mat1(i, i);
					}
				}
			return mat2;
		}

		/// <summary>
		/// 求数值型矩阵的行列式:
		/// </summary>
		/// <returns></returns>
		T det()
		{
			matlab<double> mat0;
			int n = _n;
			if (n != _m || n == 0)
			{
				cout << "\n\t当前矩阵不是有效方阵！\n";
				return 0;
			}
			string s = typeid((*this)(0, 0)).name();
			matlab<double> mat1;
			if (s != "int" && s != "double")
			{
				cout << "\n\t当前矩阵不是数值方阵！\n";
				return 0;
			}
			mat1 = (*this).to_double();
			int i = 0, j = 0, c = 0;
			for (i = 1; i <= n; i++)
			{
				if (mat1(i, i) == 0)
				{
					int k = 0;
					for (k = i + 1; k <= n; k++)
					{
						if (mat1(k, i) != 0)
							break;
					}
					if (k == n + 1)
					{
						return 0;
					}
					matlab<double> d1;
					matlab<double> d2;
					d1 = mat1.lin(i);
					d2 = mat1.lin(k);
					mat1.lin(i, d2);
					mat1.lin(k, d1);
				}
				for (j = i + 1; j <= n; j++)
				{
					double a = mat1(j, i) * 1.0 / mat1(i, i);
					for (c = 1; c <= n; c++)
					{
						mat1(j, c) -= a * mat1(i, c);
					}
				}
			}
			double d = 1;
			for (i = 1; i <= n; i++)
			{
				d *= mat1(i, i);
			}
			return d;
		}

		/// <summary>
		/// 返回矩阵的转置矩阵：
		/// </summary>
		/// <returns></returns>
		matlab<T> transpose()
		{
			matlab<T> mat1(_m, _n);
			for (int i = 0; i <= _m; i++)
			{
				for (int j = 0; j <= _n; j++)
				{
					mat1(i, j) = (*this)(j, i);
				}
			}
			return mat1;
		}

		/// <summary>
		/// 矩阵的乘法运算符重载：
		/// </summary>
		/// <param name="mat1"></param>
		/// <returns></returns>
		matlab<T> operator*(matlab<T> mat1)
		{
			matlab<T> mat2;
			if (_m != mat1._n)
			{
				cout << "\n\t左矩阵的列数不等于右矩阵的行数：\n";
				return mat2;
			}
			mat2(_n, mat1._m);
			for (int i = 1; i <= _n; i++)
			{
				for (int j = 1; j <= mat1._m; j++)
				{
					mat2(i, j) = 0;
					for (int k = 1; k <= _m; k++)
					{
						mat2(i, j) += (*this)(i, k) * mat1(k, j);
					}
				}
			}
			return mat2;
		}

		/// <summary>
		/// 矩阵的加法运算符重载：
		/// </summary>
		/// <param name="mat1"></param>
		/// <returns></returns>
		matlab<T> operator+(matlab<T> mat1)
		{
			matlab<T> mat2;
			if (_n != mat1._n || _m != mat1._m)
			{
				cout << "\n\t左矩阵的行列数不等于右矩阵的行列数：\n";
				return mat2;
			}
			mat2(_n, _m);
			for (int i = 1; i <= _n; i++)
			{
				for (int j = 1; j <= mat1._m; j++)
				{
					mat2(i, j) = (*this)(i, j) + mat1(i, j);
				}
			}
			return mat2;
		}

		/// <summary>
		/// 矩阵的减法运算符重载：
		/// </summary>
		/// <param name="mat1"></param>
		/// <returns></returns>
		matlab<T> operator-(matlab<T> mat1)
		{
			matlab<T> mat2;
			if (_n != mat1._n || _m != mat1._m)
			{
				cout << "\n\t左矩阵的行列数不等于右矩阵的行列数：\n";
				return mat2;
			}
			mat2(_n, _m);
			for (int i = 1; i <= _n; i++)
			{
				for (int j = 1; j <= mat1._m; j++)
				{
					mat2(i, j) = (*this)(i, j) - mat1(i, j);
				}
			}
			return mat2;
		}

		/// <summary>
		/// 矩阵的指数运算符重载：
		/// </summary>
		/// <param name="mat1"></param>
		/// <returns></returns>
		matlab<double> operator^(int n)
		{
			matlab<T> mat2;
			matlab<double> mat3;
			if (_n != _m || _n == 0)
			{
				cout << "\n\t：矩阵不是有效方阵！\n";
				return mat3;
			}
			mat2(_n, _n);
			for (int i = 1; i <= _n; i++)
			{
				mat2(i, i) = 1;
			}
			for (int i = 1; i <= abs(n); i++)
			{
				mat2 = mat2 * (*this);
			}
			if (n < 0)
				return mat2.inv();
			for (int i = 1; i <= _n; i++)
			{
				for (int j = 1; j <= _n; j++)
				{
					mat3(i, j) = mat2(i, j);
				}
			}
			return mat3;
		}

		/// <summary>
		/// 矩阵与数字的乘法运算符重载：
		/// </summary>
		/// <param name="mat1"></param>
		/// <returns></returns>
		matlab<double> operator*(double d)
		{
			matlab<double> mat2;
			mat2(_n, _m);
			for (int i = 1; i <= _n; i++)
			{
				for (int j = 1; j <= _m; j++)
				{
					mat2(i, j) = d * (*this)(i, j);
				}
			}
			return mat2;
		}

		/// <summary>
		/// 输入矩阵：
		/// </summary>
		void input()
		{
			string s = typeid(_arr[0][0]).name();
			cout << "\n\n请输入矩阵名：";
			cin >> _name;
			while(getchar()!=10){}
			cout << "\n\n请输入矩阵行数: L=";
			int L = 0;
			scanf("%d", &L);
			while (L<1)
			{
				while (getchar() != 10) {}
				cout << "\n\n\t输入错误！\n\n\t请输入一个大于0的整数：L=";
				scanf("%d", &L);
			}
			while (getchar() != 10) {}
			cout << "\n\n请输入矩阵列数: C=";
			int C = 0;
			scanf("%d", &C);
			while (C < 1)
			{
				while (getchar() != 10) {}
				cout << "\n\n\t输入错误！\n\n\t请输入一个大于0的整数：C=";
				scanf("%d", &C);
			}
			while (getchar() != 10) {}
			(*this)(L, C);
			cout << "\n\t1 指定某一行某一列输入\n\n\t2 依次输入每个元素\n\n请选择您的矩阵输入方式:";
			int m = 0;
			scanf("%d", &m);
			while (m != 1 && m != 2)
			{
				while (getchar() != 10) {}
				cout << "\n\n\t输入错误！\n\n\t请输入 1 或者 2 的整数：";
				scanf("%d", &m);
			}
			while (getchar() != 10) {}
			if (m == 1)
			{
				cout << "\n请问您一共要输入几个元素：";
				int k = 0;
				scanf("%d", &k);
				while (k<1 || k>L * C)
				{
					while (getchar() != 10) {}
					cout << "\n\n\t输入错误！\n\n\t请输入一个 1-" << L * C << "的整数：";
					scanf("%d", &k);
				}
				while (getchar() != 10) {}
				for (int i = 1; i <= k; i++)
				{
					cout << "\n第" << i << "个要输入的元素的 行数： row=";
					int row = 0;
					scanf("%d", &row);
					while (row<1 || row>L)
					{
						while (getchar() != 10) {}
						cout << "\n\n\t输入错误！\n\n\t请输入一个 1-" << L << "的整数：row=";
						scanf("%d", &row);
					}
					while (getchar() != 10) {}
					cout << "\n第" << i << "个要输入的元素的 列数： col=";
					int col = 0;
					scanf("%d", &col);
					while (col<1 || col>C)
					{
						while (getchar() != 10) {}
						cout << "\n\n\t输入错误！\n\n\t请输入一个 1-" << C << "的整数：col=";
						scanf("%d", &col);
					}
					while (getchar() != 10) {}
					cout << "\n第" << i << "个要输入的元素的值： "<<_name<<"(" << row << ", " << col << ") = ";
					if (s != "int" && s != "double"&&s!="float")
					{
						cin >> (*this)(row, col);
						while(getchar()!=10){}
					}
					else
					{
						double d = -0.0000000000000000001;
						scanf("%lf", &d);
						while (d == -0.0000000000000000001)
						{
							while (getchar() != 10) {}
							cout << "\n\n\t输入错误！\n\n\t请输入一个实数: " << _name << "(" << row << ", " << col << ") = ";
							scanf("%d", &d);
						}
						while (getchar() != 10) {}
						(*this)(row, col) = d;
					}
				}
			}
			else
			{
				cout << "\n请依次输入每个元素的值：\n\n\t";
				if (s == "int" || s == "double" || s == "float")
				{
					double d = -0.0000000000000000001;
					int a = 1;
					while (a)
					{
						a = 0;
						for (int i = 1; i <= L; i++)
						{
							for (int j = 1; j <= C; j++)
							{
								scanf("%lf", &d);
								if (d != -0.0000000000000000001)
								{
									(*this)(i, j) = d;
									d = -0.0000000000000000001;
								}
								else
								{
									while (getchar() != 10) {}
									cout << "格式错误！请重新输入:\n\n\t";
									a = 1;
									break;
								}
							}
							if (a == 1)
								break;
						}
					}
					while (getchar() != 10) {}
				}
				else
				{
					for (int i = 1; i <= L; i++)
					{
						for (int j = 1; j <= C; j++)
						{
							cin >> (*this)(i, j);
						}
					}
					while(getchar()!=10){}
				}
			}
			print();
		}
	};

	/// <summary>
	/// double数字与矩阵乘法运算符重载：
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="d"></param>
	/// <param name="mat1"></param>
	/// <returns></returns>
	template<class T>
	matlab<double> operator*(double d, matlab<T> mat1)
	{
		matlab<double> mat2;
		mat2(mat1._n, mat1._m);
		for (int i = 1; i <= mat1._n; i++)
		{
			for (int j = 1; j <= mat1._m; j++)
			{
				mat2(i, j) = d * mat1(i, j);
			}
		}
		return mat2;
	}

	/// <summary>
	/// int数字与矩阵乘法运算符重载：
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="d"></param>
	/// <param name="mat1"></param>
	/// <returns></returns>
	template<class T>
	matlab<double> operator*(int d, matlab<T> mat1)
	{
		matlab<double> mat2;
		mat2(mat1._n, mat1._m);
		for (int i = 1; i <= mat1._n; i++)
		{
			for (int j = 1; j <= mat1._m; j++)
			{
				mat2(i, j) = d * mat1(i, j);
			}
		}
		return mat2;
	}

	void main_space();

	void menu();

	void det();

	void inv();

	void add();

	void mul();

	void sub();

	void index();

	void dia();

	matlab<double> mat_solve(string str);

	vector<string> fen_ge_str(string str);

	vector<string> fen_ge_str_1(string str);

	vector<string> mid_convert_beh(vector<string>& arr);

	matlab<double> solve_beh(vector<string>& arr);

	matlab<double> solve(vector<string>& arr);

	matlab<double> solve_str(string str);

	matlab<double> mat_solve_1(string str);

	void print_mat(matlab<double> mat1);
}

