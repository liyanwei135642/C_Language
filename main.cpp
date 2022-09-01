#include "math.h"
#include "mat.h"
#include "plane.h"
#include "space.h"
#include "three.h"
#include "eight.h"
#include "twenty.h"
#include "rope.h"
#include<string>
void (*pfun[10])() = {NULL,math,mat,plane,space,three,eight,twenty,rope };

void menu()
{
	cout << "\n                        欢迎来到：*** V 空间***";
	printf("\n\n\t****************    0    退出	                ***************\n");
	printf("\n\t****************    1    数学运算	        ***************\n");
	printf("\n\t****************    2    矩阵运算	        ***************\n");
	printf("\n\t****************    3    平面杆系结构计算	***************\n");
	printf("\n\t****************    4    空间杆系结构计算	***************\n");
	printf("\n\t****************    5    有限元三节点计算	***************\n");
	printf("\n\t****************    6    有限元八节点计算	***************\n");
	printf("\n\t****************    7    有限元二十节点计算	***************\n");
	printf("\n\t****************    8    悬索桥索力索长计算	***************\n\n\n\t\t\t");
}

void main()///V空间主函数：
{
	/*FILE* pf = fopen("data.txt", "rb");
	if (pf != NULL)
	{
		fread(&count, sizeof(int), 1, pf);
		cps = (CPS*)malloc(count * sizeof(CPS));
		fread(cps, sizeof(CPS), count, pf);
		fclose(pf);
		pf = NULL;
	}*/
	while (1)
	{
		system("cls");
		menu();
		printf("请输入您的选择： ");
		int n = -1;
		scanf("%d",&n);
		while(n < 0 || n>8)
		{
			cout << "\n\t\t输入错误：\n\n\t\t请输入0-8的整数:";
			while (getchar() != 10) {}
			scanf("%d", &n);
		}
		while(getchar()!=10){}
		if (n == 0)
			break;
		pfun[n]();
	}
	/*pf = fopen("data.txt", "wb");
	fwrite(&count, sizeof(int), 1, pf);
	fwrite(cps, sizeof(CPS), count, pf);
	fclose(pf);
	pf = NULL;
	free(cps);*/
}

