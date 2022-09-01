#include "mat.h"

using namespace mat_namespace;

namespace mat_namespace
{
	int format = 0;
	vector<matlab<double>> Book;

	void (*pfun[9])() = { NULL,main_space,det,inv,add,mul,sub,index,dia};

	void menu()
	{
		cout << "\n                        欢迎来到：*** 矩阵空间***";
		printf("\n\n\t****************    0    退出	        ***************\n");
		printf("\n\t****************    1    矩阵**运算	***************\n");
		printf("\n\t****************    2    计算行列式	***************\n");
		printf("\n\t****************    3    计算逆矩阵	***************\n");
		printf("\n\t****************    4    矩阵的加法	***************\n");
		printf("\n\t****************    5    矩阵的乘法	***************\n");
		printf("\n\t****************    6    矩阵的减法	***************\n");
		printf("\n\t****************    7    矩阵的幂运算	***************\n");
		printf("\n\t****************    8    生成随机矩阵	***************\n\n\n\t\t\t");
	}

	void main_space()
	{
		system("cls");
		cout << "按 exit 退出当前矩阵运算空间:  按 clear 清空变量:  按 cls 清空屏幕";
		while (1)
		{
			cout << " \n\n=> ";
			string str;
			char c;
			while (1)
			{
				c = getchar();
				if (c != 10)
					break;
				else
					cout << " \n\n=> ";
			}
			while (c != 10)
			{
				str.push_back(c);
				c = getchar();
			}
			if (str == "exit")
			{
				return;
			}
			if (str == "clear")
			{
				system("cls");
				Book.clear();
				cout << "按 exit 退出当前矩阵运算空间:  按 clear 清空变量:  按 cls 清空屏幕";
				continue;
			}
			if (str == "cls")
			{
				system("cls");
				cout << "按 exit 退出当前矩阵运算空间:  按 clear 清空变量:  按 cls 清空屏幕";
				continue;
			}
			if (str == "format close")
			{
				format = 6;
				continue;
			}
			if (str == "format")
			{
				format = 0;
				continue;
			}
			if (str == "format 15")
			{
				format = 1;
				continue;
			}
			if (str == "format 6")
			{
				format = 2;
				continue;
			}
			if (str == "format +")
			{
				format = 3;
				continue;
			}
			if (str == "format 15+")
			{
				format = 4;
				continue;
			}
			if (str == "format 6+")
			{
				format = 5;
				continue;
			}
			if (str.substr(0, 4) == "det(")
			{
				int n = str.find(')');
				string s = str.substr(4, n - 4);
				vector<matlab<double>>::iterator it = Book.begin();
				matlab<double> d(1);
				int a = 0;
				while (it != Book.end())
				{
					if (it->_name == s)
					{
						a = 1;
						d(1, 1) = it->det();
						vector<matlab<double>>::iterator it = Book.begin();
						while (it != Book.end())
						{
							if (it->_name == "ans" || it->_name == d._name)
							{
								it = Book.erase(it);
							}
							else
							{
								it++;
							}
						}
						Book.push_back(d);
						break;
					}
					else
					{
						it++;
					}
				}
				if (a == 0)
				{
					cout << "\n\n\t" << s << " 未知变量！\n";
					continue;
				}
				print_mat(d);
				continue;
			}
			if (str.substr(0, 5) == "rand(")
			{
				int n = str.find(')');
				string s = str.substr(5, n - 5);
				n = 0;
				try
				{
					n = stoi(s);
				}
				catch (exception e)
				{
					cout << "\n\n\t" << s << " 格式错误！\n";
					continue;
				}
				srand((unsigned int)time(nullptr));
				matlab<double> d(n);
				for (int i = 0; i < n; i++)
				{
					for (int j = 0; j < n; j++)
					{
						d(i + 1, j + 1) = rand() % 100;
					}
				}
				vector<matlab<double>>::iterator it = Book.begin();
				while (it != Book.end())
				{
					if (it->_name == "ans" || it->_name == d._name)
					{
						it = Book.erase(it);
					}
					else
					{
						it++;
					}
				}
				Book.push_back(d);
				print_mat(d);
				continue;
			}
			if (str.substr(0, 4) == "dia(")
			{
				int n = str.find(')');
				string s = str.substr(4, n - 4);
				n = 0;
				try
				{
					n = stoi(s);
				}
				catch (exception e)
				{
					cout << "\n\n\t" << s << " 格式错误！\n";
					continue;
				}
				matlab<double> d(n);
				for (int i = 0; i < n; i++)
				{
					d(i + 1, i + 1) = i + 1;
				}
				vector<matlab<double>>::iterator it = Book.begin();
				while (it != Book.end())
				{
					if (it->_name == "ans" || it->_name == d._name)
					{
						it = Book.erase(it);
					}
					else
					{
						it++;
					}
				}
				Book.push_back(d);
				print_mat(d);
				continue;
			}
			if (str.substr(0, 4) == "sin(")
			{
				int n = str.find(')');
				string s = str.substr(4, n - 4);
				double x;
				try
				{
					x = solve_str(s)(1, 1);
				}
				catch (exception e)
				{
					cout << "\n\n\t" << s << " 格式错误！\n";
					continue;
				}
				matlab<double> d(1);
				d(1, 1) = sin(x);
				vector<matlab<double>>::iterator it = Book.begin();
				while (it != Book.end())
				{
					if (it->_name == "ans" || it->_name == d._name)
					{
						it = Book.erase(it);
					}
					else
					{
						it++;
					}
				}
				Book.push_back(d);
				print_mat(d);
				continue;
			}
			if (str.substr(0, 4) == "cos(")
			{
				int n = str.find(')');
				string s = str.substr(4, n - 4);
				double x;
				try
				{
					x = solve_str(s)(1, 1);;
				}
				catch (exception e)
				{
					cout << "\n\n\t" << s << " 格式错误！\n";
					continue;
				}
				matlab<double> d(1);
				d(1, 1) = cos(x);
				vector<matlab<double>>::iterator it = Book.begin();
				while (it != Book.end())
				{
					if (it->_name == "ans" || it->_name == d._name)
					{
						it = Book.erase(it);
					}
					else
					{
						it++;
					}
				}
				Book.push_back(d);
				print_mat(d);
				continue;
			}
			if (str.substr(0, 4) == "tan(")
			{
				int n = str.find(')');
				string s = str.substr(4, n - 4);
				double x;
				try
				{
					x = solve_str(s)(1, 1);
				}
				catch (exception e)
				{
					cout << "\n\n\t" << s << " 格式错误！\n";
					continue;
				}
				matlab<double> d(1);
				d(1, 1) = tan(x);
				vector<matlab<double>>::iterator it = Book.begin();
				while (it != Book.end())
				{
					if (it->_name == "ans" || it->_name == d._name)
					{
						it = Book.erase(it);
					}
					else
					{
						it++;
					}
				}
				Book.push_back(d);
				print_mat(d);
				continue;
			}
			if (str.substr(0, 3) == "ln(")
			{
				int n = str.find(')');
				string s = str.substr(3, n - 3);
				double x;
				try
				{
					x = solve_str(s)(1, 1);
				}
				catch (exception e)
				{
					cout << "\n\n\t" << s << " 格式错误！\n";
					continue;
				}
				matlab<double> d(1);
				d(1, 1) = log(x);
				vector<matlab<double>>::iterator it = Book.begin();
				while (it != Book.end())
				{
					if (it->_name == "ans" || it->_name == d._name)
					{
						it = Book.erase(it);
					}
					else
					{
						it++;
					}
				}
				Book.push_back(d);
				print_mat(d);
				continue;
			}
			if (str.substr(0, 5) == "sind(")
			{
				int n = str.find(')');
				string s = str.substr(5, n - 5);
				double x;
				try
				{
					x = solve_str(s)(1, 1);
				}
				catch (exception e)
				{
					cout << "\n\n\t" << s << " 格式错误！\n";
					continue;
				}
				matlab<double> d(1);
				d(1, 1) = sin(3.141592653 * x / 180);
				vector<matlab<double>>::iterator it = Book.begin();
				while (it != Book.end())
				{
					if (it->_name == "ans" || it->_name == d._name)
					{
						it = Book.erase(it);
					}
					else
					{
						it++;
					}
				}
				Book.push_back(d);
				print_mat(d);
				continue;
			}
			if (str.substr(0, 5) == "cosd(")
			{
				int n = str.find(')');
				string s = str.substr(5, n - 5);
				double x;
				try
				{
					x = solve_str(s)(1, 1);
				}
				catch (exception e)
				{
					cout << "\n\n\t" << s << " 格式错误！\n";
					continue;
				}
				matlab<double> d(1);
				d(1, 1) = cos(3.141592653 * x / 180);
				vector<matlab<double>>::iterator it = Book.begin();
				while (it != Book.end())
				{
					if (it->_name == "ans" || it->_name == d._name)
					{
						it = Book.erase(it);
					}
					else
					{
						it++;
					}
				}
				Book.push_back(d);
				print_mat(d);
				continue;
			}
			if (str.substr(0, 5) == "tand(")
			{
				int n = str.find(')');
				string s = str.substr(5, n - 5);
				double x;
				try
				{
					x = solve_str(s)(1, 1);
				}
				catch (exception e)
				{
					cout << "\n\n\t" << s << " 格式错误！\n";
					continue;
				}
				matlab<double> d(1);
				d(1, 1) = tan(3.141592653 * x / 180);
				vector<matlab<double>>::iterator it = Book.begin();
				while (it != Book.end())
				{
					if (it->_name == "ans" || it->_name == d._name)
					{
						it = Book.erase(it);
					}
					else
					{
						it++;
					}
				}
				Book.push_back(d);
				print_mat(d);
				continue;
			}
			int n1 = str.find('(');
			int n2 = str.find(',');
			int n3 = str.find(')');
			int n4 = str.find('=');
			if (n1 > 0 && n1 < n2 && n2 < n3)
			{
				if (n4 == -1)
				{
					matlab<double> mat1;
					vector<string> arr = fen_ge_str_1(str);
					if (arr.size() != 3)
					{
						cout << "\n\n\t表达式格式错误！\n";
						continue;
					}
					string s1 = arr[0];
					while (s1.back() == ' ')
					{
						s1.pop_back();
					}
					string s2 = arr[1];
					string s3 = arr[2];
					if (s2 == ":")
					{
						matlab<double> d = mat_solve_1(s3);
						int k = d.col();
						if (k == 0)
						{
							continue;
						}
						vector<int> arr;
						for (int n = 0; n < k; n++)
						{
							arr.push_back(d(1, n + 1));
						}
						vector<matlab<double>>::iterator it = Book.begin();
						int a = 0;
						while (it != Book.end())
						{
							if (it->_name == s1)
							{
								a = 1;
								mat1 = (*it).col(arr);
								break;
							}
							else
							{
								it++;
							}
						}
						if (a == 0)
						{
							cout << "\n\n\t" << s1 << " 不是矩阵变量名！\n";
							continue;
						}
					}
					else if (s3 == ":")
					{
						matlab<double> d = mat_solve_1(s2);
						int k = d.col();
						if (k == 0)
						{
							continue;
						}
						vector<int> arr;
						for (int n = 0; n < k; n++)
						{
							arr.push_back(d(1, n + 1));
						}
						vector<matlab<double>>::iterator it = Book.begin();
						int a = 0;
						while (it != Book.end())
						{
							if (it->_name == s1)
							{
								a = 1;
								mat1 = (*it).lin(arr);
								break;
							}
							else
							{
								it++;
							}
						}
						if (a == 0)
						{
							cout << "\n\n\t" << s1 << " 不是矩阵变量名！\n";
							continue;
						}
					}
					else
					{
						matlab<double> d2 = mat_solve_1(s2);
						matlab<double> d3 = mat_solve_1(s3);
						int k2 = d2.col();
						int k3 = d3.col();
						if (k2 == 0 || k3 == 0)
						{
							continue;
						}
						vector<int> arr2, arr3;
						for (int n = 0; n < k2; n++)
						{
							arr2.push_back(d2(1, n + 1));
						}
						for (int n = 0; n < k3; n++)
						{
							arr3.push_back(d3(1, n + 1));
						}
						vector<matlab<double>>::iterator it = Book.begin();
						int a = 0;
						while (it != Book.end())
						{
							if (it->_name == s1)
							{
								a = 1;
								mat1 = (*it)(arr2, arr3);
								break;
							}
							else
							{
								it++;
							}
						}
						if (a == 0)
						{
							cout << "\n\n\t" << s1 << " 不是矩阵变量名！\n";
							continue;
						}
					}
					vector<matlab<double>>::iterator it = Book.begin();
					while (it != Book.end())
					{
						if (it->_name == "ans" || it->_name == mat1._name)
						{
							it = Book.erase(it);
						}
						else
						{
							it++;
						}
					}
					Book.push_back(mat1);
					switch (format)
					{
					case 6:
						break;
					case 0:
						mat1.print_double();
						break;
					case 1:
						mat1.print_15_double();
						break;
					case 2:
						mat1.print_6_double();
						break;
					case 3:
						mat1.print();
						break;
					case 4:
						mat1.print_15();
						break;
					case 5:
						mat1.print_6();
						break;
					}
				}
				else if (n4 > n3)
				{
					matlab<double> mat1;
					string s = str.substr(n4 + 1);
					int m1 = s.find('(');
					int m2 = s.find(',');
					int m3 = s.find(')');
					if (m1 > 0 && m1 < m2 && m2 < m3)
					{
						vector<string> arr = fen_ge_str_1(s);
						if (arr.size() != 3)
						{
							cout << "\n\n\t表达式格式错误！\n";
							continue;
						}
						string s1 = arr[0];
						while (s1.back() == ' ')
						{
							s1.pop_back();
						}
						string s2 = arr[1];
						string s3 = arr[2];
						if (s2 == ":")
						{
							matlab<double> d = mat_solve_1(s3);
							int k = d.col();
							if (k == 0)
							{
								continue;
							}
							vector<int> arr;
							for (int n = 0; n < k; n++)
							{
								arr.push_back(d(1, n + 1));
							}
							vector<matlab<double>>::iterator it = Book.begin();
							int a = 0;
							while (it != Book.end())
							{
								if (it->_name == s1)
								{
									a = 1;
									mat1 = (*it).col(arr);
									break;
								}
								else
								{
									it++;
								}
							}
							if (a == 0)
							{
								cout << "\n\n\t" << s1 << "未知的变量名！\n";
								continue;
							}
						}
						else if (s3 == ":")
						{
							matlab<double> d = mat_solve_1(s2);
							int k = d.col();
							if (k == 0)
							{
								continue;
							}
							vector<int> arr;
							for (int n = 0; n < k; n++)
							{
								arr.push_back(d(1, n + 1));
							}
							vector<matlab<double>>::iterator it = Book.begin();
							int a = 0;
							while (it != Book.end())
							{
								if (it->_name == s1)
								{
									a = 1;
									mat1 = (*it).lin(arr);
									break;
								}
								else
								{
									it++;
								}
							}
							if (a == 0)
							{
								cout << "\n\n\t" << s1 << "未知的变量名！\n";
								continue;
							}
						}
						else
						{
							matlab<double> d2 = mat_solve_1(s2);
							matlab<double> d3 = mat_solve_1(s3);
							int k2 = d2.col();
							int k3 = d3.col();
							if (k2 == 0 || k3 == 0)
							{
								continue;
							}
							vector<int> arr2, arr3;
							for (int n = 0; n < k2; n++)
							{
								arr2.push_back(d2(1, n + 1));
							}
							for (int n = 0; n < k3; n++)
							{
								arr3.push_back(d3(1, n + 1));
							}
							vector<matlab<double>>::iterator it = Book.begin();
							int a = 0;
							while (it != Book.end())
							{
								if (it->_name == s1)
								{
									a = 1;
									mat1 = (*it)(arr2, arr3);
									break;
								}
								else
								{
									it++;
								}
							}
							if (a == 0)
							{
								cout << "\n\n\t" << s1 << "未知的变量名！\n";
								continue;
							}
						}
					}
					else
					{
						mat1 = mat_solve_1(s);
					}
					string ss = str.substr(0, n4);
					vector<string> arr = fen_ge_str_1(ss);
					if (arr.size() != 3)
					{
						cout << "\n\n\t表达式格式错误！\n";
						continue;
					}
					string s1 = arr[0];
					while (s1.back() == ' ')
					{
						s1.pop_back();
					}
					string s2 = arr[1];
					string s3 = arr[2];
					if (s2 == ":")
					{
						matlab<double> d = mat_solve_1(s3);
						int k = d.col();
						if (k == 0)
						{
							continue;
						}
						vector<int> arr;
						for (int n = 0; n < k; n++)
						{
							arr.push_back(d(1, n + 1));
						}
						vector<matlab<double>>::iterator it = Book.begin();
						int a = 0;
						while (it != Book.end())
						{
							if (it->_name == s1)
							{
								a = 1;
								(*it).col(arr, mat1);
								mat1 = *it;
								break;
							}
							else
							{
								it++;
							}
						}
						if (a == 0)
						{
							int n = mat1.lin();
							matlab<double> d(n);
							d._name = s1;
							d.col(arr, mat1);
							Book.push_back(d);
							mat1 = d;
						}
					}
					else if (s3 == ":")
					{
						matlab<double> d = mat_solve_1(s2);
						int k = d.col();
						if (k == 0)
						{
							continue;
						}
						vector<int> arr;
						for (int n = 0; n < k; n++)
						{
							arr.push_back(d(1, n + 1));
						}
						vector<matlab<double>>::iterator it = Book.begin();
						int a = 0;
						while (it != Book.end())
						{
							if (it->_name == s1)
							{
								a = 1;
								(*it).lin(arr, mat1);
								mat1 = *it;
								break;
							}
							else
							{
								it++;
							}
						}
						if (a == 0)
						{
							int n = mat1.col();
							matlab<double> d(n);
							d._name = s1;
							d.lin(arr, mat1);
							Book.push_back(d);
							mat1 = d;
						}
					}
					else
					{
						matlab<double> d2 = mat_solve_1(s2);
						matlab<double> d3 = mat_solve_1(s3);
						int k2 = d2.col();
						int k3 = d3.col();
						if (k2 == 0 || k3 == 0)
						{
							continue;
						}
						vector<int> arr2, arr3;
						for (int n = 0; n < k2; n++)
						{
							arr2.push_back(d2(1, n + 1));
						}
						for (int n = 0; n < k3; n++)
						{
							arr3.push_back(d3(1, n + 1));
						}
						vector<matlab<double>>::iterator it = Book.begin();
						int a = 0;
						while (it != Book.end())
						{
							if (it->_name == s1)
							{
								a = 1;
								(*it)(arr2, arr3, mat1);
								mat1 = *it;
								break;
							}
							else
							{
								it++;
							}
						}
						if (a == 0)
						{

							matlab<double> d;
							d._name = s1;
							d(arr2, arr3, mat1);
							Book.push_back(d);
							mat1 = d;
						}
					}
					switch (format)
					{
					case 6:
						break;
					case 0:
						mat1.print_double();
						break;
					case 1:
						mat1.print_15_double();
						break;
					case 2:
						mat1.print_6_double();
						break;
					case 3:
						mat1.print();
						break;
					case 4:
						mat1.print_15();
						break;
					case 5:
						mat1.print_6();
						break;
					}
				}
				else if (n4 < n1)
				{
					matlab<double> mat1;
					string name = str.substr(0, n4);
					while (name.back() == ' ')
					{
						name.pop_back();
					}
					int k = 0;
					while (name[k] == ' ')
					{
						k++;
					}
					if (!((name[k] >= 'a' && name[k] <= 'z') || (name[k] >= 'A' && name[k] <= 'Z')))
					{
						cout << "\n\n\t格式错误！\n";
						continue;
					}
					name = name.substr(k);
					string s = str.substr(n4 + 1);
					vector<string> arr = fen_ge_str_1(s);
					if (arr.size() != 3)
					{
						cout << "\n\n\t表达式格式错误！\n";
						continue;
					}
					string s1 = arr[0];
					while (s1.back() == ' ')
					{
						s1.pop_back();
					}
					string s2 = arr[1];
					string s3 = arr[2];
					if (s2 == ":")
					{
						matlab<double> d = mat_solve_1(s3);
						int k = d.col();
						if (k == 0)
						{
							continue;
						}
						vector<int> arr;
						for (int n = 0; n < k; n++)
						{
							arr.push_back(d(1, n + 1));
						}
						vector<matlab<double>>::iterator it = Book.begin();
						int a = 0;
						while (it != Book.end())
						{
							if (it->_name == s1)
							{
								a = 1;
								mat1 = (*it).col(arr);
								break;
							}
							else
							{
								it++;
							}
						}
						if (a == 0)
						{
							cout << "\n\n\t" << s1 << " 不是矩阵变量名！\n";
							continue;
						}
					}
					else if (s3 == ":")
					{
						matlab<double> d = mat_solve_1(s2);
						int k = d.col();
						if (k == 0)
						{
							continue;
						}
						vector<int> arr;
						for (int n = 0; n < k; n++)
						{
							arr.push_back(d(1, n + 1));
						}
						vector<matlab<double>>::iterator it = Book.begin();
						int a = 0;
						while (it != Book.end())
						{
							if (it->_name == s1)
							{
								a = 1;
								mat1 = (*it).lin(arr);
								break;
							}
							else
							{
								it++;
							}
						}
						if (a == 0)
						{
							cout << "\n\n\t" << s1 << " 不是矩阵变量名！\n";
							continue;
						}
					}
					else
					{
						matlab<double> d2 = mat_solve_1(s2);
						matlab<double> d3 = mat_solve_1(s3);
						int k2 = d2.col();
						int k3 = d3.col();
						if (k2 == 0 || k3 == 0)
						{
							continue;
						}
						vector<int> arr2, arr3;
						for (int n = 0; n < k2; n++)
						{
							arr2.push_back(d2(1, n + 1));
						}
						for (int n = 0; n < k3; n++)
						{
							arr3.push_back(d3(1, n + 1));
						}
						vector<matlab<double>>::iterator it = Book.begin();
						int a = 0;
						while (it != Book.end())
						{
							if (it->_name == s1)
							{
								a = 1;
								mat1 = (*it)(arr2, arr3);
								break;
							}
							else
							{
								it++;
							}
						}
						if (a == 0)
						{
							cout << "\n\n\t" << s1 << " 不是矩阵变量名！\n";
							continue;
						}
					}
					mat1._name = name;
					vector<matlab<double>>::iterator it = Book.begin();
					while (it != Book.end())
					{
						if (it->_name == "ans" || it->_name == mat1._name)
						{
							it = Book.erase(it);
						}
						else
						{
							it++;
						}
					}
					Book.push_back(mat1);
					switch (format)
					{
					case 6:
						break;
					case 0:
						mat1.print_double();
						break;
					case 1:
						mat1.print_15_double();
						break;
					case 2:
						mat1.print_6_double();
						break;
					case 3:
						mat1.print();
						break;
					case 4:
						mat1.print_15();
						break;
					case 5:
						mat1.print_6();
						break;
					}
				}
				else
				{
					cout << "\n\n\t表达式格式错误！\n";
				}
			}
			else
			{
				mat_solve(str);
			}
		}
	}

	void det()
	{
		system("cls");
		cout << "\n\n请输入您要计算的方阵 A 的阶数: n=";
		int n = 0;
		scanf("%d", &n);
		while (n<2)
		{
			while (getchar() != 10) {}
			cout << "\n\n\t输入错误！\n\n\t请输入一个大于1的整数：n=";
			scanf("%d", &n);
		}
		while(getchar()!=10){}
		matlab<double> A(n);
		cout << "\n\t1 指定某一行某一列输入\n\n\t2 依次输入每个元素\n\n请选择您的矩阵输入方式:";
		int m = 0;
		scanf("%d", &m);
		while (m!=1&&m!=2)
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
			while (k<1||k>n*n)
			{
				while (getchar() != 10) {}
				cout << "\n\n\t输入错误！\n\n\t请输入一个 1-"<<n*n<<"的整数：";
				scanf("%d", &k);
			}
			while (getchar() != 10) {}
			for (int i = 1; i <= k; i++)
			{
				cout << "\n第" << i << "个要输入的元素的 行数： row=";
				int row = 0;
				scanf("%d", &row);
				while (row<1||row>n)
				{
					while (getchar() != 10) {}
					cout << "\n\n\t输入错误！\n\n\t请输入一个 1-"<<n<<"的整数：row=";
					scanf("%d", &row);
				}
				while (getchar() != 10) {}
				cout << "\n第" << i << "个要输入的元素的 列数： col=";
				int col = 0;
				scanf("%d", &col);
				while (col<1 || col>n)
				{
					while (getchar() != 10) {}
					cout << "\n\n\t输入错误！\n\n\t请输入一个 1-" << n << "的整数：col=";
					scanf("%d", &col);
				}
				while (getchar() != 10) {}
				cout << "\n第" << i << "个要输入的元素的 值： A("<<row<<","<<col<<")=";
				double d=-0.0000000000000000001;
				scanf("%lf", &d);
				while (d==-0.0000000000000000001)
				{
					while (getchar() != 10) {}
					cout << "\n\n\t输入错误！\n\n\t请输入一个实数: A(" << row << "," << col << ")=";
					scanf("%d", &d);
				}
				while (getchar() != 10) {}
				A(row, col) = d;
			}
		}
		else
		{
			cout << "\n请依次输入每个元素的值：\n\n\t";
			double d = -0.0000000000000000001;
			int a = 1;
			while (a)
			{
				a = 0;
				for (int i = 1; i <= n; i++)
				{
					for (int j = 1; j <= n; j++)
					{
						scanf("%lf", &d);
						if (d != -0.0000000000000000001)
						{
							A(i, j) = d;
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
			while(getchar()!=10){}
		}
		cout << "\n\n当前矩阵 A=";
		A.print();
		cout << "矩阵 A 的行列式 |A|=" << A.det() <<"\n\n\n";
		system("pause");
	}

	void add()
	{
		matlab<double> d;
		d.input();
		system("pause");
	}

	void inv()
	{
		system("cls");
		cout << "\n\n请输入您要计算的方阵 A 的阶数: n=";
		int n = 0;
		scanf("%d", &n);
		while (n<2)
		{
			while (getchar() != 10) {}
			cout << "\n\n\t输入错误！\n\n\t请输入一个大于1的整数：n=";
			scanf("%d", &n);
		}
		while (getchar() != 10) {}
		matlab<double> A(n);
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
			while (k<1 || k>n * n)
			{
				while (getchar() != 10) {}
				cout << "\n\n\t输入错误！\n\n\t请输入一个 1-" << n * n << "的整数：";
				scanf("%d", &k);
			}
			while (getchar() != 10) {}
			for (int i = 1; i <= k; i++)
			{
				cout << "\n第" << i << "个要输入的元素的 行数： row=";
				int row = 0;
				scanf("%d", &row);
				while (row<1 || row>n)
				{
					while (getchar() != 10) {}
					cout << "\n\n\t输入错误！\n\n\t请输入一个 1-" << n << "的整数：row=";
					scanf("%d", &row);
				}
				while (getchar() != 10) {}
				cout << "\n第" << i << "个要输入的元素的 列数： col=";
				int col = 0;
				scanf("%d", &col);
				while (col<1 || col>n)
				{
					while (getchar() != 10) {}
					cout << "\n\n\t输入错误！\n\n\t请输入一个 1-" << n << "的整数：col=";
					scanf("%d", &col);
				}
				while (getchar() != 10) {}
				cout << "\n第" << i << "个要输入的元素的 值： A(" << row << "," << col << ")=";
				double d = -0.0000000000000000001;
				scanf("%lf", &d);
				while (d == -0.0000000000000000001)
				{
					while (getchar() != 10) {}
					cout << "\n\n\t输入错误！\n\n\t请输入一个实数: A(" << row << "," << col << ")=";
					scanf("%d", &d);
				}
				while (getchar() != 10) {}
				A(row, col) = d;
			}
		}
		else
		{
			cout << "\n请依次输入每个元素的值：\n\n\t";
			double d = -0.0000000000000000001;
			int a = 1;
			while (a)
			{
				a = 0;
				for (int i = 1; i <= n; i++)
				{
					for (int j = 1; j <= n; j++)
					{
						scanf("%lf", &d);
						if (d != -0.0000000000000000001)
						{
							A(i, j) = d;
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
		cout << "\n\n当前矩阵 A=";
		A.print();
		cout << "矩阵 A 的逆矩阵 A^(-1)=";
		A.inv().print();
		system("pause");
	}

	void mul()
	{
		cout << "mul()" << endl;
		system("pause");
	}

	void sub()
	{
		cout << "sub()" << endl;
		system("pause");
	}

	void index()
	{
		cout << "index()" << endl;
		system("pause");
	}

	void dia()
	{
		cout << "dia()" << endl;
		system("pause");
	}
	
	/// <summary>
	/// 分割  矩阵初始赋值  字符串 A=[1 2 3; 4 5 6; 7 8 9]:
	/// </summary>
	/// <param name="str"></param>
	/// <returns></returns>
	vector<string> fen_ge_str(string str)
	{
		int i = str.find('[');
		int j = str.find(']');
		vector<string> arr;
		arr.push_back("");
		for (int n = i + 1; n < j; n++)
		{
			int k = arr.size() - 1;
			if (str[n] != ' '&& str[n] != ';')
			{
				arr[k].push_back(str[n]);
			}
			else
			{
				if (str[n] == ';')
				{
					if (arr[k].empty())
					{
						arr[k].push_back(';');
						arr.push_back("");
					}
					else
					{
						arr.push_back("");
						arr[k + 1].push_back(';');
						arr.push_back("");
					}
				}
				else
				{
					if (!arr[k].empty())
					{
						arr.push_back("");
					}
				}
			}
		}
		if (arr.back().empty())
		{
			arr.back().push_back(';');
		}
		else
		{
			arr.push_back(";");
		}
		return arr;
	}

	/// <summary>
	/// 分割  矩阵赋值  字符串 A(1,2):
	/// </summary>
	/// <param name="str"></param>
	/// <returns></returns>
	vector<string> fen_ge_str_1(string str)
	{
		vector<string> arr;
		int k = 0;
		while (str[k] == ' ')
		{
			k++;
		}
		if (!((str[k] >= 'a' && str[k] <= 'z') || (str[k] >= 'A' && str[k] <= 'Z')))
		{
			return arr;
		}
		arr.push_back("");
		for (int n = k; n < str.size(); n++)
		{
			int k = arr.size() - 1;
			if (str[n] != ',' && str[n] != '('&&str[n]!=')'&&str[n]!=':')
			{
					arr[k].push_back(str[n]);
			}
			else
			{
				if (str[n] == ':')
				{
					if (arr[k].empty())
					{
						arr[k].push_back(':');
						arr.push_back("");
					}
					else
					{
						arr.push_back("");
						arr[k + 1].push_back(':');
						arr.push_back("");
					}
				}
				else
				{
					if (!arr[k].empty())
					{
						arr.push_back("");
					}
				}
			}
		}
		if (arr.back().empty())
		{
			arr.pop_back();
		}
		return arr;
	}

	/// <summary>
	/// 把字符串换算成矩阵：
	/// </summary>
	/// <param name="str"></param>
	matlab<double> mat_solve(string str)
	{
		matlab<double> mat1;
		int n1 = str.find('=');
		int n2 = str.find('[');
		int n3 = str.find(']');
		if (n2 >= 0 && n3 >= 0)
		{
			vector<string> arr = fen_ge_str(str);
			stack<double> st1;
			stack<double> st2;
			if (n1 >= 0)
			{
				int k = 0;
				while (str[k] == ' ')
				{
					k++;
				}
				if ((str[k] >= 'a' && str[k] <= 'z') || (str[k] >= 'A' && str[k] <= 'Z'))
				{
					mat1._name = str.substr(k, n1-k);
					while (mat1._name.back() == ' ')
					{
						mat1._name.pop_back();
					}
				}
				else
				{
					cout << "\n\n\t" << str.substr(0, n1) << "不是规范的矩阵名：\n";
					return mat1;
				}
			}
			for (auto i : arr)
			{
				if (i != ";")
				{
					double d;
					try
					{
						d = stod(i);
					}
					catch (exception e)
					{
						cout << "\n\n\t" << i << "格式错误！\n";
						return mat1;
					}
					st1.push(d);
				}
				else
				{
					int L = mat1.lin() + 1;
					int C = 0;
					while (!st1.empty())
					{
						st2.push(st1.top());
						st1.pop();
					}
					while (!st2.empty())
					{
						C++;
						mat1(L, C) = st2.top();
						st2.pop();
					}
				}
			}
			vector<matlab<double>>::iterator it = Book.begin();
			while (it != Book.end())
			{
				if (it->_name == "ans"||it->_name==mat1._name)
				{
					it=Book.erase(it);
				}
				else
				{
					it++;
				}
			}
			Book.push_back(mat1);
			switch (format)
			{
				case 6:
					break;
				case 0:
					mat1.print_double();
					return mat1;
				case 1:
					mat1.print_15_double();
					return mat1;
				case 2:
					mat1.print_6_double();
					return mat1;
				case 3:
					mat1.print();
					return mat1;
				case 4:
					mat1.print_15();
					return mat1;
				case 5:
					mat1.print_6();
					return mat1;
			}
			return mat1;
		}
		if (n2 == -1 && n3 == -1)
		{
			if (n1 >= 0)
			{
				int k = 0;
				while (str[k] == ' ')
				{
					k++;
				}
				if ((str[k] >= 'a' && str[k] <= 'z') || (str[k] >= 'A' && str[k] <= 'Z'))
				{
					mat1._name = str.substr(k, n1 - k);
					while (mat1._name.back() == ' ')
					{
						mat1._name.pop_back();
					}
				}
				else
				{
					cout << "\n\n\t" << str.substr(0, n1) << "不是规范的矩阵名：\n";
					return mat1;
				}
			}
			int i = n1 + 1;
			string s = str.substr(i);
			string name = mat1._name;
			mat1 = solve_str(s);
			if (name != "ans")
			{
				mat1._name = name;
			}
			vector<matlab<double>>::iterator it = Book.begin();
			while (it != Book.end())
			{
				if (it->_name == "ans" || it->_name == mat1._name)
				{
					it = Book.erase(it);
				}
				else
				{
					it++;
				}
			}
			Book.push_back(mat1);
			switch (format)
			{
			case 6:
				break;
			case 0:
				mat1.print_double();
				return mat1;
			case 1:
				mat1.print_15_double();
				return mat1;
			case 2:
				mat1.print_6_double();
				return mat1;
			case 3:
				mat1.print();
				return mat1;
			case 4:
				mat1.print_15();
				return mat1;
			case 5:
				mat1.print_6();
				return mat1;
			}
			return mat1;
		}
		cout << "\n\n\t表达式格式错误！\n";
		return mat1;
	}

	/// <summary>
	/// 把字符串变换成字符串数组：
	/// </summary>
	/// <param name="str"></param>
	/// <returns></returns>
	matlab<double> solve_str(string str)
	{
		int k9 = str.find(',');
		if (k9 != -1)
		{
			matlab<double> d;
			cout << "\n\n\t格式错误！\n";
			return d;
		}
		vector<string> arr;
		arr.push_back("");
		for (auto& i : str)
		{
			int n = arr.size() - 1;
			if (i==' '||i == '+' || i == '-' || i == '*' || i == '/' || i == '^' || i == '(' || i == ')'||i=='\'')
			{
				if (arr[n].empty())
				{
					if (i == '-' && (n == 0 || arr[n - 1] == "(" || arr[n - 1] == "^"))
					{
						arr[n].push_back(i);
					}
					else
					{
						if (i != ' ')
						{
							arr[n].push_back(i);
							arr.push_back("");
						}
					}
				}
				else
				{
					if (i != ' ')
					{
						arr.push_back("");
						arr[n + 1].push_back(i);
						arr.push_back("");
					}
					else
					{
						arr.push_back("");
					}
					
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

	/// <summary>
	/// 中缀表达式转后缀表达式：
	/// </summary>
	/// <param name="arr"></param>
	/// <returns></returns>
	vector<string> mid_convert_beh(vector<string>& arr)
	{
		vector<string> ret;
		stack<string> st;
		for (auto i : arr)
		{
			if (i != "+" && i != "-" && i != "*"&& i!="/"&& i != "^"&&i!="'")
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
				else if (i == "*"||i=="/")
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
					else if (s == "*"||s=="/")
					{
						ps = 2;
					}
					else
					{
						ps = 3;
					}
					if (pi > ps)
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

	/// <summary>
	/// 计算后缀表达式：
	/// </summary>
	/// <param name="arr"></param>
	/// <returns></returns>
	matlab<double> solve_beh(vector<string>& arr)
	{
		matlab<double> mat1;
		stack<matlab<double>>st;
		for (auto& i : arr)
		{
			if (i != "+" && i != "-" && i != "*"&&i!="/" && i != "^"&&i!="'")
			{
				try
				{
					matlab<double>d(1,1);
					d(1, 1) = stod(i);
					st.push(d);

				}
				catch (exception e)
				{
					int a = 0;
					for (auto& e : Book)
					{
						if (i == e._name)
						{
							st.push(e);
							a = 1;
							break;
						}
					}
					if (a == 0)
					{
						cout << "\n\n\t" << i << " 未知变量！\n";
						return mat1;
					}
				}
			}
			else
			{
				if (i != "'")
				{
					matlab<double> right;
					matlab<double> left;
					if (st.empty())
					{
						cout << "\n\n\t表达式格式错误！\n";
						return mat1;
					}
					right = st.top();
					st.pop();
					if (st.empty())
					{
						cout << "\n\n\t表达式格式错误！\n";
						return mat1;
					}
					left = st.top();
					st.pop();
					double rt, lt;
					int n1 = 0, n2 = 0;
					if (right.lin() == 1 && right.col() == 1)
					{
						rt = right(1, 1);
						n1 = 1;
					}
					if (left.lin() == 1 && left.col() == 1)
					{
						lt = left(1, 1);
						n2 = 1;
					}
					if (n1 == 0 && n2 == 0)
					{
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
							cout << "\n\n\t表达式格式错误\n";
							return mat1;
						case '^':
							cout << "\n\n\t表达式格式错误\n";
							return mat1;
						}
					}
					else if (n1 == 1 && n2 == 0)
					{
						switch (i[0])
						{
						case '+':
							cout << "\n\n\t表达式格式错误\n";
							return mat1;
						case '-':
							cout << "\n\n\t表达式格式错误\n";
							return mat1;
						case '*':
							st.push(left * rt);
							break;
						case '/':
							cout << "\n\n\t表达式格式错误\n";
							return mat1;
						case '^':
							st.push(left ^ rt);
							break;
						}
					}
					else if (n1 == 0 && n2 == 1)
					{
						switch (i[0])
						{
						case '+':
							cout << "\n\n\t表达式格式错误\n";
							return mat1;
						case '-':
							cout << "\n\n\t表达式格式错误\n";
							return mat1;
						case '*':
							st.push(lt * right);
							break;
						case '/':
							cout << "\n\n\t表达式格式错误\n";
							return mat1;
						case '^':
							cout << "\n\n\t表达式格式错误\n";
							return mat1;
						}
					}
					else
					{
						matlab<double>d(1, 1);
						switch (i[0])
						{
						case '+':
							d(1, 1) = lt + rt;
							st.push(d);
							break;
						case '-':
							d(1, 1) = lt - rt;
							st.push(d);
							break;
						case '*':
							d(1, 1) = lt * rt;
							st.push(d);
							break;
						case '/':
							d(1, 1) = lt / rt;
							st.push(d);
							break;
						case '^':
							d(1, 1) = pow(lt, rt);
							st.push(d);
							break;
						}
					}
				}
				else
				{
					matlab<double> d;
					if (st.empty())
					{
						cout << "\n\n\t表达式格式错误！\n";
						return mat1;
					}
					d = st.top();
					st.pop();
					st.push(d.transpose());
				}
			}
		}
		return st.top();
	}

	/// <summary>
	/// 计算中缀表达式
	/// </summary>
	/// <param name="arr"></param>
	/// <returns></returns>
	matlab<double> solve(vector<string>& arr)
	{
		matlab<double>mat1;
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
				if (st.empty())
				{
					cout << "\n\n\t表达式格式错误！\n";
					return mat1;
				}
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
				matlab<double> d = solve_beh(arr2);
				int n = Book.size();
				string s = "mat";
				string s0 = to_string(n+1);
				s.append(s0);
				d._name = s;
				Book.push_back(d);
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

	/// <summary>
	/// 把字符串换算成矩阵运算_2：
	/// </summary>
	/// <param name="str"></param>
	matlab<double> mat_solve_1(string str)
	{
		matlab<double> mat1;
		int n2 = str.find('[');
		int n3 = str.find(']');
		if (n2 >= 0 && n3 >= 0)
		{
			vector<string> arr = fen_ge_str(str);
			stack<double> st1;
			stack<double> st2;
			for (auto i : arr)
			{
				if (i != ";")
				{
					double d;
					try
					{
						d = stod(i);
					}
					catch (exception e)
					{
						cout << "\n\n\t" << i << "格式错误！\n";
						return mat1;
					}
					st1.push(d);
				}
				else
				{
					int L = mat1.lin() + 1;
					int C = 0;
					while (!st1.empty())
					{
						st2.push(st1.top());
						st1.pop();
					}
					while (!st2.empty())
					{
						C++;
						mat1(L, C) = st2.top();
						st2.pop();
					}
				}
			}
			return mat1;
		}
		if (n2 == -1 && n3 == -1)
		{
			return solve_str(str);
		}
		return mat1;
	}

	/// <summary>
	/// 输出矩阵标准函数：
	/// </summary>
	/// <param name="mat1"></param>
	void print_mat(matlab<double> mat1)
	{
		switch (format)
		{
		case 6:
			break;
		case 0:
			mat1.print_double();
			break;
		case 1:
			mat1.print_15_double();
			break;
		case 2:
			mat1.print_6_double();
			break;
		case 3:
			mat1.print();
			break;
		case 4:
			mat1.print_15();
			break;
		case 5:
			mat1.print_6();
			break;
		}
	}
}

void main()
{
	while (1)
	{
		system("cls");
		menu();
		printf("请输入您的选择： ");
		int n = -1;
		scanf("%d", &n);
		while (n < 0 || n>8)
		{
			cout << "\n\t\t输入错误：\n\n\t\t请输入0-8的整数:";
			while (getchar() != 10) {}
			scanf("%d", &n);
		}
		while (getchar() != 10) {}
		if (n == 0)
			break;
		pfun[n]();
	}
}

