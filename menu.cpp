#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operate.cpp"

void Menu();					//显示开始菜单
void MenuChoice(char ch);		//菜单选择及权限登陆

void AdminMenu();				//显示管理员菜单及操作
void AdminMenuChoice();			//管理员菜单及操作

void TeacherMenu();				//显示老师菜单及操作
void TeacherMenuChoice();		//老师菜单及操作

void StudentMenu();				//显示学生菜单及操作
void StudentMenuChoice();		//学生菜单及操作

void Menu()								//开始菜单
{
	system("color A0");
	printf("\n\n\t学院级学生管理系统\n\n");
	printf("\t\t1.我是管理员\n\n");
    printf("\t\t2.我是教师\n\n");
    printf("\t\t3.我是学生\n\n");  
    printf("\t\t4.退出系统\n\n"); 	
}

void MenuChoice(char c)					//菜单选择及权限登陆
{
	while (getchar() != '\n');		//清空缓存区
	printf("\t请输入");

	int ret;
	char account[20];		//账户
	char password[20];		//密码	

	switch(c)
	{
		case '1':										//管理员登陆
		{
			char stdacc[20];		//设置标准账户与密码
			char stdpass[20];
			strcpy_s(stdacc, "linshujing");
			strcpy_s(stdpass, "password");

			printf(" 管理员账号：\n");
			gets_s(account,20);
			while((ret= strcmp(account, stdacc))!= 0)
			{
				printf("没有此管理员账号！抱歉！请重新输入！\n");
				gets_s(account);
			}
			printf("\t             密码：\n");
			gets_s(password,20);
			if((ret= strcmp(password, stdpass))!= 0)
			{
				printf("管理员密码输入错误！请重新输入！\n");
				gets_s(password);
			}
			AdminMenuChoice();
			break;
		}
		case '2':									//老师登陆
		{
			int i, num = 0;
			//读取文件
			FILE *fp;
			fopen_s(&fp, "password/teachers.data", "r");
			char stdacc[20][20];
			char stdpass[20][20];
			while (!feof(fp))
			{
				num++;
				fscanf_s(fp, "%s\n", stdacc[num], 20);
				fscanf_s(fp, "%s\n", stdpass[num], 20);
			}
			bool flag = true;
			printf(" 教师账号：\n");
			gets_s(account,20);
			//对帐号进行判断
			do {
				for (i = 1; i <= num; i++)
				{
					if (!strcmp(account, stdacc[i]))
					{
						flag = false;
						break;
					}
				}
				if (i == num + 1)
				{
					printf("没有此老师账号！抱歉！请重新输入！\n");
					gets_s(account);
				}
			} while (flag);

			printf("\t           密码：\n");
			gets_s(password,20);
			while (strcmp(password, stdpass[i]))
			{
				printf("该老师账号密码输入错误！请重新输入！\n");
				gets_s(password);
			}
			TeacherMenuChoice();
			break;
		}
		case '3':									//学生登陆
		{
			int i, num = 0;
			//读取文件
			FILE *fp;
			fopen_s(&fp, "password/students.data", "r");
			char stdacc[20][20];
			char stdpass[20][20];
			while (!feof(fp))
			{
				num++;
				fscanf_s(fp, "%s\n", stdacc[num], 20);
				fscanf_s(fp, "%s\n", stdpass[num], 20);
			}
			bool flag = true;
			printf(" 学生账号：\n");
			gets_s(account, 20);
			//对帐号进行判断
			do {
				for (i = 1; i <= num; i++)
				{
					if (!strcmp(account, stdacc[i]))
					{
						flag = false;
						break;
					}
				}
				if (i == num + 1)
				{
					printf("没有此学生账号！抱歉！请重新输入！\n");
					gets_s(account);
				}
			} while (flag);

			printf("\t           密码：\n");
			gets_s(password, 20);
			while (strcmp(password, stdpass[i]))
			{
				printf("该学生账号密码输入错误！请重新输入！\n");
				gets_s(password);
			}
			StudentMenuChoice();
			break;
		}
		case '4':
			exit(0);
	}
	while ((getchar()) != '\n');
}

void AdminMenu()							//显示管理员菜单及操作
{
	system("cls");
	printf("\n\n\t管理员操作菜单\n\n");
	printf("\t\t1.添加学生信息\n\n");
    printf("\t\t2.删除学生信息\n\n");
    printf("\t\t3.为指定学生添加指定的课程\n\n");  
    printf("\t\t4.删除指定学生的指定课程\n\n"); 
    printf("\t\t5.为所有学生添加指定课程\n\n"); 
    printf("\t\t6.删除所有学生的指定课程\n\n"); 
	printf("\t\t7.返回\n\n"); 
}

void AdminMenuChoice()							//管理员菜单及操作
{
	char ch;
	while(1)
	{
		AdminMenu();
		printf("请选择： ");
		ch= getchar();
		while(ch!= '1' && ch!= '2' && ch!= '3' && ch!= '4' && ch!= '5'&& ch != '6' && ch != '7')
		{
			printf("输入错误！！请再次输入！\n");
			ch= getchar();
		}
		if(ch == '7')
			break;
		AdminOperate(ch);
	}
}

void TeacherMenu()						//显示老师菜单及操作
{
	system("cls");
	printf("\n\n\t教师操作菜单\n\n");
	printf("\t\t1.为某个学生某门课给分\n\n");
    printf("\t\t2.查看某门课及格率，平均分\n\n");
    printf("\t\t3.查看某门课所有学生成绩\n\n");  
    printf("\t\t4.返回\n\n"); 
}

void TeacherMenuChoice()						//老师菜单及操作
{
	char ch;
	while(1)
	{
		TeacherMenu();
		printf("请选择： ");
		ch= getchar();
		while(ch!= '1' && ch!= '2' && ch!= '3' && ch!= '4')
		{
			printf("输入错误！！请再次输入！\n");
			ch= getchar();
		}
		if(ch == '4')
			break;
		TeacherOperate(ch);		
	}
}

void StudentMenu()						//显示学生菜单及操作
{
	system("cls");
	printf("\n\n\t学生操作菜单\n\n");
	printf("\t\t1.查看我的信息\n\n");
    printf("\t\t2.返回\n\n");
}

void StudentMenuChoice()						//学生菜单及操作
{
	char ch;
	while(1)
	{
		StudentMenu();
		printf("请选择： ");
		ch= getchar();
		while(ch!= '1' && ch!= '2')
		{
			fflush(stdin);
			printf("输入错误！！请再次输入！\n");
			ch= getchar();
		}
		if(ch == '2')
			break;
		StudentOperate(ch);
	}
}



