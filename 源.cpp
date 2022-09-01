#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<list>
#include<stack>
#include<queue>
#include<set>
#include<stdio.h>
#include<stdlib.h>
#include<bitset>
#include<unordered_map>
#include<mutex>
#include<thread>

using namespace std;

namespace Lyw
{
#define MAX ~(1<<31)


	/// <summary>
	/// 判断popV数组是否可以是pushV数组的出栈顺序：
	/// </summary>
	/// <param name="pushV">入栈顺序数组</param>
	/// <param name="popV">出栈顺序数组</param>
	/// <returns>布尔值</returns>
	bool IsPopOrder(vector<int>pushV, vector<int>popV)
	{
		if (pushV.size() != popV.size())
		{
			return false;
		}
		int n = pushV.size();
		int i = 0, j = 0;
		stack<int>st;
		while (j < n)
		{
			if (st.empty() || st.top() != popV[j])
			{
				if (i == n)
				{
					return false;
				}
				st.push(pushV[i]);
				i++;
			}
			else
			{
				st.pop();
				j++;
			}
		}
		return true;
	}

	/// <summary>
	/// 解析算数字符串
	/// </summary>
	/// <param name="str">普通算式string："-25 +89+78*(59-37)/(-3)"</param>
	/// <returns>字符串数组：["-25","+","89","+","78".....]</returns>
	vector<string> solve_string(string str)
	{
		int n = str.size();
		vector<string>ret;
		ret.push_back("");
		int j = 0;
		for (int i = 0; i < n; i++)
		{
			if (!(str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '^' || str[i] == ' ' || str[i] == '(' || str[i] == ')'))
			{
				ret[j].push_back(str[i]);
				continue;
			}
			if (str[i] == '-' && (i == 0 || str[i - 1] == '('))
			{
				if (str[i + 1] == '(')
				{
					ret[j].append("-1");
					ret.push_back("*");
					j++;
					ret.push_back("");
					j++;
					continue;
				}
				ret[j].push_back(str[i]);
				continue;
			}
			if (str[i] == '('&&i>0&&str[i-1]>='0'&&str[i-1]<='9')
			{
				ret.push_back("*");
				j++;
				ret.push_back("");
				j++;
			}
			if (str[i] != ' ')
			{
				if (ret[j].size() != 0)
				{
					ret.push_back("");
					j++;
				}
				ret[j].push_back(str[i]);
				ret.push_back("");
				j++;
			}
		}
		if (ret[j].size() == 0)
		{
			ret.pop_back();
		}
		return ret;
	}

	/// <summary>
	/// 求逆波兰表达式:将解析后的字符串数组变为逆波兰表达式
	/// </summary>
	/// <param name="arr"></param>
	/// <returns>逆波兰表达式</returns>
	vector<string> NiBoLan_string(vector<string> arr)
	{
		stack<string> st;
		vector<string> arr1;
		map<string, int>map;
		map["+"] = 1;
		map["-"] = 1;
		map["*"] = 2;
		map["/"] = 2;
		map["^"] = 3;
		for (auto& e : arr)
		{
			if (e != "+" && e != "-" && e != "*" && e != "/" && e != "^" && e != "(" && e != ")")
			{
				arr1.push_back(e);
				continue;
			}
			if (e == "(")
			{
				st.push(e);
				continue;
			}
			if (e == ")")
			{
				while (st.top() != "(")
				{
					arr1.push_back(st.top());
					st.pop();
				}
				st.pop();
				continue;
			}
			while (!st.empty() && st.top() != "(" && map[e] <= map[st.top()])
			{
				arr1.push_back(st.top());
				st.pop();
			}
			st.push(e);
		}
		while (!st.empty())
		{
			arr1.push_back(st.top());
			st.pop();
		}
		return arr1;
	}
	/// <summary>
	///  求逆波兰表达式:将原始字符串变为逆波兰表达式
	/// </summary>
	/// <param name="str"></param>
	/// <returns></returns>
	vector<string> NiBoLan_string(string str)
	{
		return NiBoLan_string(solve_string(str));
	}

	/// <summary>
	/// 将逆波兰表达式计算出结果：
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	double solve(vector<string>arr)
	{
		stack<double> st;
		for (auto& e : arr)
		{
			if (e != "+" && e != "-" && e != "*" && e != "/" && e != "^")
			{
				st.push(stod(e));
				continue;
			}
			if (st.empty())
			{
				cout << "表达式格式错误:\n";
				exit(1);
			}
			double d2 = st.top();
			st.pop();
			if (st.empty())
			{
				cout << "表达式格式错误:\n";
				exit(1);
			}
			double d1 = st.top();
			st.pop();
			if (e == "+")
			{
				st.push(d1 + d2);
			}
			else if (e == "-")
			{
				st.push(d1 - d2);
			}
			else if (e == "*")
			{
				st.push(d1 * d2);
			}
			else if (e == "/")
			{
				st.push(d1 / d2);
			}
			else
			{
				st.push(pow(d1, d2));
			}
		}
		return st.top();
	}


	/// <summary>
	/// 计算字符串表达式
	/// </summary>
	/// <param name="str"></param>
	/// <returns></returns>
	double solve(string str)
	{
		return solve(NiBoLan_string(solve_string(str)));
	}



	/// <summary>
	/// 两个榨实现一个队列
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<class T>
	class queue
	{
		stack<T> st1;
		stack<T> st2;
		int n;
	public:
		queue():n(0){}
		void push(T t)
		{
			st1.push(t);
			n++;
		}
		void pop()
		{
			if (st2.empty())
			{
				while (!st1.empty())
				{
					st2.push(st1.top());
					st1.pop();
				}
			}
			st2.pop();
			n--;
		}
		T front()
		{
			if (st2.empty())
			{
				while (!st1.empty())
				{
					st2.push(st1.top());
					st1.pop();
				}
			}
			return st2.top();
		}
		bool empty()
		{
			return !n;
		}



	};

	/// <summary>
	/// 优先级队列：底层堆结构
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <typeparam name="Container"></typeparam>
	/// <typeparam name="Compare"></typeparam>
	template<class T , class Container=std::vector<T>,class Compare=less<T>>
	class priority_queue
	{
		Container ct;
		Compare cp;
		void adjustDown( int parent)
		{
			int n = ct.size();
			int left = parent * 2 + 1, right = parent * 2 + 2;
			while (left < n)
			{
				if (right < n)
				{
					if (cp(ct[parent], ct[left]) && cp(ct[parent], ct[right]))
					{
						return;
					}
					else if (cp(ct[left], ct[right]))
					{
						T t = ct[parent];
						ct[parent] = ct[left];
						ct[left] = t;
						parent = left;
						left = parent * 2 + 1;
						right = parent * 2 + 2;
					}
					else
					{
						T t = ct[parent];
						ct[parent] = ct[right];
						ct[right] = t;
						parent = right;
						left = parent * 2 + 1;
						right = parent * 2 + 2;
					}
				}
				else
				{
					if (cp(ct[left], ct[parent]))
					{
						T t = ct[parent];
						ct[parent] = ct[left];
						ct[left] = t;
					}
					return;
				}
			}
			return;
		}
		void adjustUp(int child)
		{
			int parent;
			while (child)
			{
				parent = (child - 1) / 2;
				if (cp(ct[parent], ct[child]))
				{
					return;
				}
				T t = ct[parent];
				ct[parent] = ct[child];
				ct[child] = t;
				child = parent;
			}
		}
	public:
		priority_queue(){}
		priority_queue(Container arr)
			:ct(arr)
		{
			int n = ct.size();
			int parent = (n - 2) / 2;
			while (parent>=0)
			{
				adjustDown(parent);
				parent -= 1;
			}
		}
		void push(T t)
		{
			ct.push_back(t);
			adjustUp(ct.size() - 1);
		}
		void pop()
		{
			int n = ct.size() - 1;
			ct[0] = ct[n];
			ct.pop_back();
			adjustDown(0);
		}
		T top()
		{
			return ct[0];
		}
		int size()
		{
			return ct.size();
		}
		bool empty()
		{
			return ct.empty();
		}
	};

	/// <summary>
	/// 堆排序：
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <typeparam name="Container"></typeparam>
	/// <typeparam name="Compare"></typeparam>
	template<class T, class Container = std::vector<T>, class Compare = greater<T>>
	class HeapSort
	{
		void adjustDown(Container& ct,int parent,int n)
		{
			Compare cp;
			int left = parent * 2 + 1, right = parent * 2 + 2;
			while (left < n)
			{
				if (right < n)
				{
					if (cp(ct[parent], ct[left]) && cp(ct[parent], ct[right]))
					{
						return;
					}
					else if (cp(ct[left], ct[right]))
					{
						T t = ct[parent];
						ct[parent] = ct[left];
						ct[left] = t;
						parent = left;
						left = parent * 2 + 1;
						right = parent * 2 + 2;
					}
					else
					{
						T t = ct[parent];
						ct[parent] = ct[right];
						ct[right] = t;
						parent = right;
						left = parent * 2 + 1;
						right = parent * 2 + 2;
					}
				}
				else
				{
					if (cp(ct[left], ct[parent]))
					{
						T t = ct[parent];
						ct[parent] = ct[left];
						ct[left] = t;
					}
					return;
				}
			}
		}
	public:
		bool operator()(Container& ct)
		{
			int n = ct.size();
			int parent = (n - 2) / 2;
			while (parent >= 0)
			{
				adjustDown(ct, parent, n);
				parent--;
			}
			while (n>1)
			{
				T t = ct[0];
				ct[0] = ct[n - 1];
				ct[n - 1] = t;
				adjustDown(ct, 0, --n);
			}
			return true;
		}
	};


	void adjustDown(vector<int>& arr, int parent, int n)
	{
		int left = parent * 2 + 1, right = parent*2+2;
		while (left < n)
		{
			if (right < n)
			{
				if (arr[parent] >= arr[left] && arr[parent] >= arr[right])
				{
					return;
				}
				if (arr[left] >= arr[right])
				{
					int a = arr[left];
					arr[left] = arr[parent];
					arr[parent] = a;
					parent = left;
					left = parent * 2 + 1;
					right = left + 1;
					continue;
				}
				int a = arr[right];
				arr[right] = arr[parent];
				arr[parent] = a;
				parent = right;
				left = parent * 2 + 1;
				right = left + 1;
				continue;
			}
			if (arr[parent] >= arr[left])
			{
				return;
			}
			int a = arr[left];
			arr[left] = arr[parent];
			arr[parent] = a;
			return;
		}

	}

	void heapSort(vector<int>& arr)
	{
		int parent = (arr.size() - 2) / 2;
		int n = arr.size();
		while (parent >= 0)
		{
			adjustDown(arr, parent--, n);
		}
		while (n > 1)
		{
			int a = arr[0];
			arr[0] = arr[n - 1];
			arr[n - 1] = a;
			adjustDown(arr, 0, --n);
		}
	}


	template<class T>
	class circle_queue
	{
		vector<T> arr;
		int front;
		int rear;
	public:
		circle_queue(int k) :arr(k + 1), front(0), rear(0) {}///循环队列的大小为k
		bool empty()
		{
			return front == rear;
		}

		bool full()
		{
			return (rear + 1) % arr.size() == front;
		}

		bool push(T t)
		{
			if (full())
			{
				return false;
			}
			arr[rear] = t;
			rear += 1;
			rear %= arr.size();
			return true;
		}

		bool pop()
		{
			if (empty())
			{
				return false;
			}
			front += 1;
			front %= arr.size();
			return true;
		}

		T Front()
		{
			if(empty())
			{
				cout << "空队列无法取出队首元素：";
				exit(1);
			}
			return arr[front];
		}

	};

	template<class T>
	class treeNode
	{
	public:
		T val;
		treeNode* left;
		treeNode* right;
		treeNode(T x):val(x),left(NULL),right(NULL){}
	};


	treeNode<char>* createTree(string str)
	{
		treeNode<char>* root=NULL;
		if (str.size()==0||str[0] == '#')
		{
			return root;
		}
		int n = str.size();
		stack<treeNode<char>*>st;
		root = new treeNode<char>(str[0]);
		st.push(root);
		for (int i = 1; i < n; i++)
		{
			if (str[i] != '#')
			{
				treeNode<char>* p = new treeNode<char>(str[i]);
				st.top()->left = p;
				st.push(p);
				continue;
			}
			st.top()->left = NULL;
			i++;
			while (i<n&&str[i] == '#')
			{
				st.top()->right = NULL;
				i++;
				st.pop();
			}
			if (i == n)
				break;
			treeNode<char>* p = new treeNode<char>(str[i]);
			st.top()->right = p;
			st.pop();
			st.push(p);
		}
		return root;
	}




	/// <summary>
	/// 非递归前序遍历二叉树
	/// </summary>
	/// <param name="root"></param>
	/// <returns></returns>
	template<class T>
	vector<T> front_BianLi(treeNode<T>* root)
	{
		vector<T> arr;
		if (!root)
			return arr;
		stack<treeNode<T>*> st;
		st.push(root);
		while (!st.empty())
		{
			treeNode<T>* p = st.top();
			st.pop();
			arr.push_back(p->val);
			if (p->right)
				st.push(p->right);
			if (p->left)
				st.push(p->left);
		}
		return arr;
	}

	/// <summary>
	/// 非递归中序遍历
	/// </summary>
	/// <param name="root"></param>
	/// <returns></returns>
	template<class T>
	vector<T> middle_BianLi(treeNode<T>* root)
	{
		vector<T>arr;
		if (!root)
			return arr;
		stack<treeNode<T>*>st;
		st.push(root);
		while (!st.empty())
		{
			treeNode<T>* top = st.top();
			if (top->left)
			{
				st.push(top->left);
				continue;
			}
			while (!st.empty())
			{
				treeNode<T>* top = st.top();
				st.pop();
				arr.push_back(top->val);
				if (top->right)
				{
					st.push(top->right);
					break;
				}
			}
		}
		return arr;

	}

	/// <summary>
	/// 非递归后序遍历
	/// </summary>
	/// <param name="root"></param>
	/// <returns></returns>
	template<class T>
	vector<T> back_BianLi(treeNode<T>* root)
	{
		vector<T>arr;
		if (!root)
			return arr;
		stack<treeNode<T>*>st;
		st.push(root);
		while (!st.empty())
		{
			treeNode<T>* top = st.top();
			if (top->left)
			{
				st.push(top->left);
				continue;
			}
			treeNode<T>* right = NULL;
			while (!st.empty())
			{
				treeNode<T>* top = st.top();
				if (top->right&&top->right!=right)
				{
					st.push(top->right);
					break;
				}
				st.pop();
				arr.push_back(top->val);
				right = top;
			}
		}
		return arr;

	}

	
	template<class T>
	void lays_BianLi(vector<vector<T>>& arr, int& n, treeNode<T>* root)
	{
		if (root == NULL)
		{
			return;
		}
		n++;
		if (arr.size() < n)
		{
			arr.resize(n);
		}
		arr[n - 1].push_back(root->val);
		lays_BianLi(arr, n, root->left);
		lays_BianLi(arr, n, root->right);
		n--;
	}
	
	
	/// <summary>
	/// 层序遍历二叉树
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="root"></param>
	/// <returns></returns>
	template<class T>
	vector<vector<T>> lays_BianLi(treeNode<T>* root)
	{
		vector<vector<T>> ret;
		if (root == NULL)
		{
			return ret;
		}
		std::queue<treeNode<T>*>qe;
		qe.push(root);
		while (!qe.empty())
		{
			int n = qe.size();
			vector<T>arr(n);
			for (int i = 0; i < n; i++)
			{
				treeNode<T>* p = qe.front();
				arr[i] = p->val;
				qe.pop();
				if (p->left)
				{
					qe.push(p->left);
				}
				if (p->right)
				{
					qe.push(p->right);
				}
			}
			ret.push_back(arr);
		}
		return ret;
	}


	/// <summary>
	/// 全排列数组
	/// </summary>
	/// <param name="arr"></param>
	/// <returns></returns>
	vector<vector<int>> allSort(vector<int>& arr)
	{
		vector<vector<int>>ret;
		if (arr.size() < 2)
		{
			ret.push_back(arr);
			return ret;
		}
		int x = arr.back();
		arr.pop_back();
		vector<vector<int>>ret1 = allSort(arr);
		for (auto& e : ret1)
		{
			for (int i = 0; i <= e.size(); i++)
			{
				ret.push_back(e);
				ret.back().insert(ret.back().begin() + i, x);
			}
		}
		return ret;
	}

	///排序算法：
	
	/// <summary>
	/// 插入排序：
	/// </summary>
	/// <param name="arr"></param>
	void insertSort(vector<int>& arr)
	{
		int n = arr.size();
		for (int i = 1; i < n; i++)
		{
			for (int j = i - 1; j >= 0; j--)
			{
				if (arr[j] <= arr[j + 1])
				{
					break;
				}
				arr[j] ^= arr[j + 1];
				arr[j + 1] ^= arr[j];
				arr[j] ^= arr[j + 1];
			}
		}
	}

	/// <summary>
	/// 希尔排序：
	/// </summary>
	/// <param name="arr"></param>
	void shellSort(vector<int>& arr)
	{
		int n = arr.size();
		int k = n / 3 + 1;
		for (int K = k; K >= 1; K /= 2)
		{
			for (int i = K; i < n; i++)
			{
				for (int j = i - K; j >= 0; j -= K)
				{
					if (arr[j] <= arr[j + K])
					{
						break;
					}
					int x = arr[j];
					arr[j] = arr[j + K];
					arr[j + K] = x;
				}
			}
		}
	}


	template<class K, class V>
	class AVLTreeNode
	{
	public:
		std::pair<K, V> val;
		AVLTreeNode<K, V>* father;
		AVLTreeNode<K, V>* left;
		AVLTreeNode<K, V>* right;
		int bal;
		AVLTreeNode(std::pair<K, V> x) :val(x) {}
	};
	template<class K, class V>
	class AVLTree
	{
		typedef AVLTreeNode<K, V> Node;
		Node* root;
	public:
		AVLTree() :root(nullptr) {}
		pair<Node*, bool> insert(pair<K, V> x)
		{
			Node* p = root;
			Node* father = nullptr;
			while (p)
			{
				if (x.first == p->val.first)
				{
					return pair<Node*, bool>(p, false);
				}
				father = p;
				if (x.first < p->val.first)
				{
					p = p->left;
					continue;
				}
				p = p->right;
			}
			Node* child = new Node(x);
			if (father == nullptr)
			{
				root = child;
				return pair<Node*, bool>(root, true);
			}
			child->father = father;
			if (x.first > father->val.first)
			{
				father->right = child;
				father->bal += 1;
			}
			else
			{
				father->left = child;
				father->bal -= 1;
			}
			Node* ret = child;
			child = father;
			while (child->bal == -1 || child->bal == 1)
			{
				if (!child->father)
				{
					return make_pair(ret, true);
				}
				father = child->father;
				if (father->right == child)
				{
					father->bal += 1;
				}
				else
				{
					father->bal -= 1;
				}
				child = father;
			}
			if (child->bal == 0)
			{
				return make_pair(ret, true);
			}
			if (child->bal == -2)
			{
				Node* left = child->left;
				if (left->bal == -1)
				{
					right_rotate(child);
					child->bal = 0;
					left->bal = 0;
				}
				else
				{
					Node* right = left->right;
					left_rotate(left);
					right_rotate(child);
					if (right->bal == -1)
					{
						left->bal = 0;
						child->bal = 1;
					}
					else if (right->bal == 0)
					{
						left->bal = 0;
						child->bal = 0;
					}
					else
					{
						left->bal = -1;
						child->bal = 0;
					}
					right->bal = 0;
				}
			}
			else
			{
				Node* right = child->right;
				if (right->bal == 1)
				{
					left_rotate(child);
					child->bal = 0;
					right->bal = 0;
				}
				else
				{
					Node* left = right->left;
					right_rotate(right);
					left_rotate(child);
					if (left->bal == -1)
					{
						right->bal = 1;
						child->bal = 0;
					}
					else if (left->bal == 0)
					{
						right->bal = 0;
						child->bal = 0;
					}
					else
					{
						right->bal = 0;
						child->bal = -1;
					}
					left->bal = 0;
				}
			}
			return make_pair(ret, true);
		}

		void right_rotate(Node* cur)
		{
			Node* father = cur->father;
			Node* left = cur->left;
			if (father == nullptr)
			{
				root = left;
			}
			else if (father->left == cur)
			{
				father->left = left;
			}
			else
			{
				father->right = left;
			}
			left->father = father;
			cur->left = left->right;
			if (left->right)
				left->right->father = cur;
			left->right = cur;
			cur->father = left;
		}

		void left_rotate(Node* cur)
		{
			Node* father = cur->father;
			Node* right = cur->right;
			if (father == nullptr)
			{
				root = right;
			}
			else if (father->left == cur)
			{
				father->left = right;
			}
			else
			{
				father->right = right;
			}
			right->father = father;
			cur->right = right->left;
			if (right->left)
				right->left->father = cur;
			right->left = cur;
			cur->father = right;
		}

		vector<V> middle_BianLi()
		{
			vector<V>arr;
			if (!root)
				return arr;
			stack<AVLTreeNode<K, V>*>st;
			st.push(root);
			while (!st.empty())
			{
				AVLTreeNode<K, V>* top = st.top();
				if (top->left)
				{
					st.push(top->left);
					continue;
				}
				while (!st.empty())
				{
					AVLTreeNode<K, V>* top = st.top();
					st.pop();
					arr.push_back(top->val.second);
					if (top->right)
					{
						st.push(top->right);
						break;
					}
				}
			}
			return arr;

		}

		V& operator[](K key)
		{
			pair<Node*, bool> ret = insert(make_pair(key, V()));
			return ret.first->val.second;
		}

		bool erase(K key)
		{
			if (root == NULL)
				return false;
			Node* cur = root;
			while (cur)
			{
				if (key > cur->val.first)
					cur = cur->right;
				else if (key < cur->val.first)
					cur = cur->left;
				else
					break;
			}
			if (cur == NULL)
				return false;
			if (cur->left)
			{
				Node* p = cur->left;
				while (p->right)
				{
					p = p->right;
				}
				if (p->left)
					p = p->left;
				cur->val = p->val;
				cur = p;
			}
			else if (cur->right)
			{
				Node* p = cur->right;
				while (p->left)
				{
					p = p->left;
				}
				if (p->right)
					p = p->right;
				cur->val = p->val;
				cur = p;
			}
			Node* father = cur->father;
			if (father == NULL)
			{
				delete cur;
				root = NULL;
				return true;
			}
			if (cur == father->left)
			{
				father->left = NULL;
				father->bal++;
			}
			else
			{
				father->right = NULL;
				father->bal--;
			}
			delete cur;
			while (father)
			{
				if (father->bal == 1 || father->bal == -1)
				{
					break;
				}
				if (father->bal == -2)
				{
					Node* left = father->left;
					if (left->bal == -1)
					{
						right_rotate(father);
						father->bal = 0;
						left->bal = 0;
						father = left;
					}
					else if (left->bal == 0)
					{
						right_rotate(father);
						father->bal = -1;
						left->bal = 1;
						break;
					}
					else
					{
						Node* right = left->right;
						left_rotate(left);
						right_rotate(father);
						if (right->bal == -1)
						{
							father->bal = 1;
							left->bal = 0;
						}
						else if (right->bal == 0)
						{
							father->bal = 0;
							left->bal = 0;
						}
						else
						{
							father->bal = 0;
							left->bal = -1;
						}
						right->bal = 0;
						father = right;
					}
				}
				else if (father->bal == 2)
				{
					Node* right = father->right;
					if (right->bal == 1)
					{
						left_rotate(father);
						father->bal = 0;
						right->bal = 0;
						father = right;
					}
					else if (right->bal == 0)
					{
						left_rotate(father);
						father->bal = 1;
						right->bal = -1;
						break;
					}
					else
					{
						Node* left = right->left;
						right_rotate(right);
						left_rotate(father);
						if (left->bal == -1)
						{
							father->bal = 0;
							right->bal = 1;
						}
						else if (left->bal == 0)
						{
							father->bal = 0;
							right->bal = 0;
						}
						else
						{
							father->bal = -1;
							right->bal = 0;
						}
						left->bal = 0;
						father = left;
					}
				}
				if (father->father)
				{
					if (father == father->father->left)
						father->father->bal++;
					else
						father->father->bal--;
				}
				father = father->father;
			}
			return true;
		}






	};


	/// <summary>
	/// 红黑树
	/// </summary>
	enum COLOR
	{
		RED,
		BLACK
	};
	template<class K, class V>
	struct RBTreeNode
	{
		RBTreeNode* _left;
		RBTreeNode* _right;
		RBTreeNode* _father;
		COLOR _cr;
		pair<K, V> _kv;
		RBTreeNode(pair<K, V> kv)
			:_left(nullptr)
			, _right(nullptr)
			, _father(nullptr)
			, _cr(RED)
			, _kv(kv)
		{}

	};
	template<class K, class V>
	class RBTree
	{
		typedef RBTreeNode<K, V> node;
		node* _root = nullptr;
	public:

		void rotate_right(node* p)
		{
			node* father = p->_left;
			if (p == _root)
			{
				_root = father;
				father->_father = nullptr;
			}
			else if (p->_father->_left == p)
			{
				p->_father->_left = father;
				father->_father = p->_father;
			}
			else
			{
				p->_father->_right = father;
				father->_father = p->_father;
			}
			p->_left = father->_right;
			if (father->_right)
				father->_right->_father = p;
			father->_right = p;
			p->_father = father;
		}

		void rotate_left(node* p)
		{
			node* father = p->_right;
			if (p == _root)
			{
				_root = father;
				father->_father = nullptr;
			}
			else if (p->_father->_left == p)
			{
				p->_father->_left = father;
				father->_father = p->_father;
			}
			else
			{
				p->_father->_right = father;
				father->_father = p->_father;
			}
			p->_right = father->_left;
			if (father->_left)
				father->_left->_father = p;
			father->_left = p;
			p->_father = father;
		}

		pair<node*, bool> insert(pair<K, V> kv)
		{
			if (_root == nullptr)
			{
				_root = new node(kv);
				_root->_cr = BLACK;
				return make_pair(_root, true);
			}
			node* cur = _root;
			node* father = nullptr;
			while (cur)
			{
				if (kv.first > cur->_kv.first)
				{
					father = cur;
					cur = cur->_right;
				}
				else if (kv.first < cur->_kv.first)
				{
					father = cur;
					cur = cur->_left;
				}
				else
				{
					return make_pair(cur, false);
				}
			}
			cur = new node(kv);
			if (kv.first > father->_kv.first)
			{
				father->_right = cur;
				cur->_father = father;
			}
			else
			{
				father->_left = cur;
				cur->_father = father;
			}
			node* ret = cur;
			while (1)
			{
				if (father->_cr == BLACK)
					break;
				node* p = father->_father;
				if (p->_left == father)
				{
					if (p->_right && p->_right->_cr == RED)
					{
						father->_cr = BLACK;
						p->_right->_cr = BLACK;
						if (p == _root)
							break;
						p->_cr = RED;
						cur = p;
						father = p->_father;
						continue;
					}
					else if (cur == father->_left)
					{
						rotate_right(p);
						p->_cr = RED;
						father->_cr = BLACK;
						break;
					}
					else
					{
						rotate_left(father);
						rotate_right(p);
						p->_cr = RED;
						cur->_cr = BLACK;
						break;
					}
				}
				else
				{
					if (p->_left && p->_left->_cr == RED)
					{
						father->_cr = BLACK;
						p->_left->_cr = BLACK;
						if (p == _root)
							break;
						p->_cr = RED;
						cur = p;
						father = p->_father;
						continue;
					}
					else if (cur == father->_right)
					{
						rotate_left(p);
						p->_cr = RED;
						father->_cr = BLACK;
						break;
					}
					else
					{
						rotate_right(father);
						rotate_left(p);
						p->_cr = RED;
						cur->_cr = BLACK;
						break;
					}
				}
			}
			return make_pair(ret, true);
		}

		bool erase(K key)
		{
			if (_root == NULL)
			{
				return false;
			}
			node* cur = _root;
			while (cur)
			{
				if (key > cur->_kv.first)
				{
					cur = cur->_right;
				}
				else if (key < cur->_kv.first)
				{
					cur = cur->_left;
				}
				else
				{
					break;
				}
			}
			if (cur == nullptr)
			{
				return false;
			}
			if (cur->_left)
			{
				node* p = cur->_left;
				while (p->_right)
				{
					p = p->_right;
				}
				cur->_kv = p->_kv;
				cur = p;
			}
			else if (cur->_right)
			{
				node* p = cur->_right;
				while (p->_left)
				{
					p = p->_left;
				}
				cur->_kv = p->_kv;
				cur = p;
			}
			node* p = cur;
			while (cur->_father && cur->_cr == BLACK)
			{
				node* father = cur->_father;
				if (cur == father->_left)
				{
					node* brother = father->_right;
					if (brother->_cr == BLACK)
					{
						if (brother->_right && brother->_right->_cr == RED)
						{
							brother->_right->_cr = BLACK;
							brother->_cr = father->_cr;
							father->_cr = BLACK;
							rotate_left(father);
							break;
						}
						else if (brother->_left && brother->_left->_cr == RED)
						{
							brother->_left->_cr = father->_cr;
							father->_cr = BLACK;
							rotate_right(brother);
							rotate_left(father);
							break;
						}
						else
						{
							if (father->_cr == RED)
							{
								brother->_cr = RED;
								father->_cr = BLACK;
								break;
							}
							else
							{
								brother->_cr = RED;
								cur = father;
								continue;
							}
						}
					}
					else
					{
						brother->_cr = BLACK;
						father->_cr = RED;
						rotate_left(father);
						continue;
					}
				}
				else
				{
					node* brother = father->_left;
					if (brother->_cr == BLACK)
					{
						if (brother->_left && brother->_left->_cr == RED)
						{
							brother->_left->_cr = BLACK;
							brother->_cr = father->_cr;
							father->_cr = BLACK;
							rotate_right(father);
							break;
						}
						else if (brother->_right && brother->_right->_cr == RED)
						{
							brother->_right->_cr = father->_cr;
							father->_cr = BLACK;
							rotate_left(brother);
							rotate_right(father);
							break;
						}
						else
						{
							if (father->_cr == RED)
							{
								brother->_cr = RED;
								father->_cr = BLACK;
								break;
							}
							else
							{
								brother->_cr = RED;
								cur = father;
								continue;
							}
						}
					}
					else
					{
						brother->_cr = BLACK;
						father->_cr = RED;
						rotate_right(father);
						continue;
					}
				}
			}
			if (p->_father)
			{
				if (p->_father->_left == p)
				{
					if (p->_left)
					{
						p->_father->_left = p->_left;
						p->_left->_father = p->_father;
					}
					else if (p->_right)
					{
						p->_father->_left = p->_right;
						p->_right->_father = p->_father;
					}
					else
					{
						p->_father->_left = nullptr;
					}
				}
				else
				{
					if (p->_left)
					{
						p->_father->_right = p->_left;
						p->_left->_father = p->_father;
					}
					else if (p->_right)
					{
						p->_father->_right = p->_right;
						p->_right->_father = p->_father;
					}
					else
					{
						p->_father->_right = nullptr;

					}
				}
			}
			else
			{
				_root = nullptr;
			}
			delete(p);
			return true;
		}

		V& operator[](K key)
		{
			pair<node*, bool> ret = insert(make_pair(key, V()));
			return ret.first->_kv.second;
		}

		vector<V> middle_BianLi()
		{
			vector<V>arr;
			if (!_root)
				return arr;
			stack<RBTreeNode<K, V>*>st;
			st.push(_root);
			while (!st.empty())
			{
				RBTreeNode<K, V>* top = st.top();
				if (top->_left)
				{
					st.push(top->_left);
					continue;
				}
				while (!st.empty())
				{
					RBTreeNode<K, V>* top = st.top();
					st.pop();
					arr.push_back(top->_kv.second);
					if (top->_right)
					{
						st.push(top->_right);
						break;
					}
				}
			}
			return arr;

		}

	};

	/// <summary>
	/// 并查集
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<class T>
	class unionFindSet
	{
		vector<int>arr;
		map<T, int>map;
	public:

		unionFindSet(){}

		unionFindSet(vector<T> _t)
		{
			int n = _t.size();
			for (int i = 0; i < n; i++)
			{
				arr.push_back(-1);
				map[_t[i]] = i;
			}
		}

		int findRoot(T child)
		{
			auto it = map.find(child);
			if (it == map.end())
				return -1;
			int n = map[child];
			while (1)
			{
				if (arr[n] < 0)
					return n;
				n = arr[n];
			}
			int n1 = map[child];
			if (n1 != n)
				arr[n1] = n;
			return n;
		}

		bool combine(T t1, T t2)
		{
			if (map.find(t2) == map.end() || map.find(t2) == map.end())
				return false;
			int n1 = findRoot(t1);
			int n2 = findRoot(t2);
			if (n1 == n2)
				return true;
			arr[n2] = n1;
		}

		int set_size()
		{
			int n = 0;
			for (auto& e : arr)
			{
				if (e < 0)
					n++;
			}
			return n;
		}

		void insert(T t)
		{
			if (map.find(t) == map.end())
			{
				map[t] = arr.size();
				arr.push_back(-1);
			}
			return;
		}
	};

	struct edge
	{
		int n1;
		int n2;
		int w;
		edge(int x,int y,int W):n1(x),n2(y),w(W){}
	};

	template<class T>
	class greater
	{
	public:
		bool operator()(T t1, T t2)
		{
			return t1.w > t2.w;
		}
	};


	
	struct pathPoint
	{
		int point;
		int w;
		pathPoint(int n1,int n2):point(n1),w(n2){}
	};



	/// <summary>
	/// 图
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<class T>
	class Graph
	{
		vector<T>arr;
		map<T, int>map;
		vector<vector<int>>mat;
		std::priority_queue<edge, vector<edge>, Lyw::greater<edge>> pq;
		vector<vector<list<int>>>min_path;
		vector<vector<int>>MIN_PATH;
	public:

		Graph(){}

		Graph(vector<T>_t)
		{
			int n = _t.size();
			arr.reserve(n);
			for (int i = 0; i < n; i++)
			{
				arr.push_back(_t[i]);
				map[_t[i]] = i;
			}
			mat.resize(n);
			min_path.resize(n);
			for (int i=0;i<n;i++)
			{
				mat[i].resize(n,MAX);
				min_path[i].resize(n);
			}
			for (int i = 0; i < n; i++)
			{
				mat[i][i] = 0;
				min_path[i][i].push_back(i);
			}
			MIN_PATH = mat;
		}

		void insert(T t)
		{
			if (map.find(t) == map.end())
			{
				map[t] = arr.size();
				arr.push_back(t);
				int n = arr.size();
				mat.resize(n);
				min_path.resize(n);
				for (int i=0;i<n;i++)
				{
					mat[i].push_back(MAX);
					min_path[i].resize(n);
				}
				mat[n - 1].resize(n, MAX);
				mat[n-1][n-1] = 0;
				min_path[n-1][n-1].push_back(n-1);
			}
			MIN_PATH = mat;
		}

		bool addEdge(T t1, T t2, int w)
		{
			if (t1 == t2)
				return false;
			if (map.find(t1) == map.end() || map.find(t2) == map.end())
				return false;
			int n1 = map[t1];
			int n2 = map[t2];
			mat[n1][n2] = w;
			mat[n2][n1] = w;
			pq.push(edge(n2, n1, w));
			return true;
		}

		bool addEdge(edge eg)
		{
			mat[eg.n1][eg.n2] = eg.w;
			mat[eg.n2][eg.n1] = eg.w;
			pq.push(eg);
			return true;
		}

		void print()
		{
			cout << "\n图的数组：\n\n";
			int n = arr.size();
			for (int i=0;i<n;i++)
			{
				cout << "\t[" << i << "]:" << arr[i] << "\t";
			}
			cout << "\n\n图的领接矩阵：\n\n\t\t";
			for (int i = 0; i < n;i++)
			{
				cout << arr[i] << "\t";
			}
			cout << "\n\n\n\t";
			for (int i=0;i<n;i++)
			{
				cout << arr[i]<<"\t";
				for (auto& k : mat[i])
				{
					if (k == MAX)
						cout << "*\t";
					else
						cout << k << "\t";
				}
				cout << "\n\n\t";
			}
		}

		/// <summary>
		/// 广度优先遍历
		/// </summary>
		/// <param name="t"></param>
		/// <returns></returns>
		vector<T> broad_traverse(T t)
		{
			vector<T>ret;
			if (map.find(t) == map.end())
				return ret;
			int root = map[t];
			std::bitset<MAX>bt;
			std::queue<int>qe;
			qe.push(root);
			bt.set(root);
			while (!qe.empty())
			{
				int front = qe.front();
				qe.pop();
				ret.push_back(arr[front]);
				for (int i = 0; i < arr.size(); i++)
				{
					if (mat[front][i] != 0 && bt[i] == 0)
					{
						qe.push(i);
						bt.set(i);
					}
				}
			}
			return ret;
		}

		void allEdge()
		{
			for (int i = 0; i < arr.size(); i++)
			{
				for (int j = i+1; j < arr.size(); j++)
				{
					int x= rand() % 98+2;
					mat[i][j] =x ;
					mat[j][i] = x;
					pq.push(edge(i, j, x));
				}
			}
		}

		/// <summary>
		/// 深度优先遍历
		/// </summary>
		/// <param name="t"></param>
		/// <returns></returns>
		vector<T> deep_traverse(T t)
		{
			vector<T>ret;
			if (map.find(t) == map.end())
				return ret;
			int root = map[t];
			std::bitset<MAX> bt;
			std::stack<int>st;
			st.push(root);
			bt.set(root);
			while (!st.empty())
			{
				int top = st.top();
				st.pop();
				ret.push_back(arr[top]);
				for (int i = arr.size()-1; i >=0; i--)
				{
					if (mat[top][i] != 0 && bt[i] == 0)
					{
						st.push(i);
						bt.set(i);
					}
				}
			}
			return ret;
		}

		/// <summary>
		/// 层序遍历返回二维数组
		/// </summary>
		/// <param name="t"></param>
		/// <returns></returns>
		vector<vector<T>> laysTraverse(T t)
		{
			vector<vector<T>>ret;
			if (map.find(t) == map.end())
				return ret;
			int root = map[t];
			std::bitset<MAX> bt;
			std::queue<int>qe;
			qe.push(root);
			bt.set(root);
			while (!qe.empty())
			{
				int n = qe.size();
				vector<T>arr1;
				for (int i = 0; i < n; i++)
				{
					int front = qe.front();
					qe.pop();
					arr1.push_back(arr[front]);
					for (int j = 0; j < arr.size(); j++)
					{
						if (mat[front][j] != 0 && bt[j] == 0)
						{
							qe.push(j);
						}
					}
				}
				ret.push_back(arr1);
			}
			return ret;
		}

		vector<list<T>> path(T t, std::bitset<MAX>& bt)
		{
			vector<list<T>>ret;
			if (map.find(t) == map.end())
				return ret;
			int n = map[t];
			bt.set(n);
			vector<int>arr1;
			for (int i = 0; i < arr.size(); i++)
			{
				if (mat[n][i] != 0 && bt[i] == 0)
				{
					arr1.push_back(i);
				}
			}
			if (arr1.size() == 0)
			{
				list<T>lt;
				lt.push_back(t);
				ret.push_back(lt);
				bt.set(n, false);
				return ret;
			}
			for (int i = 0; i < arr1.size(); i++)
			{
				T x = arr[arr1[i]];
				vector<list<T>>ret1 = path(x, bt);
				for (int j = 0; j < ret1.size();j++)
				{
					ret1[j].push_front(t);
					ret.push_back(ret1[j]);
				}
			}
			bt.set(n, false);
			return ret;
		}

		/// <summary>
		/// 返回t开始的所有路径
		/// </summary>
		vector<list<T>> path(T t)
		{
			std::bitset<MAX>bt;
			return path(t, bt);
		}

		int size()
		{
			return arr, size();
		}

		int edgeSize()
		{
			return pq.size();
		}

		Graph minTree()
		{
			Graph gh(arr);
			std::priority_queue<edge, vector<edge>, Lyw::greater<edge>> pq1 = pq;
			unionFindSet<T> ust(arr);
			int n = 0;
			while (!pq1.empty())
			{
				int n1 = pq1.top().n1;
				int n2 = pq1.top().n2;
				int w = pq1.top().w;
				pq1.pop();
				if (ust.findRoot(arr[n1])==ust.findRoot(arr[n2]))
					continue;
				gh.addEdge(arr[n1], arr[n2], w);
				ust.combine(arr[n1], arr[n2]);
				n++;
				if (n == arr.size() - 1)
					break;
			}
			return gh;
		}

		Graph minTree_list()
		{
			Graph gh(arr);
			set<int> lt1;
			lt1.insert(0);
			set<int>lt2;
			for (int i = 1; i < arr.size(); i++)
			{
				lt2.insert(i);
			}
			while (!lt2.empty())
			{
				std::priority_queue<edge, vector<edge>, greater<edge>>pq;
				for (auto& i : lt1)
				{
					for (auto& j : lt2)
					{
						if (mat[i][j] != 0)
						{
							pq.push(edge(i, j, mat[i][j]));
						}
					}
				}
				gh.addEdge(pq.top());
				lt1.insert(pq.top().n2);
				lt2.erase(pq.top().n2);
			}
			return gh;
		}

		void print_edge()
		{
			std::priority_queue<edge, vector<edge>, Lyw::greater<edge>> pq1=pq;
			int size = 0;
			int n = pq1.size();
			cout << endl;
			for (int i=0;i<n;i++)
			{
				edge eg = pq1.top();
				size += eg.w;
				cout << arr[eg.n1] << "->" << arr[eg.n2] << ":" << eg.w << endl;
				pq1.pop();
			}
			cout << "总大小：" << size;

		}

		void updatePath()
		{
			int n = arr.size();
			for (int i = 0; i < n; i++)
			{
				updatePath(i);
			}
		}

		void updatePath(int root)
		{
			int n = arr.size();
			std::map<int,int> map1;
			for (int i = 0; i < n; i++)
			{
				if (i == root)
					map1[i] = 0;
				else
					map1[i] = MAX;
			}
			while (!map1.empty())
			{
				std::priority_queue<pathPoint, vector<pathPoint>, Lyw::greater<pathPoint>> PQ;
				for (auto& e : map1)
				{
					PQ.push(pathPoint(e.first,e.second));
				}
				pathPoint pp=PQ.top();
				int k = pp.point;
				for (int i = 0; i < n; i++)
				{
					if (map1.find(i) == map1.end())
						continue;
					if (i == k || mat[k][i] == MAX)
						continue;
					int x = map1[k] + mat[k][i];
					if (x >= map1[i])
						continue;
					map1[i] = x;
					min_path[root][i] = min_path[root][k];
					min_path[root][i].push_back(i);
				}
				MIN_PATH[root][k] = map1[k];
				map1.erase(k);
			}
		}

		void print_path()
		{
			int n = arr.size();
			cout << "\n\n图的最短路径：\n\n\t\t";
			for (int i = 0; i < n; i++)
			{
				cout << arr[i] << "\t";
			}
			cout << "\n\n\n\t";
			for (int i = 0; i < n; i++)
			{
				cout << arr[i] << "\t";
				for (auto& k : MIN_PATH[i])
				{
					cout << k << "\t";
				}
				cout << "\n\n\t";
			}
			cout << "\n\n图的最短路径：\n\n\t\t";
			for (int i = 0; i < n; i++)
			{
				for (int j=0;j<n;j++)
				{
					cout << arr[i] << "到" << arr[j] << "的路径：";
					for (auto& e : min_path[i][j])
					{
						cout << arr[e]<< "->";
					}
					cout << endl;
				}
			}



		}



	};

}






int main()
{
	
	size_t x = 5;
}