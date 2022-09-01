#define _CRT_SECURE_NO_WARNINGS 1

#include"contact.h"


void(*pfun[7])()={NULL,add,del,search,edit,show,sort};
typedef struct CPS
{
	char name[30];
	char tele[20];
	char sex[4];
	char age;
	char ip[50];
}CPS;

int count=0;///总人数
CPS* cps;

int compare(const void*p1,const void* p2)
{
	char*pp1=(char*)&(*(CPS*)p1).age;
	char*pp2=(char*)&(*(CPS*)p2).age;
	return *pp1-*pp2;
}

void menu()
{
	printf("当前通讯录总人数为： %d",count);
	printf("\n\n\t*********************    0    EXIT	***********************\n\n");
	printf("\t*********************    1    Add	***********************\n");
	printf("\t*********************    2    Del	***********************\n");
	printf("\t*********************    3    Search	***********************\n");
	printf("\t*********************    4    Edit	***********************\n");
	printf("\t*********************    5    Show	***********************\n");
	printf("\t*********************    6    Sort	***********************\n\n\n\n\n\t\t\t");
}

void add()
{
	system("cls");
	int i=count;
	static CPS* pp=cps;
	cps=(CPS*)realloc(cps,sizeof(CPS)*(i+1));
	if(cps==NULL)
	{
		cps=pp;
		printf("%s",strerror(errno));
		system("pause");
		return;
	}
	printf("\n\n\n\t\t姓名： ");
	scanf("%s",cps[i].name);
	printf("\n\n\t\t姓别： ");
	scanf("%s",cps[i].sex);
	printf("\n\n\t\t年龄： ");
	scanf("%d",&cps[i].age);
	printf("\n\n\t\t电话： ");
	scanf("%s",cps[i].tele);
	printf("\n\n\t\t地址： ");
	scanf("%s",cps[i].ip);
	printf("\n\n\n\t\t\t%s 已添加成功！\n",cps[i].name);
	count++;
	system("pause");
}

void del()
{
	system("cls");
	printf("\n\n\n\t\t您要删除谁呢：");
	char name[20];
	scanf("%s",name);
	int i=0;
	for(i=0;i<count;i++)
	{
		if(strcmp(cps[i].name,name)==0)
		{
			memcpy(&cps[i],&cps[count-1],sizeof(CPS));
			count--;
			printf("\n\n\n\n\t\t\t\t%s 已被删除！\n",name);
			system("pause");
			return;
		}
	}
	printf("\n\n\n\n\t\t\t\t查无此人!");
	system("pause");
}

void search()
{
	system("cls");
	printf("\n\n\n\t\t您要搜索谁呢：");
	char name[20];
	scanf("%s",name);
	int i=0;
	for(i=0;i<count;i++)
	{
		if(strcmp(cps[i].name,name)==0)
		{
			printf("\n\n\n\t\t姓名：%s\n\n\t\t性别：%s\n\n\t\t年龄：%d岁\n\n\t\t电话：%s\n\n\t\t地址：%s\n\n\t\t",
			cps[i].name,
			cps[i].sex,
			cps[i].age,
			cps[i].tele,
			cps[i].ip);
			system("pause");
			return;
		}
		
	}
	printf("\n\n\n\n\t\t\t\t查无此人!");
	system("pause");
}

void edit()
{
	system("cls");
	printf("\n\n\n\t\t您要重新编辑谁呢：");
	char name[20];
	scanf("%s",name);
	int i=0;
	for(i=0;i<count;i++)
	{
		if(strcmp(cps[i].name,name)==0)
		{
			printf("\n\n\n\t\t姓名： ");
			scanf("%s",cps[i].name);
			printf("\n\n\t\t姓别： ");
			scanf("%s",cps[i].sex);
			printf("\n\n\t\t年龄： ");
			scanf("%d",&cps[i].age);
			printf("\n\n\t\t电话： ");
			scanf("%s",cps[i].tele);
			printf("\n\n\t\t地址： ");
			scanf("%s",cps[i].ip);
			printf("\n\n\n\n\t\t\t\t%s 已被修改！\n",name);
			system("pause");
			return;
		}
	}
	printf("\n\n\n\n\t\t\t\t查无此人!");
	system("pause");
}

void show()
{
	system("cls");
	int i=0;
	for(i=0;i<count;i++)
	{
		printf("%s\t%s\t%d岁\t电话：%s\t地址：%s\n",
			cps[i].name,
			cps[i].sex,
			cps[i].age,
			cps[i].tele,
			cps[i].ip);
	}
	system("pause");
}

void sort()
{
	system("cls");
	qsort(cps,count,sizeof(CPS),compare);
	printf("\n\n\t\t按照年龄排序已经完成!\n\n\n\t\t");
	system("pause");
}

void contact()///通讯录主函数：
{
	FILE*pf=fopen("data.txt","rb");
	if(pf!=NULL)
	{
		fread(&count,sizeof(int),1,pf);
		cps=(CPS*)malloc(count*sizeof(CPS));
		fread(cps,sizeof(CPS),count,pf);
		fclose(pf);
		pf=NULL;
	}
	while(1)
	{
		system("cls");
		menu();
		printf("请输入您的选择： ");
		int n=7;
		scanf("%d",&n);
		while(getchar()!=10){}
		if(n==0)
			break;
		if(n>6)
			continue;
		pfun[n]();
	}
	pf=fopen("data.txt","wb");
	fwrite(&count,sizeof(int),1,pf);
	fwrite(cps,sizeof(CPS),count,pf);
	fclose(pf);
	pf=NULL;
	free(cps);
}

